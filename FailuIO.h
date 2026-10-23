#ifndef FAILUIO_H
#define FAILUIO_H

#include <string>
#include <vector>
#include <list>
#include "Studentas.h"

// Nuskaitymas i VECTOR
bool skaitytiIsFailo(const std::string& failoVardas, std::vector<Studentas>& studentai, int numatomasKiekis = 0);
// Nuskaitymas i LIST
bool skaitytiIsFailo(const std::string& failoVardas, std::list<Studentas>& studentai, int numatomasKiekis = 0);

// Irasymas is VECTOR
void irasytiIFaila(const std::string& failoVardas, const std::vector<Studentas>& studentai);
// Irasymas is LIST
void irasytiIFaila(const std::string& failoVardas, const std::list<Studentas>& studentai);

#endif
