#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

struct Studentas {
    std::string var, pav;
    std::vector<int> paz;
    int egz;
    double vid;
    double med;
};

// apskaiciuoja studento vidurki (vid) ir mediana (med)
// is jo namu darbu pazymiu (paz) ir egzamino (egz)
void apskaiciuoti(Studentas& s);

#endif
