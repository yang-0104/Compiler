// #include "compile.h"
// // #include "stack.h"

// // 单词链表
// extern list<BinaryEquation> wordsList;
// // // 文法
// // extern vector<Production> Grammars;

// #define E 0
// #define e 1
// #define T 2
// #define t 3
// #define F 4
// #define A 5
// #define M 6

// // LL1分析表
// char *form[7][8];
// // map1
// int map1[120];
// // 分析栈
// stack<int> myStack;

// void init_map1()
// {
//     // ????form????????
//     map1[UnsignedNum] = 0;
//     map1[PL] = 1;
//     map1[MI] = 2;
//     map1[MU] = 3;
//     map1[DI] = 4;
//     map1[leftParenthesis] = 5;
//     map1[RightParenthesis] = 6;
//     map1[pound] = 7;
//     // form???????????????
//     map1['E'] = E;
//     map1['e'] = e;
//     map1['T'] = T;
//     map1['t'] = t;
//     map1['F'] = F;
//     map1['A'] = A;
//     map1['M'] = M;
//     map1['i'] = UnsignedNum;
//     map1['+'] = PL;
//     map1['-'] = MI;
//     map1['*'] = MU;
//     map1['/'] = DI;
//     map1['('] = leftParenthesis;
//     map1[')'] = RightParenthesis;
// }
// void init_form()
// {
//     for (int i = 0; i < 7; i++)
//     {
//         for (int j = 0; j < 8; j++)
//         {
//             form[i][j] = NULL;
//         }
//     }
//     form[E][map1[UnsignedNum]] = "Te";
//     form[E][map1[leftParenthesis]] = "Te";
//     form[e][map1[PL]] = "ATe";
//     form[e][map1[MI]] = "ATe";
//     form[e][map1[RightParenthesis]] = "";
//     form[e][map1[pound]] = "";
//     form[T][map1[UnsignedNum]] = "Ft";
//     form[T][map1[leftParenthesis]] = "Ft";
//     form[t][map1[PL]] = "";
//     form[t][map1[MI]] = "";
//     form[t][map1[MU]] = "MFt";
//     form[t][map1[DI]] = "MFt";
//     form[t][map1[RightParenthesis]] = "";
//     form[t][map1[pound]] = "";
//     form[F][map1[UnsignedNum]] = "i";
//     form[F][map1[leftParenthesis]] = "(E)";
//     form[A][map1[PL]] = "+";
//     form[A][map1[MI]] = "-";
//     form[M][map1[MU]] = "*";
//     form[M][map1[DI]] = "/";
// }

// //判断是否是终结符
// int isEndSymbol(int ch)
// {
//     return ch == PL || ch == MI || ch == MU || ch == DI || ch == UnsignedNum ||
//            ch == leftParenthesis || ch == RightParenthesis || ch == pound;
// }

// // 字符串反向入栈
// void StrReversePush(stack<int> &myStack, char *str)
// {
//     int cnt = strlen(str);
//     while (cnt > 0)
//     {
//         // push(myStack, map1[str[cnt - 1]]);
//         myStack.push(map1[str[cnt - 1]]);
//         cnt--;
//     }
// }

// void LL1()
// {
//     //#和E入栈
//     myStack.push(pound);
//     myStack.push(E);
    
//     auto p = wordsList.begin();
//     // 单词链表后面添加#
//     BinaryEquation data;
//     data.Class = pound;
//     wordsList.push_back(data);
//     // 初始化map1
//     init_map1();
//     // 初始化form表
//     init_form();
    
//     int xm, ai;
//     while (!((xm = myStack.top()) == pound & (ai = p->Class) == pound))
//     { //xm和ai不同时为#
//         // 将整形、浮点型、科学计数法统一成无符号数类型
//         if (ai == ScientificNotation || ai == FloatingPoint || ai == INT)
//             ai = UnsignedNum;
//         if (isEndSymbol(xm) && xm == ai)
//         { //xm为终结符且xm==ai
//             myStack.pop();
//             p++;
//         }
//         else
//         {
//             // Xm不是终结符或Xm, ai不等
//             // ????????Xm?Y1Y2??Yk????Xm?????Y1Y2??Yk?????????
//             if (!form[xm][map1[ai]])
//             {
//                 printf("LL1:error\n");
//                 return;
//             }
//             else
//             {
//                 myStack.pop();
//                 StrReversePush(myStack, form[xm][map1[ai]]);
//             }
//         }
//     }
//     printf("LL1:Yes!\n");
// }