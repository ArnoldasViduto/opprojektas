#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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

int skaitytiPazymi(const std::string& prompt)
{
    using namespace std;
    int n;
    while (true) {
        cout << prompt;
        if (cin >> n && n >= 1 && n <= 10) return n;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Klaida: pazymys turi buti sveikas skaicius nuo 1 iki 10.\n";
    }
}

int skaitytiTeigiamaSkaiciu(const std::string& prompt)
{
    using namespace std;
    int n;
    while (true) {
        cout << prompt;
        if (cin >> n && n > 0) return n;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Klaida: iveskite teigiama sveika skaiciu.\n";
    }
}

bool skaitytiIsFailo(std::vector<studentas>& studentai)
{
    using namespace std;

    ifstream f("kursiokai.txt");
    if (!f.is_open()) {
        cout << "Klaida: nepavyko atidaryti failo kursiokai.txt\n";
        return false;
    }

    string antraste;
    if (!getline(f, antraste)) {
        cout << "Klaida: failas yra tuscias\n";
        return false;
    }

    istringstream is(antraste);
    string zodis;
    int stulpeliai = 0;
    while (is >> zodis) stulpeliai++;

    if (stulpeliai < 4) {
        cout << "Klaida: neteisingas failo formatas (per mazai stulpeliu)\n";
        return false;
    }
    int ndKiek = stulpeliai - 3;

    studentas A;
    while (f >> A.var >> A.pav) {
        A.paz.assign(ndKiek, 0);

        bool ok = true;
        for (int i = 0; i < ndKiek; i++) {
            if (!(f >> A.paz[i])) { ok = false; break; }
        }
        if (ok && !(f >> A.egz)) ok = false;

        if (!ok) {
            cout << "Klaida: neteisingas failo formatas (truksta duomenu)\n";
            return false;
        }

        apskaiciuoti(A);
        studentai.push_back(A);
    }

    if (studentai.empty()) {
        cout << "Klaida: faile nera studentu duomenu\n";
        return false;
    }

    return true;
}

void ivestiRankiniu(std::vector<studentas>& studentai)
{
    using namespace std;

    studentas A;

    cout << "Vardas: ";
    cin >> A.var;
    cout << "Pavarde: ";
    cin >> A.pav;

    char darPaz;
    do {
        int n = skaitytiPazymi("Namu darbo pazymys: ");
        A.paz.push_back(n);

        cout << "Ar yra dar pazymiu? (t/n): ";
        cin >> darPaz;
        while (darPaz != 't' && darPaz != 'T' &&
               darPaz != 'n' && darPaz != 'N') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Klaida: atsakykite t arba n: ";
            cin >> darPaz;
        }
    } while (darPaz == 't' || darPaz == 'T');

    A.egz = skaitytiPazymi("Egzaminas: ");

    apskaiciuoti(A);
    studentai.push_back(A);
}

void generuotiAtsitiktinai(std::vector<studentas>& studentai)
{
    using namespace std;

    int kiek = skaitytiTeigiamaSkaiciu("Kiek studentu generuoti? ");
    int ndKiek = skaitytiTeigiamaSkaiciu("Kiek namu darbu pazymiu kiekvienam? ");

    for (int i = 0; i < kiek; i++) {
        studentas A;
        A.var = "Vardas" + to_string(studentai.size() + 1);
        A.pav = "Pavarde" + to_string(studentai.size() + 1);

        for (int j = 0; j < ndKiek; j++)
            A.paz.push_back(rand() % 10 + 1);

        A.egz = rand() % 10 + 1;

        apskaiciuoti(A);
        studentai.push_back(A);
    }
}

void rodytiRezultatus(std::vector<studentas>& studentai)
{
    using namespace std;

    char pasirinkimas;
    cout << "Vidurki (v), mediana (m) ar abu (a)? ";
    cin >> pasirinkimas;

    while (pasirinkimas != 'v' && pasirinkimas != 'V' &&
           pasirinkimas != 'm' && pasirinkimas != 'M' &&
           pasirinkimas != 'a' && pasirinkimas != 'A') {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Klaida: pasirinkimas turi buti v, m arba a. Bandykite dar karta: ";
        cin >> pasirinkimas;
    }

    if (pasirinkimas == 'V') pasirinkimas = 'v';
    if (pasirinkimas == 'M') pasirinkimas = 'm';
    if (pasirinkimas == 'A') pasirinkimas = 'a';

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
}

int main()
{
    using namespace std;
    srand((unsigned)time(0));

    vector<studentas> studentai;
    int pasirinkimas;

    cout << "1 - skaityti is failo\n";
    cout << "2 - ivesti rankiniu budu\n";
    cout << "3 - generuoti atsitiktinai\n";
    cout << "Pasirinkimas: ";
    cin >> pasirinkimas;

    while (cin.fail() || pasirinkimas < 1 || pasirinkimas > 3) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Klaida: pasirinkimas turi buti 1, 2 arba 3. Bandykite dar karta: ";
        cin >> pasirinkimas;
    }

    if (pasirinkimas == 1) {
        if (!skaitytiIsFailo(studentai)) return 1;
    }
    else if (pasirinkimas == 2) {
        char dar;
        do {
            ivestiRankiniu(studentai);
            cout << "Ar ivesti dar viena studenta? (t/n): ";
            cin >> dar;
            while (dar != 't' && dar != 'T' && dar != 'n' && dar != 'N') {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Klaida: atsakykite t arba n: ";
                cin >> dar;
            }
        } while (dar == 't' || dar == 'T');
    }
    else if (pasirinkimas == 3) {
        generuotiAtsitiktinai(studentai);
    }

    rodytiRezultatus(studentai);

    return 0;
}
