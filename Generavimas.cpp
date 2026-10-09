#include "Generavimas.h"
#include <fstream>
#include <cstdlib>

void generuotiFaila(const std::string& failoVardas, int kiekis, int ndKiek)
{
    using namespace std;

    ofstream f(failoVardas);

    f << "Vardas Pavarde";
    for (int i = 1; i <= ndKiek; i++)
        f << " ND" << i;
    f << " Egz.\n";

    for (int i = 1; i <= kiekis; i++) {
        f << "Vardas" << i << " Pavarde" << i;
        for (int j = 0; j < ndKiek; j++)
            f << " " << (rand() % 10 + 1);
        f << " " << (rand() % 10 + 1) << "\n";
    }
}
