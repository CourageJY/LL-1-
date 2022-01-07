#pragma once

#include <map>
#include <set>
#include <string>
#include <Grammar.h>
#include <First.h>
#include <Follow.h>

using namespace std;

class Table{
public:
    /**
     * @brief Get the Table object
     * 
     * @param G 文法
     * @param ft first集
     * @param fw follow集
     */
    void getTable(Grammar& G,First& ft,Follow& fw);

private:
    /**
     * 用以储存分析预测表的map
     * key:由终结符+非终结符组合而成
     * value:key所对应的文法
     */
    map<string,string> Table;

    //may be public
    set<char>Vt_temp;

    map<char, set<string> > P; //
    
    friend class Analyse;
};









