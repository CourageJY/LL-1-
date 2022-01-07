#pragma once

#include <map>
#include <set>
#include <string>

using namespace std;

class Grammar {
public:
    //用以处理文法输入的函数
    void inputGrammar();

    //用以消除左递归的函数
    void removeLeftRecursion();

    //用以提取左公因子的函数
    void removeLeftFactor();

    //打印出LL(1)文法
    void printAns();

private:
    //开始符
    char S;

    //非终结符集合
    set<char> Vn;

    //终结符集合
    set<char> Vt;
public:
    char getS() const;

    void setS(char s);

    const set<char> &getVn() const;

    void setVn(const set<char> &vn);

    const set<char> &getVt() const;

    void setVt(const set<char> &vt);

    const map<char, set<string>> &getGr() const;

    void setGr(const map<char, set<string>> &gr);

private:
    //用于存储文法的map映射表
    map<char, set<string>> Gr;

    friend class First;

    friend class Follow;

    friend class Table;

    friend class Analyse;
};