#pragma once

#include <map>
#include <set>
#include <string>
#include "Grammer.h"

using namespace std;

class First{
public:
    /**
     * 用以得到Follow集合的函数
     * 输入：文法Grammer
     * 输出：内部映射表FOLLOW
     */
    void getFollow(Grammer& G);

    //打印结果
    void printAns();
    
private:
    //用以储存FIRST集合的映射表
    map<char,set<char>> FOLLOW;

    friend class Table;

};