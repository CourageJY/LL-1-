#include <iostream>
#include <iomanip>
#include "Table.h"

void Table::getTable(Grammar &G, First &ft, Follow &fw) {

    map<char,set<char> >FIRST = ft.getFirst();
    map<char,set<char> >FOLLOW = fw.getFollow();
    set<char>Vn = Grammar().getVn(); // 非终结符
    set<char>Vt = Grammar().getVt(); // 终结符

    for (char c : Vt) {
        Vt_temp.insert(c);
    }
    Vt_temp.insert('#');
    for (auto it = Vn.begin(); it != Vn.end(); it++) {
        char cur_s = *it;
        for (auto it1 = P[cur_s].begin(); it1 != P[cur_s].end(); it1++) {
            /*
            产生式为
                cur_s->cur_string
            */
            string cur_string = *it1;
            if (isupper(cur_string[0])) {
                char first_s = cur_string[0];
                for (auto it2 = FIRST[first_s].begin(); it2 != FIRST[first_s].end(); it2++) {
                    string TableLeft = "";
                    TableLeft = TableLeft +cur_s + *it2;
                    Table[TableLeft] = cur_string;
                }

            }
            else {
                string TableLeft = "";
                TableLeft = TableLeft+ cur_s + cur_string[0];
                Table[TableLeft] = cur_string;
            }
        }
        if (FIRST[cur_s].count('@') > 0) {
            for (auto it1 = FOLLOW[cur_s].begin(); it1 != FOLLOW[cur_s].end(); it1++) {
                string TableLeft = "";
                TableLeft =TableLeft+ cur_s + *it1;
                Table[TableLeft] = "@";
            }
        }
    }
    /*
        检查出错信息：即表格中没有出现过的
    */


    for (auto it = Vn.begin(); it != Vn.end(); it++) {
        for (auto it1 = Vt_temp.begin(); it1 != Vt_temp.end(); it1++) {
            string TableLeft = "";
            TableLeft =TableLeft+ *it + *it1;
            if (!Table.count(TableLeft)) {
                Table[TableLeft] = "error";
            }
        }
    }

    /*
        显示Table
    */
    cout << "显示table表：" << endl << endl;
    cout.setf(std::ios::left);
    for (auto it1 = Vt_temp.begin(); it1 != Vt_temp.end(); it1++) {
        if (it1 == Vt_temp.begin())cout << setw(10) << " ";
        cout << setw(10) << *it1;
    }
    cout << endl;
    for (auto it = Vn.begin(); it != Vn.end(); it++) {
        for (auto it1 = Vt_temp.begin(); it1 != Vt_temp.end(); it1++) {
            string TableLeft="";
            if (it1 == Vt_temp.begin())cout << setw(10) << *it;
            TableLeft =TableLeft+ *it + *it1;
            cout << *it << "->" << setw(7) << Table[TableLeft];
        }
        cout << endl;
    }
}