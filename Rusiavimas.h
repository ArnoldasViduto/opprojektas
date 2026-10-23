#ifndef RUSIAVIMAS_H
#define RUSIAVIMAS_H

#include <vector>
#include <list>
#include <algorithm>
#include "Studentas.h"

// For Vector
void rusiuotiVektoriu(std::vector<Studentas>& studentai, char pagal);
void skirstytiVektoriu(std::vector<Studentas>& studentai, std::vector<Studentas>& silpni, std::vector<Studentas>& stiprus);

// For List (Notice we use std::list)
void rusiuotiSarasa(std::list<Studentas>& studentai, char pagal);
void skirstytiSarasa(std::list<Studentas>& studentai, std::list<Studentas>& silpni, std::list<Studentas>& stiprus);

#endif
