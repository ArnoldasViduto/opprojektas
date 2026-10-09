#include "FailuIO.h"
#include <fstream>
#include <sstream>
#include <iomanip>

bool skaitytiIsFailo(const std::string& failoVardas, std::vector<Studentas>& studentai, int numatomasKiekis)
{
    using namespace std;

    ifstream f(failoVardas);
    if (!f.is_open()) return false;

    string antraste;
    if (!getline(f, antraste)) return false;

    istringstream is(antraste);
    string zodis;
    int stulpeliai = 0;
    while (is >> zodis) stulpeliai++;
    int ndKiek = stulpeliai - 3;
    if (ndKiek < 0) ndKiek = 0;

    if (numatomasKiekis > 0) studentai.reserve(numatomasKiekis);

    Studentas A;
    A.paz.resize(ndKiek);
    while (f >> A.var >> A.pav) {
        for (int i = 0; i < ndKiek; i++)
            f >> A.paz[i];
        f >> A.egz;

        apskaiciuoti(A);
        studentai.push_back(A);
    }

    return true;
}

void irasytiIFaila(const std::string& failoVardas, const std::vector<Studentas>& studentai)
{
    using namespace std;

    ofstream f(failoVardas);
    if (!f.is_open()) return;

    f << left << setw(16) << "Vardas" << setw(16) << "Pavarde" << "Galutinis (Vid.)\n";
    f << string(46, '-') << "\n";

    f << fixed << setprecision(2);
    for (const Studentas& s : studentai) {
        f << left << setw(16) << s.var << setw(16) << s.pav << s.vid << "\n";
    }
}
