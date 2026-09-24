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

int main()
{
    using namespace std;

    ifstream f("studentai10000.txt");

    string antraste;
    getline(f, antraste);

    istringstream is(antraste);
    string zodis;
    int stulpeliai = 0;
    while (is >> zodis) stulpeliai++;
    int ndKiek = stulpeliai - 3;

    vector<studentas> studentai;
    studentas A;

    while (f >> A.var >> A.pav) {
        A.paz.assign(ndKiek, 0);
        for (int i = 0; i < ndKiek; i++)
            f >> A.paz[i];
        f >> A.egz;

        vector<int> visi = A.paz;
        visi.push_back(A.egz);

        int suma = 0;
        for (int p : visi) suma += p;
        A.vid = (double)suma / visi.size();

        sort(visi.begin(), visi.end());
        int n = visi.size();
        if (n % 2 == 0)
            A.med = (visi[n / 2 - 1] + visi[n / 2]) / 2.0;
        else
            A.med = visi[n / 2];

        studentai.push_back(A);
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

