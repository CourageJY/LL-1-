 #include "Analyse.h"

 bool Analyse::AnalyseSequence(Grammar &G, Table &T, string sq) {
     sq += '#';
     ST.push('#');
     ST.push(G.S);
     /* 指向当前字符 */
     int ip = 0;
     /* 栈顶符号X， 和当前输入符号a */
     char X, a;
     cout<<"\n推导过程所用产生式:\n";
     X = ST.top();
     while (X != '#'){
         a = sq[ip];
         /* 如果是终结符或者 # */
         if (isInT(X,G)) {
             /* 如果栈顶符号和当前符号匹配，出栈，指针前移 */
             if (X == a) {
                 ST.pop();
                 ip = ip + 1;
             } else { /* 不匹配报错 */
                 cout<<"error for not match\n";
                 return false;
             }
         } else {    //非终结符
             string s;
             /* 取出对应预测分析表的项 */
             //TODO
             getFromTable(X, a, s, T);
             /* 预测分析表项中有元素 */
             if (!s.empty()) {
                 /* 弹栈并将右部符号串逆序入栈 */
                 char top = ST.top();
                 ST.pop();
//                 cout<<s;
                 for (int i = s.size() - 1; i >= 0; i--) {
                     if (s[i] != '@') { // 为空时不入栈
                         ST.push(s[i]);
                     }
                 }
                 /* 输出产生式 */
                 cout<<top<<"->" << setw(7) << s <<endl;
//                 for (int i = 0; i < s.size(); i++) {
//                     printf("%c", s[i]);
//                 }
             } else { // 空，报错
                 cout<<"error\n";
                 return false;
             }
         }
         X = ST.top();
     }
     return true;
 }


 /* 判断ch是否是终结符 */
 bool Analyse::isInT(char ch,Grammar &G)
 {
     for (set<char>::iterator i = G.Vt.begin(); i!=G.Vt.end(); i++) {
//         cout<< (*i) <<endl;
         if ( (*i) == ch) {
             return true;
         }
     }
     return false;
 }

 /* 取出预测分析表对应的项中的产生式 */
 void Analyse::getFromTable(char A, char a, string &s,Table &T)
 {
     string tableLeft="";
     tableLeft=tableLeft+A+a;
     s = T.Table[tableLeft];
 }

 void Analyse::check(bool b){
     if(b){
         cout<<"识别成功"<<endl;
     }
     else cout<<"识别失败"<<endl;

 }