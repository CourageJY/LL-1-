
#include "First.h"
#include "Follow.h"
#include "Table.h"
#include "Analyse.h"
#include "iostream"

using namespace std;

int main(){
    Grammar G;
    //文法输入
    G.inputGrammar();
    cout<<"文法规格化后为：\n";
    G.printGrammar();
    //消除左递归
    cout<<"\n消除左递归后文法为：\n";
    G.removeLeftRecursion();
    G.printGrammar();
    
    //计算first集合
    First first;
    first.generateFirst(G);
    first.printFirst(G);

    //计算follow集合
    Follow follow;
    follow.generateFollow(G);
    follow.printFollow(G);

    //计算预测分析表
    Table table;
    table.getTable(G,first,follow);
    table.printTable(G);

    //对输入的句子进行语法分析
    Analyse analyse;
    cout<<"\n请输入您想要分析的句子：\n";
    string seq;
    cin>>seq;
    analyse.check(analyse.AnalyseSequence(G, table, seq));


}