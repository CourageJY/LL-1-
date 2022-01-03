#pragma once

#include <map>
#include <set>
#include <string>
#include <Grammer.h>
#include <First.h>
#include <Follow.h>

use namespace std;

class Table{
public:
    /**
     * @brief Get the Table object
     * 
     * @param G 文法
     * @param ft first集
     * @param fw follow集
     */
    void getTable(Grammer& G,First& ft,First& fw);

private:
    /**
     * 用以储存分析预测表的map
     * key:由终结符+非终结符组合而成
     * value:key所对应的文法
     */
    map<string,string> Table;
    
    friend class Analyse;
}