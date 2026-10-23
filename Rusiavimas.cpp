#include "Rusiavimas.h"

// --- VECTOR LOGIC ---
void skirstytiVektoriu(std::vector<Studentas>& studentai, std::vector<Studentas>& silpni, std::vector<Studentas>& stiprus) {
    for (Studentas& s : studentai) {
        if (s.vid < 5.0) silpni.push_back(std::move(s));
        else stiprus.push_back(std::move(s));
    }
    studentai.clear();
}

void rusiuotiVektoriu(std::vector<Studentas>& studentai, char pagal) {
    auto compare = [pagal](const Studentas& a, const Studentas& b) {
        if (pagal == 'p') return a.pav < b.pav;
        if (pagal == 'b') return a.vid < b.vid;
        return a.var < b.var;
    };
    std::sort(studentai.begin(), studentai.end(), compare);
}

// --- LIST LOGIC ---
void skirstytiSarasa(std::list<Studentas>& studentai, std::list<Studentas>& silpni, std::list<Studentas>& stiprus) {
    for (Studentas& s : studentai) {
        if (s.vid < 5.0) silpni.push_back(std::move(s));
        else stiprus.push_back(std::move(s));
    }
    studentai.clear();
}

void rusiuotiSarasa(std::list<Studentas>& studentai, char pagal) {
    auto compare = [pagal](const Studentas& a, const Studentas& b) {
        if (pagal == 'p') return a.pav < b.pav;
        if (pagal == 'b') return a.vid < b.vid;
        return a.var < b.var;
    };
    // Note: std::list has its own .sort() method!
    studentai.sort(compare); 
}
