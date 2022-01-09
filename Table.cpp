#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Table.h"

void Table::getTable(Grammar &G, First &ft, Follow &fw) {

    map<char,set<char> > FIRST = ft.FIRST;
    map<char,set<char> >FOLLOW = fw.FOLLOW;
    set<char>Vn = G.Vn; // 非终结符
    set<char>Vt = G.Vt; // 终结符
    P=G.Gr;

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
}

void Table::printTable(Grammar& G){
    /*
        显示Table
    */
    const set<char>&Vn = G.getVn(); // 非终结符
    const set<char>&Vt = G.getVt(); // 终结符

    cout << "\n显示table表：" << endl;
    cout.setf(std::ios::left);
    for (auto it1 = Vt_temp.begin(); it1 != Vt_temp.end(); it1++) {
        if (it1 == Vt_temp.begin())cout << setw(10) << " ";
        cout << setw(10) << *it1;
    }
    cout << endl;
    for (char it : Vn) {
        for (auto it1 = Vt_temp.begin(); it1 != Vt_temp.end(); it1++) {
            string TableLeft;
            if (it1 == Vt_temp.begin())cout << setw(10) << it;
            TableLeft =TableLeft+ it + *it1;
            cout << it << "->" << setw(7) << Table[TableLeft];
        }
        cout << endl;
    }
}

bool Table::checkGrammar(Grammar& G,First& ft,Follow& fw) {
    //判断每个非终结符的first和follow是否有交集
    for(auto& v:G.Vn){
        //交集运算
        set<char> merge;
        set<char> first=ft.FIRST[v];
        set<char> follow=fw.FOLLOW[v];
        set_intersection(first.begin(),first.end(),
                         follow.begin(),follow.end(),
                         inserter(merge,merge.begin()));
        if(!merge.empty()){
            return false;
        }
    }

    //判断每个产生式的first之间是否有交集
    for(auto& v:G.Vn){
        for(auto it1=G.Gr[v].begin();it1!=G.Gr[v].end();it1++){
            for(auto it2=it1;it2!=G.Gr[v].end();){
                it2++;
                if(it2==G.Gr[v].end())break;//边界判断
                string str1=*it1;
                string str2=*it2;
                set<char> A=ft.getSeqFirst(str1);
                set<char> B=ft.getSeqFirst(str2);
                set<char> C;
                set_intersection(A.begin(),A.end(),
                                 B.begin(),B.end(),
                                 inserter(C,C.begin()));
                if(!C.empty()){
                    return false;
                }
            }
        }
    }
    return true;
}