// #include "Analyse.h"

// bool Analyse::AnalyseSequence(Grammar &G, Table &T, string sq) {
//     /* 指向当前字符 */
//     int ip = 0;
//     /* 栈顶符号X， 和当前输入符号a */
//     char X, a;
//     printf("The answer:\n");
//     do{
//         X = ST.top();
//         a = str[ip];
//         /* 如果是终结符或者$ */
//         if (isInT(X)) {
//             /* 如果栈顶符号和当前符号匹配，出栈，指针前移 */
//             if (X == a) {
//                 ST.pop();
//                 ip = ip + 1;
//             } else { /* 不匹配报错 */
//                 printf("error1\n");
//             }
//         } else {    //非终结符
//             vector<char> s;
//             /* 取出对应预测分析表的项 */
//             //TODO
//             getFromForecastAnalysisTable(X, a, s);
//             /* 预测分析表项中有元素 */
//             if (!s.empty()) {
//                 /* 弹栈并将右部符号串逆序入栈 */
//                 ST.pop();
//                 for (int i = s.size() - 1; i >= 3; i--) {
//                     if (s[i] != '&') { // 为空时不入栈
//                         ST.push(s[i]);
//                     }
//                 }
//                 /* 输出产生式 */
//                 for (int i = 0; i < s.size(); i++) {
//                     printf("%c", s[i]);
//                 }
//                 printf("\n");
//             } else { // 空，报错
//                 printf("error2\n");
//             }
//         }
//     } while (X != '$');
// }

// /* 判断ch是否是终结符 */
// int Analyse::isInT(char ch)
// {
// //    //需要grammar
// //    for (int i = 0; i < grammar.T.size(); i++) {
// //        if (grammar.T[i] == ch) {
// //            return i + 1;
// //        }
// //    }
//     return 0;
// }