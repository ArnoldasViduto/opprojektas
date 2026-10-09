#include "Studentas.h"
#include <algorithm>

void apskaiciuoti(Studentas& s)
{
    std::vector<int> visi = s.paz;
    visi.push_back(s.egz);

    int suma = 0;
    for (int p : visi) suma += p;
    s.vid = (double)suma / visi.size();

    std::sort(visi.begin(), visi.end());
    int n = visi.size();
    if (n % 2 == 0)
        s.med = (visi[n / 2 - 1] + visi[n / 2]) / 2.0;
    else
        s.med = visi[n / 2];
}
