#ifndef RUSIAVIMAS_H
#define RUSIAVIMAS_H

#include <vector>
#include "Studentas.h"

// surusiuoja studentus didejimo tvarka pagal galutini vidurki (std::sort)
void rusiuotiDidejimoTvarka(std::vector<Studentas>& studentai);

// padalina studentus i dvi grupes pagal galutini vidurki (< 5.0 ir >= 5.0)
// ir isvalo pradini studentai vektoriu
void skirstytiIDvi(std::vector<Studentas>& studentai,
                    std::vector<Studentas>& silpnesni,
                    std::vector<Studentas>& stipresni);

// surusiuoja studentus pagal naudotojo pasirinkta parametra:
// 'v' - varda, 'p' - pavarde, 'b' - galutini bala
void rusiuotiPagalLauka(std::vector<Studentas>& studentai, char pagal);

#endif
