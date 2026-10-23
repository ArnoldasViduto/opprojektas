#include <iostream>
#include <vector>
#include <list>
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
    return 'v';
}

// 1. Kriterijaus punktas: rankinio ivedimo metu isvesti objekto adresa
void rodytiAdresa()
{
    Studentas A;
    cout << "\n--- RANKINIS IVEDIMAS (Adreso demonstracija) ---\n";
    cout << "Iveskite varda: "; cin >> A.var;
    cout << "Iveskite pavarde: "; cin >> A.pav;
    cout << "Iveskite egzamino pazymi: "; cin >> A.egz;

    cout << "Studento objekto saugojimo atmintyje adresas: " << &A << "\n";
    cout << "-----------------------------------------------\n\n";
    cin.ignore(10000, '\n'); // isvalome buferi
}

int main()
{
    srand((unsigned)time(0));

    // Pirma parodome adresa (kriterijui)
    rodytiAdresa();

    vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
    const int NDKIEK = 15;
    const int PAKARTOJIMAI = 3; // Galite padidinti iki 5, jei norite tikslesnio vidurkio

    cout << "=== Failu generavimas ===\n";
    for (int d : dydziai) {
        string failas = "studentai_" + to_string(d) + ".txt";
        auto t1 = high_resolution_clock::now();
        generuotiFaila(failas, d, NDKIEK);
        auto t2 = high_resolution_clock::now();
        cout << d << " irasu failo kurimo laikas: " << laikas(t1, t2) << "\n";
    }

    char laukas = ivestiRikiavimoLauka();

    // ==========================================
    // 1 DALIS: VECTOR TESTAVIMAS
    // ==========================================
    cout << "\n=== TESTAVIMAS SU STD::VECTOR ===\n";
    for (int d : dydziai) {
        string failas = "studentai_" + to_string(d) + ".txt";
        string silpniFailas = "vargsiukai_vec_" + to_string(d) + ".txt";
        string stiprusFailas = "kietiakiai_vec_" + to_string(d) + ".txt";

        double sum_read = 0, sum_split = 0, sum_write = 0;
        int sekmingi = 0;

        for (int run = 0; run < PAKARTOJIMAI; run++) {
            vector<Studentas> studentai;
            vector<Studentas> silpni, stiprus;

            auto t1 = high_resolution_clock::now();
            if (!skaitytiIsFailo(failas, studentai, d)) break;
            auto t2 = high_resolution_clock::now();

            skirstytiVektoriu(studentai, silpni, stiprus);
            auto t3 = high_resolution_clock::now();
            
            rusiuotiVektoriu(silpni, laukas);
            rusiuotiVektoriu(stiprus, laukas);

            irasytiIFaila(silpniFailas, silpni);
            irasytiIFaila(stiprusFailas, stiprus);
            auto t4 = high_resolution_clock::now();

            sum_read += laikas(t1, t2);
            sum_split += laikas(t2, t3);
            sum_write += laikas(t3, t4);
            sekmingi++;
        }

        if (sekmingi > 0) {
            cout << d << " irasu (Vector):\n";
            cout << "  Nuskaitymas:        " << sum_read / sekmingi << " s\n";
            cout << "  Skirstymas:         " << sum_split / sekmingi << " s\n";
            cout << "  Rikiavimas+Irasymas:" << sum_write / sekmingi << " s\n\n";
        }
    }

    // ==========================================
    // 2 DALIS: LIST TESTAVIMAS
    // ==========================================
    cout << "=== TESTAVIMAS SU STD::LIST ===\n";
    for (int d : dydziai) {
        string failas = "studentai_" + to_string(d) + ".txt";
        string silpniFailas = "vargsiukai_list_" + to_string(d) + ".txt";
        string stiprusFailas = "kietiakiai_list_" + to_string(d) + ".txt";

        double sum_read = 0, sum_split = 0, sum_write = 0;
        int sekmingi = 0;

        for (int run = 0; run < PAKARTOJIMAI; run++) {
            list<Studentas> studentai;
            list<Studentas> silpni, stiprus;

            auto t1 = high_resolution_clock::now();
            if (!skaitytiIsFailo(failas, studentai, d)) break;
            auto t2 = high_resolution_clock::now();

            skirstytiSarasa(studentai, silpni, stiprus);
            auto t3 = high_resolution_clock::now();
            
            rusiuotiSarasa(silpni, laukas);
            rusiuotiSarasa(stiprus, laukas);

            irasytiIFaila(silpniFailas, silpni);
            irasytiIFaila(stiprusFailas, stiprus);
            auto t4 = high_resolution_clock::now();

            sum_read += laikas(t1, t2);
            sum_split += laikas(t2, t3);
            sum_write += laikas(t3, t4);
            sekmingi++;
        }

        if (sekmingi > 0) {
            cout << d << " irasu (List):\n";
            cout << "  Nuskaitymas:        " << sum_read / sekmingi << " s\n";
            cout << "  Skirstymas:         " << sum_split / sekmingi << " s\n";
            cout << "  Rikiavimas+Irasymas:" << sum_write / sekmingi << " s\n\n";
        }
    }

    return 0;
}
