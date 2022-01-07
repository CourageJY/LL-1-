#pragma once

#include <map>
#include <set>
#include <string>

using namespace std;

class Grammar{
public:
    //用以处理文法输入的函数
    void inputGrammer();

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

    //用于存储文法的map映射表
    map<char,set<string>> Gr;

    friend class First;
    friend class Follow;
    friend class Table;
    friend class Analyse;
};