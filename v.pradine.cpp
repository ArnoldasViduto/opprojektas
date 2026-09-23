#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct studentas {
    std::string var, pav;
    std::vector<int> paz;
    int egz;
    double rez;
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

        int suma = A.egz;
        for (int p : A.paz) suma += p;
        A.rez = (double)suma / (ndKiek + 1);

        studentai.push_back(A);
    }

    cout << left << setw(16) << "Pavarde" << setw(16) << "Vardas" << "Galutinis (Vid.)\n";
    cout << string(46, '-') << "\n";

    cout << fixed << setprecision(2);
    for (studentas& s : studentai) {
        cout << left << setw(16) << s.pav << setw(16) << s.var << s.rez << "\n";
    }

    return 0;
}
