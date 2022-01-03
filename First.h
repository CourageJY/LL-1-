#pragma once

#include <map>
#include <set>
#include <string>
#include "Grammer.h"

using namespace std;

class First{
public:
    /**
     * 用以得到FIRST集合的函数
     * 输入：文法Grammer
     * 输出：内部映射表FIRST
     */
    void getFirst(Grammer& G);

    void printAns();
    
private:
    //用以储存FIRST集合的映射表
    map<char,set<char>> FIRST;

    friend class Table;
};