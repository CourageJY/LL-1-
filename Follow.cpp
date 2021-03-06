#include <iostream>
#include "Follow.h"
#include "First.h"
using namespace std;


const map<char, set<char>> &Follow::getFollow() const {
    return FOLLOW;
}

void Follow::generateFollow(Grammar &G) {
    FOLLOW.clear();
    //1. 对于文法的开始符号S,置#于Follow（S）中；
    FOLLOW[G.getS()].insert('#');
    int iter = 4;
    auto *first = new First();
    first->generateFirst(G);
    auto FIRST = first->getFirst();
    while (iter--) {
        for (char cur_s: G.getVn()) {
            map<char, set<string>> P = G.getGr();
            for (auto it1 = P[cur_s].begin(); it1 != P[cur_s].end(); it1++) {
                string cur_string = *it1;
                for (int i = 0; i < cur_string.length() - 1; i++) {
                    /*
                     2. 若A->αBβ是一个产生式，则把First(β) \ {ε} 加入到Follow（B）中
                    */

                    //B->Ac 跟在后面的是终结符,将c加到A的follow集
                    if (isupper(cur_string[i]) && !isupper(cur_string[i + 1])) {
                        FOLLOW[cur_string[i]].insert(cur_string[i + 1]);
                    }
                    /*
                        B->AC
                        跟在后面的是一个非终结符,将C的first集加到A的follow集
                    */
                    if (isupper(cur_string[i]) && isupper(cur_string[i + 1])) {
                        //遍历C的first去除@，加到A的follow集
                        for (auto it2 = FIRST[cur_string[i + 1]].begin();
                             it2 != FIRST[cur_string[i + 1]].end(); it2++) {
                            if ((*it2) != '@')
                                FOLLOW[cur_string[i]].insert(*it2);
                        }
                    }

                }
                /*
                 * 3. 若A->αB是一个产生式，或A->αBβ是一个产生式且β=>ε，则把Follow(A)加入到Follow(B)中
                B->AC/ACK为最后两个或者三个
                B->AC
                B->ACK(K的first集含有@)
                将B的follow集加入到C的follow集
                */
                auto len = cur_string.length();
                if ((len >= 1 && isupper(cur_string[len - 1]))) {
                    for (auto it2 = FOLLOW[cur_s].begin(); it2 != FOLLOW[cur_s].end(); it2++) {
                        if (isupper(cur_string[len - 1]))
                            FOLLOW[cur_string[len - 1]].insert(*it2);
                    }
                }
                if ((len >= 2 && isupper(cur_string[len - 2]) && isupper(cur_string[len - 1]) &&
                     FIRST[cur_string[len - 1]].count('@') > 0)) {
                    for (auto it2 = FOLLOW[cur_s].begin(); it2 != FOLLOW[cur_s].end(); it2++) {
                        FOLLOW[cur_string[len - 2]].insert(*it2);
                    }
                }
            }
        }
    }
}

void Follow::printFollow(Grammar &G) {
    //输出FOLLOW集
    cout << "\nFOLLOW集为：" << endl;
    for (char cur_s : G.getVn()) {
        cout << "FOLLOW("<<cur_s << ")  ";
        for (char it1 : FOLLOW[cur_s]) {
            cout << "       " << it1;
        }
        cout << endl;
    }

}