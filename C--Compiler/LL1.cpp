// #include "compile.h"
// // #include "stack.h"

// // ��������
// extern list<BinaryEquation> wordsList;
// // // �ķ�
// // extern vector<Production> Grammars;

// #define E 0
// #define e 1
// #define T 2
// #define t 3
// #define F 4
// #define A 5
// #define M 6

// // LL1������
// char *form[7][8];
// // map1
// int map1[120];
// // ����ջ
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

// //�ж��Ƿ����ս��
// int isEndSymbol(int ch)
// {
//     return ch == PL || ch == MI || ch == MU || ch == DI || ch == UnsignedNum ||
//            ch == leftParenthesis || ch == RightParenthesis || ch == pound;
// }

// // �ַ���������ջ
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
//     //#��E��ջ
//     myStack.push(pound);
//     myStack.push(E);
    
//     auto p = wordsList.begin();
//     // ��������������#
//     BinaryEquation data;
//     data.Class = pound;
//     wordsList.push_back(data);
//     // ��ʼ��map1
//     init_map1();
//     // ��ʼ��form��
//     init_form();
    
//     int xm, ai;
//     while (!((xm = myStack.top()) == pound & (ai = p->Class) == pound))
//     { //xm��ai��ͬʱΪ#
//         // �����Ρ������͡���ѧ������ͳһ���޷���������
//         if (ai == ScientificNotation || ai == FloatingPoint || ai == INT)
//             ai = UnsignedNum;
//         if (isEndSymbol(xm) && xm == ai)
//         { //xmΪ�ս����xm==ai
//             myStack.pop();
//             p++;
//         }
//         else
//         {
//             // Xm�����ս����Xm, ai����
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