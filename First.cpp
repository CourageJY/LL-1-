#include "First.h"
#include <iostream>

using namespace std;

const map<char, set<char>> &First::getFirst() const {
    return FIRST;
}

void First::generateFirst(Grammar &G) {
    FIRST.clear();
    //判断迭代次数
    int iter = 4;
    while (iter--) {
        for (char cur_s: G.getVn()) {
            /*
            A -> a
            a加到A的FIRST集
            A -> B
            B的FIRST集加到A的FIRST集
            */
            map<char, set<string>> P = G.getGr();
            for (auto it1 = P[cur_s].begin(); it1 != P[cur_s].end(); it1++) {
                string cur_string = *it1;
                if (!isupper(cur_string[0])) {
                    FIRST[cur_s].insert(cur_string[0]);
                } else {
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
}

void First::printFirst(Grammar &G) {
    //输出FIRST集
    cout << "\nFIRST集为：" << endl;
    for (char cur_s: G.getVn()) {
        cout << "FIRST("<<cur_s << ")   ";
        for (char it1: FIRST[cur_s]) {
            cout << "       " << it1;
        }
        cout << endl;
    }
}