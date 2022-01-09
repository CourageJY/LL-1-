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
        //1. 取每一个非终结符，遍历它的所有产生式。
        for (char cur_s: G.getVn()) {
            map<char, set<string>> P = G.getGr();
            //2. 每判断一个产生式：
            for (auto it1 = P[cur_s].begin(); it1 != P[cur_s].end(); it1++) {
                string cur_string = *it1;
                //  2.1 首先判断产生式右侧首符是不是终结符，如果是则直接加入first集。
                if (!isupper(cur_string[0])) {
                    FIRST[cur_s].insert(cur_string[0]);
                } else {
                    //2.2 如果产生式第一个为非终结符，就需要将该非终结符的first集加入到所求first集。
                    /*
                     * 2.3. 如果该非终结符的first集中含有空字，那需要加入顺位下一个字符的first集，直到遇到以下三种情况：
                            a. 遇到终结符；
                            b. 某个非终结符的first集不含空字；
                            c. 处理完右侧。
                     */
                    int count = 0; //count用来取产生式右侧的符号，如果遇到first集含有@的情况 则需要考虑下一位
                    char nxt_s;//当前判断的符号
                    int flag = 1;//这一层循环所取的符号first集是否有空，如果有就置为1，继续下一层循环。
                    while (flag == 1) {
                        flag = 0;//默认该符号如果是非终结符，则first集不含空字
                        nxt_s = cur_string[count]; //当前符号获取
                        if (!isupper(nxt_s)) FIRST[cur_s].insert(nxt_s);//遇到终结符 则直接加入
                        else //如果是非终结符，则加入其first集，并判断first集中是否有空字
                            for (auto it2 = FIRST[nxt_s].begin(); it2 != FIRST[nxt_s].end(); it2++) {
                                FIRST[cur_s].insert(*it2); //加入其first集
                                if ((*it2) == '@') {
                                    flag = 1;//发现first集含空字，应进行下一轮循环
                                }
                            }
                        count++;//下一轮循环取下一个字符，下标+1
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
        cout << "FIRST(" << cur_s << ")   ";
        for (char it1: FIRST[cur_s]) {
            cout << "       " << it1;
        }
        cout << endl;
    }
}

set<char> First::getSeqFirst(string seq) {
    set<char> ans;
    if (isupper(seq[0])) {//大写
        return FIRST[seq[0]];
    } else {//小写
        ans.insert(seq[0]);
        return ans;
    }
}