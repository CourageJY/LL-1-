#include "Grammar.h"

char Grammar::getS() const {
    return S;
}

void Grammar::setS(char s) {
    S = s;
}

const set<char> &Grammar::getVn() const {
    return Vn;
}

void Grammar::setVn(const set<char> &vn) {
    Vn = vn;
}

const set<char> &Grammar::getVt() const {
    return Vt;
}

void Grammar::setVt(const set<char> &vt) {
    Vt = vt;
}

const map<char, set<string>> &Grammar::getGr() const {
    return Gr;
}

void Grammar::setGr(const map<char, set<string>> &gr) {
    Gr = gr;
}


