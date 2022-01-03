#pragma once

#include <map>
#include <set>
#include <string>
#include "Grammer.h"
#include "Table.h"

using namespace std;

class Analyse{
public:
    /**
     * @brief 根据文法和分析表判断是否能识别一个句子，并打印出分析过程
     * 
     * @param G 文法
     * @param T 分析表
     * @return true 判断成功，并打印出分析过程（涉及到的文法序列）
     * @return false 判断失败
     */
    bool AnalyseSequence(Grammer& G,Table& T,string sq);

private:

};