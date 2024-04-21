// #include "compile.h"
// #include "stack.h"

// extern void initGrammar();
// extern void initForm(const string &filename);
// // 文法分析表
// extern vector<Production> Grammars;
// // SLR1分析表
// extern vector<vector<string>> form;
// // 单词链表
// extern list<BinaryEquation> wordsList;

// // 状态栈
// Stack StateStack;
// // 符号栈
// Stack SymbolStack;

// // 单词链表的class向列index的映射
// //int map1[100];
// map<int, int> map1;
// // 非终结符的字符向列index的映射
// // int map2[100];
// map<int, char> map2;
// //遍历栈用
// map<int, string> map3;
// // int map3[100];

// void init_map1()
// {
//     map1[IF] = 0;
//     map1[WHILE] = 1;
//     map1[leftParenthesis] = 2;
//     map1[RightParenthesis] = 3;
//     map1[leftBrace] = 4;
//     map1[rightBrace] = 5;
//     map1[UnsignedNum] = 6;
//     map1[ID] = 6;
//     map1[IS] = 7;
//     map1[SEM] = 8;
//     map1[LT] = 9;
//     map1[GT] = 10;
//     map1[INT] = 11;
//     map1[FloatingPoint] = 11;
//     map1[ScientificNotation] = 11;
//     map1[PL] = 12;
//     map1[MI] = 13;
//     map1[MU] = 14;
//     map1[DI] = 15;
//     map1[pound] = 16;
// }
// // 非终结符映射列序号
// // #define S 17
// // #define A 18
// // #define B 19
// // #define C 20
// // #define D 21
// // #define G 22
// // #define K 23
// // #define E 24
// // #define T 25
// // #define F 26
// enum N_Symbol
// {
//     S = 17,
//     A,B,C,D,G,K,E,T,F,
// };
// void init_map2()
// {
//     map2['S'] = S;
//     map2['A'] = A;
//     map2['B'] = B;
//     map2['C'] = C;
//     map2['D'] = D;
//     map2['G'] = G;
//     map2['K'] = K;
//     map2['E'] = E;
//     map2['T'] = T;
//     map2['F'] = F;
// }
// void init_map3()
// {
//     // map3[pound] = '#';
//     // map3[leftParenthesis] = '(';
//     // map3[RightParenthesis] = ')';
//     // map3[PL] = '+';
//     // map3[MI] = '-';
//     // map3[MU] = '*';
//     // map3[DI] = '/';
//     // map3[UnsignedNum] = 'i';
//     // map3[INT] = 'i';
//     // map3[FloatingPoint] = 'i';
//     // map3[ScientificNotation] = 'i';
//     // map3[IF] = 'f';
//     // map3[WHILE] = 'w';
//     // map3[leftBrace] = '{';
//     // map3[rightBrace] = '}';
//     // map3[ID] = 'd';
//     // map3[IS] = '=';
//     // map3[SEM] = ';';
//     // map3[LT] = '<';
//     // map3[GT] = '>';

//     map3[pound] = "#";
//     map3[leftParenthesis] = "(";
//     map3[RightParenthesis] = ")";
//     map3[PL] = "+";
//     map3[MI] = "-";
//     map3[MU] = "*";
//     map3[DI] = "/";
//     map3[UnsignedNum] = "UnsignedNum";
//     map3[INT] = "UnsignedNum";
//     map3[FloatingPoint] = "UnsignedNum";
//     map3[ScientificNotation] = "UnsignedNum";
//     map3[IF] = "if";
//     map3[WHILE] = "while";
//     map3[leftBrace] = "{";
//     map3[rightBrace] = "}";
//     map3[ID] = "ID";
//     map3[IS] = "=";
//     map3[SEM] = ";";
//     map3[LT] = "<";
//     map3[GT] = ">";
// }

// void traverseStack(Stack *stack, bool isSymbol)
// {
//     if (isEmpty(stack))
//     {
//         printf("栈为空,遍历终止\n");
//         return;
//     }
//     for (int i = 0; i <= stack->top; i++)
//     {
//         if (isSymbol)
//             // printf("%c-", map3[stack->items[i]]);
//             printf("%s-", map3[stack->items[i]].c_str());
//         else
//             printf("%d-", stack->items[i]);
//     }
// }

// void Split(string str, char *action, int *state)
// {
//     *action = str[0];
//     *state = atoi(&str[1]);
// }

// void SLR1()
// {
//     // 初始化栈
//     initialize(&StateStack);
//     initialize(&SymbolStack);
//     // 将状态S0和#分别压入状态站和符号栈
//     push(&StateStack, 0);
//     push(&SymbolStack, pound);

//     init_map1();
//     init_map2();
//     init_map3();
//     initGrammar();
//     initForm("form.CSV");
//     // 索引指针指向链表头结点
//     auto p = wordsList.begin();
//     // 链表尾部添加‘#’
//     BinaryEquation data;
//     data.Class = pound;
//     wordsList.push_back(data);

//     char action;
//     int state;

//     string item;

//     int SerialNum = 1;

//     while (true)
//     {
//         printf("%d\t", SerialNum++);
//         traverseStack(&StateStack, false);
//         printf("\t\t");
//         traverseStack(&SymbolStack, true);
//         printf("\n");

//         item = form[peek_stack(&StateStack)][map1[p->Class]];
//         // printf("%d\t", SerialNum);
//         if (item == "")
//         {
//             printf("SLR1:Error\n");
//             break;
//         }
//         Split(item, &action, &state);
//         if (action == 's')
//         { // Sk
//             // 将ai入栈，并将分析状态转为K
//             push(&SymbolStack, p->Class);
//             push(&StateStack, state);
//             p++;
//         }
//         else if (action == 'r')
//         {
//             // 规约
//             int length = Grammars[state].right.size();
//             for (int i = 0; i < length; i++)
//             {
//                 pop(&SymbolStack);
//                 pop(&StateStack);
//             }
//             push(&SymbolStack, Grammars[state].left);
//             // 以状态栈和符号栈栈顶符号查goto分析表
//             item = form[peek_stack(&StateStack)][map2[peek_stack(&SymbolStack)]];
//             Split(item, &action, &state);
//             push(&StateStack, state);
//         }
//         else
//         {
//             printf("SLR1:Yes!\n");
//             break;
//         }
//     }
// }