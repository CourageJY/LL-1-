#pragma once

#include <map>
#include <set>
#include <string>
#include "Grammar.h"

using namespace std;

class Follow{
public:
    /**
     * 用以得到Follow集合的函数
     * 输入：文法Grammar
     * 输出：内部映射表FOLLOW
     */
    void generateFollow(Grammar& G);

    //打印结果
    void printFollow(Grammar &G);

    const map<char, set<char>> &getFollow() const;

private:
    //用以储存FIRST集合的映射表
    map<char,set<char>> FOLLOW;

    friend class Table;

};