#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Studentas.h"
#include "Generavimas.h"
#include "FailuIO.h"
#include "Rusiavimas.h"

using namespace std;
using namespace std::chrono;

double laikas(const high_resolution_clock::time_point& a, const high_resolution_clock::time_point& b)
{
    return duration<double>(b - a).count();
}

// Saugus v/p/b pasirinkimo nuskaitymas su klaidos pranesimu
char ivestiRikiavimoLauka()
{
    string eilute;
    cout << "Pagal ka rusiuoti rezultatu failus? (v - varda, p - pavarde, b - galutini bala): ";
    while (getline(cin, eilute)) {
        if (eilute.size() == 1) {
            char c = eilute[0];
            if (c == 'v' || c == 'V') return 'v';
            if (c == 'p' || c == 'P') return 'p';
            if (c == 'b' || c == 'B') return 'b';
        }
        cout << "Klaida: iveskite v, p arba b: ";
    }
    return 'v'; // jei cin uzdarytas (EOF) - saugus variantas
}

int main()
{
    srand((unsigned)time(0));

    vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
    const int NDKIEK = 15;
    const int PAKARTOJIMAI = 5; // kiek kartu testuoti kiekviena faila (vidurkiui)

    // 1 etapas: failu generavimas (matuojamas tik kurimo laikas)
    cout << "=== Failu generavimas ===\n";
    for (int d : dydziai) {
        string failas = "studentai_" + to_string(d) + ".txt";

        auto t1 = high_resolution_clock::now();
        generuotiFaila(failas, d, NDKIEK);
        auto t2 = high_resolution_clock::now();

        cout << d << " irasu failo kurimo laikas: " << laikas(t1, t2) << "\n";
    }

    char laukas = ivestiRikiavimoLauka();

    cout << "\n=== Testavimas (kiekvienas dydis kartojamas " << PAKARTOJIMAI << " kartus) ===\n";
    for (int d : dydziai) {
        string failas = "studentai_" + to_string(d) + ".txt";
        string silpnesniFailas = "vargsiukai_" + to_string(d) + ".txt";
        string stipresniFailas = "kietiakiai_" + to_string(d) + ".txt";

        double sum_read = 0, sum_sort = 0, sum_split = 0, sum_split_total = 0;
        double sum_sort_field = 0, sum_write_silp = 0, sum_write_stip = 0, sum_write_total = 0;
        double sum_total = 0;
        int sekmingi = 0;

        for (int run = 0; run < PAKARTOJIMAI; run++) {
            vector<Studentas> studentai;
            vector<Studentas> silpnesni, stipresni;

            auto t1 = high_resolution_clock::now();
            if (!skaitytiIsFailo(failas, studentai, d)) {
                cout << "Klaida: nepavyko nuskaityti failo " << failas << "\n";
                break;
            }
            auto t2 = high_resolution_clock::now();

            rusiuotiDidejimoTvarka(studentai);
            auto t3 = high_resolution_clock::now();

            skirstytiIDvi(studentai, silpnesni, stipresni);
            auto t4 = high_resolution_clock::now();

            rusiuotiPagalLauka(silpnesni, laukas);
            rusiuotiPagalLauka(stipresni, laukas);
            auto t4b = high_resolution_clock::now();

            irasytiIFaila(silpnesniFailas, silpnesni);
            auto t5 = high_resolution_clock::now();

            irasytiIFaila(stipresniFailas, stipresni);
            auto t6 = high_resolution_clock::now();

            sum_read        += laikas(t1, t2);
            sum_sort        += laikas(t2, t3);
            sum_split       += laikas(t3, t4);
            sum_split_total += laikas(t2, t4);
            sum_sort_field  += laikas(t4, t4b);
            sum_write_silp  += laikas(t4b, t5);
            sum_write_stip  += laikas(t5, t6);
            sum_write_total += laikas(t4b, t6);
            sum_total       += laikas(t1, t6);
            sekmingi++;
        }

        if (sekmingi == 0) continue;

        cout << d << " irasu (vidurkis is " << sekmingi << " bandymu):\n";
        cout << "  nuskaitymo laikas:                              " << sum_read / sekmingi << "\n";
        cout << "  rusiavimas didejimo tvarka (std::sort):         " << sum_sort / sekmingi << "\n";
        cout << "  dalijimas i dvi grupes:                         " << sum_split / sekmingi << "\n";
        cout << "  rusiavimas i dvi grupes (sort + dalijimas):     " << sum_split_total / sekmingi << "\n";
        cout << "  rusiavimas pagal pasirinkta parametra:          " << sum_sort_field / sekmingi << "\n";
        cout << "  vargsiuku irasymas i faila:                     " << sum_write_silp / sekmingi << "\n";
        cout << "  kietiakiu irasymas i faila:                     " << sum_write_stip / sekmingi << "\n";
        cout << "  abieju failu irasymas (bendras):                " << sum_write_total / sekmingi << "\n";
        cout << "  bendras testo laikas:                           " << sum_total / sekmingi << "\n\n";
    }

    return 0;
}
