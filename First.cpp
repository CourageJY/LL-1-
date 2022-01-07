#include "First.h"
#include <iostream>
using namespace std;
const map<char, set<char>> &First::getFirst() const {
    return FIRST;
}

void First::setFirst(const map<char, set<char>> &first) {
    FIRST = first;
}

void First::generateFirst(Grammar &G) {
    FIRST.clear();
    //判断迭代次数
    int iter = 4;
    while (iter--) {
        for (char cur_s : ) {
            /*
        cur_s->cur_string[0]
            a加到A的FIRST集
        cur_s->cur_string[0]
            B的FITRST集加到A的FIRST集
        */
            for (auto it1 = P[cur_s].begin(); it1 != P[cur_s].end(); it1++) {
                string cur_string = *it1;
                if (!isupper(cur_string[0])) {
                    FIRST[cur_s].insert(cur_string[0]);
                }
                else {
                    char nxt_s = cur_string[0];
                    for (auto it2 = FIRST[nxt_s].begin(); it2 != FIRST[nxt_s].end(); it2++) {
                        if ((*it2) != '@') {
                            FIRST[cur_s].insert(*it2);
                        }
                    }
                }
            }
        }
    }
    //输出FIRST集
    cout << "FIRST集为：" << endl << endl;
    for (char cur_s : Vn) {
        cout << "FIRST()   " << cur_s ;
        for (char it1 : FIRST[cur_s]) {
            cout<<"       " << it1 ;
        }
        cout << endl;
    }

}

void First::printFirst() {

}