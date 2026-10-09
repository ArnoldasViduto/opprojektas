#include "Rusiavimas.h"
#include <algorithm>

void rusiuotiDidejimoTvarka(std::vector<Studentas>& studentai)
{
    std::sort(studentai.begin(), studentai.end(),
        [](const Studentas& a, const Studentas& b) { return a.vid < b.vid; });
}

void skirstytiIDvi(std::vector<Studentas>& studentai,
                    std::vector<Studentas>& silpnesni,
                    std::vector<Studentas>& stipresni)
{
    for (Studentas& s : studentai) {
        if (s.vid < 5.0)
            silpnesni.push_back(std::move(s));
        else
            stipresni.push_back(std::move(s));
    }

    studentai.clear();
    studentai.shrink_to_fit();
}

void rusiuotiPagalLauka(std::vector<Studentas>& studentai, char pagal)
{
    if (pagal == 'p')
        std::sort(studentai.begin(), studentai.end(),
            [](const Studentas& a, const Studentas& b) { return a.pav < b.pav; });
    else if (pagal == 'b')
        std::sort(studentai.begin(), studentai.end(),
            [](const Studentas& a, const Studentas& b) { return a.vid < b.vid; });
    else
        std::sort(studentai.begin(), studentai.end(),
            [](const Studentas& a, const Studentas& b) { return a.var < b.var; });
}
