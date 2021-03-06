#include "First.h"
#include "Follow.h"
#include "Table.h"
#include "Analyse.h"
#include <iostream>

using namespace std;

int main(){
    Grammar G;
    //文法输入
    G.inputGrammar();
    cout<<"\n文法规格化后为：\n";
    G.printGrammar();

    //消除左递归
    cout<<"\n消除左递归后文法为：\n";
    G.removeLeftRecursion();
    G.printGrammar();

    //提取左公因子
    cout<<"\n消除左公因子后文法为：\n";
    G.removeLeftFactor();
    G.printGrammar();
    
    //计算first集合
    First first;
    first.generateFirst(G);
    first.printFirst(G);

    //计算follow集合
    Follow follow;
    follow.generateFollow(G);
    follow.printFollow(G);


    Table table;
    //判断是否已为LL(1)文法
    if(!table.checkGrammar(G,first,follow)){
        cout<<"\n当前文法还不是LL(1)文法\n";
        exit(1);
    }
    //计算预测分析表
    table.getTable(G,first,follow);
    table.printTable(G);

    //对输入的句子进行语法分析
    Analyse analyse;
    string seq;
    while(true){
        cout<<"\n请输入您想要分析的句子：(输入0结束)\n";
        cin>>seq;
        if(seq=="0")break;
        analyse.check(analyse.AnalyseSequence(G, table, seq));
    }
}