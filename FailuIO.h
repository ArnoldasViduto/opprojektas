#ifndef FAILUIO_H
#define FAILUIO_H

#include <string>
#include <vector>
#include "Studentas.h"

// nuskaito studentus is failo (grazina false, jei failo atidaryti nepavyko)
// numatomasKiekis - jei zinomas isankstinis studentu kiekis, naudojamas vektoriaus reserve()
bool skaitytiIsFailo(const std::string& failoVardas, std::vector<Studentas>& studentai, int numatomasKiekis = 0);

// israso studentu sarasa (Pavarde, Vardas, Galutinis (Vid.)) i faila
void irasytiIFaila(const std::string& failoVardas, const std::vector<Studentas>& studentai);

#endif
