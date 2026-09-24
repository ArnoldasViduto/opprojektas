#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

struct studentas {
    std::string var, pav;
    std::vector<int> paz;
    int egz;
    double vid;
    double med;
};

void apskaiciuoti(studentas& A)
{
    std::vector<int> visi = A.paz;
    visi.push_back(A.egz);

    int suma = 0;
    for (int p : visi) suma += p;
    A.vid = (double)suma / visi.size();

    std::sort(visi.begin(), visi.end());
    int n = visi.size();
    if (n % 2 == 0)
        A.med = (visi[n / 2 - 1] + visi[n / 2]) / 2.0;
    else
        A.med = visi[n / 2];
}

int main()
{
    using namespace std;

    vector<studentas> studentai;

    char budas;
    cout << "Duomenis skaityti is failo (f) ar ivesti rankiniu budu (r)? ";
    cin >> budas;

    if (budas == 'f') {
        ifstream f("studentai10000.txt");

        string antraste;
        getline(f, antraste);

        istringstream is(antraste);
        string zodis;
        int stulpeliai = 0;
        while (is >> zodis) stulpeliai++;
        int ndKiek = stulpeliai - 3;

        studentas A;
        while (f >> A.var >> A.pav) {
            A.paz.assign(ndKiek, 0);
            for (int i = 0; i < ndKiek; i++)
                f >> A.paz[i];
            f >> A.egz;

            apskaiciuoti(A);
            studentai.push_back(A);
        }
    }
    else {
        char dar;
        do {
            studentas A;

            cout << "Vardas: ";
            cin >> A.var;
            cout << "Pavarde: ";
            cin >> A.pav;

            char darPaz;
            do {
                int n;
                cout << "Namu darbo pazymys: ";
                cin >> n;
                A.paz.push_back(n);

                cout << "Ar yra dar pazymiu? (t/n): ";
                cin >> darPaz;
            } while (darPaz == 't' || darPaz == 'T');

            cout << "Egzaminas: ";
            cin >> A.egz;

            apskaiciuoti(A);
            studentai.push_back(A);

            cout << "Ar yra dar studentu? (t/n): ";
            cin >> dar;
        } while (dar == 't' || dar == 'T');
    }

    char pasirinkimas;
    cout << "Vidurki (v), mediana (m) ar abu (a)? ";
    cin >> pasirinkimas;

    cout << left << setw(16) << "Pavarde" << setw(16) << "Vardas";
    if (pasirinkimas == 'v')
        cout << "Galutinis (Vid.)\n";
    else if (pasirinkimas == 'm')
        cout << "Galutinis (Med.)\n";
    else
        cout << "Galutinis (Vid.) / Galutinis (Med.)\n";

    cout << string(60, '-') << "\n";

    cout << fixed << setprecision(2);
    for (studentas& s : studentai) {
        cout << left << setw(16) << s.pav << setw(16) << s.var;
        if (pasirinkimas == 'v')
            cout << s.vid << "\n";
        else if (pasirinkimas == 'm')
            cout << s.med << "\n";
        else
            cout << setw(16) << s.vid << s.med << "\n";
    }

    return 0;
}
