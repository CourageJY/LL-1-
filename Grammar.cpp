#include <iostream>
#include <cstring>
#include <vector>
#include "Grammar.h"

void Grammar::inputGrammar(){
    cout<<"请输入文法产生式：\n";
    //清空
    Vn.clear();
    Vt.clear();
    Gr.clear();
    //从控制台读入全部字符
    char *buffer = new char[maxnlen];
    cin.getline(buffer, maxnlen, '#');
    string temps = "";//用temp存储单个产生式
    bool is_sethead = 0; //判断是否为开始字符（默认第一个产生式的非终结符为开始字符）
    for (int i = 0; i < strlen(buffer); i++){
        if (buffer[i] == '\n' || buffer[i] == ' ')
            continue; //去除换行和空格
        if (buffer[i] == ';'){
            if (!is_sethead){ //填入开始符号
                this->setS(temps[0]);
                is_sethead = 1;
            }
            this->addProduction(temps);
            temps = "";//清空
        }
        else{
            temps += buffer[i];
        }
    }
    delete buffer;
}

void Grammar::addProduction(string s){
    char s1 = s[0];//终结符
    string s2 = "";//非终结符
    int num = 0;
    for (int i = 0; i < s.length(); i++){
        if (s[i] == '>')
            num = i;
        if (num == 0)
            continue;
        if (i > num)
            s2 += s[i];
    }
    s2 += ';';//结束标志
    Vn.insert(s1);//插入非终结符集合
    string temp = "";//按'|'拆分产生式
    for (char s : s2){
        if (!isupper(s) && s != '|' && s != ';' && s != '@')
            Vt.insert(s);//插入终结符集合
        if (s == '|' || s == ';'){
            Gr[s1].insert(temp);//插入文法
            temp = "";
        }
        else{
            temp += s;//字符拼接
        }
    }
}

void Grammar::printGrammar(){
    for (auto it = Vn.begin(); it != Vn.end(); it++){
        cout << *it << "->";
        char c = *it;//非终结符
        for (auto it1 = Gr[c].begin(); it1 != Gr[c].end(); it1++){
            if (it1 == Gr[c].begin())
                cout << *it1;//单个文法
            else
                cout << "|" << *it1;//拼接
        }
        cout << endl;//换行
    }
}

void Grammar::removeLeftRecursion(){
    string tempVn;//拼接所有非终结符
    for (char it : Vn){
        tempVn += it;
    }

    for (int i = 0; i < tempVn.length(); i++){//非终结符使用默认排序
        char pi = tempVn[i];
        set<string> NewPRight;
        for (auto it = Gr[pi].begin(); it != Gr[pi].end(); it++){
            bool isget = false;//判断序列前是否有非终结符与首字符匹配
            string right = *it;
            for (int j = 0; j < i; j++){//找到之前的非终结符
                char pj = tempVn[j];
                if (pj == right[0]){//判断该产生式首字母是否为非终结符
                    isget = true;
                    for (const auto & it1 : Gr[pj]){
                        string s = it1 + right.substr(1);//拼接从1开始的子串
                        NewPRight.insert(s);
                    }
                }
            }
            if (isget == 0){//未匹配
                NewPRight.insert(right);
            }
        }
        Gr[pi] = NewPRight;//更新产生式
        removeDirectLeftRecursion(pi);
    }
}

void Grammar::removeDirectLeftRecursion(char c){
    char NewVn=generateNewVn();//新终结符
    bool isaddNewVn = false;
    for (auto it = Gr[c].begin(); it != Gr[c].end(); it++) {
        string right = *it;
        if (right[0] == c) {
            isaddNewVn = true;
            break;
        }
    }
    if (isaddNewVn) {
        set<string> NewPRight;
        set<string> NewPNewVn;
        for (auto it = Gr[c].begin(); it != Gr[c].end(); it++) {
            string right = *it;
            if (right[0] != c) {
                right += NewVn;
                NewPRight.insert(right);
            } else {
                right = right.substr(1);
                right += NewVn;
                NewPNewVn.insert(right);
            }
        }
        Vn.insert(NewVn);
        NewPNewVn.insert("@");
        Gr[NewVn] = NewPNewVn;
        Gr[c] = NewPRight;
    }
}

//提取左公因子
void Grammar::removeLeftFactor(){
    string tempVn;//拼接所有非终结符
    for (char it : Vn){
        tempVn += it;
    }

    //全体产生式遍历
    for(int i=0;i<tempVn.length();){
        set<char> dup;//判重的集合
        bool isDup= false;//判断是否有公因子
        char c;//公共因子
        for(auto& s:Gr[tempVn[i]]){
            if(dup.count(s[0])){
                isDup= true;
                c=s[0];
                break;
            } else{
                dup.insert(s[0]);
            }
        }
        if(isDup){//有公因子
            char newVn=generateNewVn();//新非终结符
            Vn.insert(newVn);//插入
            tempVn+=newVn;//拼接
            vector<string> dels;//被删除的右部集
            for(auto& s:Gr[tempVn[i]]){
                if(s[0]==c){
                    dels.push_back(s);
                    Gr[newVn].insert(s.substr(1));//新非终结符插入
                }
            }
            for(auto& s:dels){//原非终结符删除
                Gr[tempVn[i]].erase(s);
            }
            string newRight;
            newRight+=c;
            newRight+=newVn;
            Gr[tempVn[i]].insert(newRight);//原非终结符插入新右部
        }
        else{//无公因子则继续遍历
            i++;
        }
    }

}

char Grammar::getS() const {
    return S;
}

void Grammar::setS(char s) {
    S = s;
}

char Grammar::generateNewVn() {
    char NewVn;
    for (int i = 0; i < 26; i++) {
        NewVn = i + 'A';
        if (!Vn.count(NewVn)) {
            break;
        }
    }
    return NewVn;
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