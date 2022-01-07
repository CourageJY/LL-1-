#pragma once

#include <map>
#include <set>
#include <string>
#include "Grammar.h"

using namespace std;

class First{
public:
    /**
     * 用以得到FIRST集合的函数
     * 输入：文法Grammar
     * 输出：内部映射表FIRST
     */
    void generateFirst(Grammar& G);

    void printFirst(Grammar &G);

    const map<char, set<char>> &getFirst() const;

private:
    //用以储存FIRST集合的映射表
    map<char,set<char>> FIRST;

    friend class Table;
};