#include "compile.h"
#include"stack.h"

extern vector<Production> Grammars;
extern void initGrammar();
void execute(int index, BinaryEquation *i);

// 单词链表
extern list<BinaryEquation> wordsList;

// // SLR1文法分析表
string form[100][100];

// 状态栈
Stack StateStack;
// 符号栈
Stack SymbolStack;

// 单词链表的class向列index的映射
int map1[100];
// 非终结符的字符向列index的映射
int map2[100];
// 实现分析过程可视化需要输出栈，将int类型的class转换为字符型输出
int map3[100];

//Equation Grammar[9];

void init_map1()
{
    map1[leftParenthesis] = 0;
    map1[RightParenthesis] = 1;
    map1[PL] = 2;
    map1[MI] = 3;
    map1[MU] = 4;
    map1[DI] = 5;
    map1[UnsignedNum] = 6;
    map1[INT] = 6;
    map1[FloatingPoint] = 6;
    map1[ScientificNotation] = 6;
    map1[pound] = 7;
}

#define E 8
#define T 9
#define F 10
void init_map2()
{
    map2['E'] = E;
    map2['T'] = T;
    map2['F'] = F;
}

void init_map3()
{
    map3[pound] = '#';
    map3[leftParenthesis] = '(';
    map3[RightParenthesis] = ')';
    map3[PL] = '+';
    map3[MI] = '-';
    map3[MU] = '*';
    map3[DI] = '/';
    map3[UnsignedNum] = 'i';
    map3[INT] = 'i';
    map3[FloatingPoint] = 'i';
    map3[ScientificNotation] = 'i';
}
// 0. E’→E 1. E→E + T 2. E→E - T 3. E→T 4. T→T *F
// 5. T→T / F 6. T→F 7. F→(E) 8. F→i
// Follow(E)={#，)，+，-}
// Follow(T)={#，)，+，-，*，/}
// Follow(F)={#，)，+，-，*，/}

// void init_Grammar()
// {
//     Grammar[1].left = E;
//     Grammar[1].right = "E+T";
//     Grammar[2].left = E;
//     Grammar[2].right = "E-T";
//     Grammar[3].left = E;
//     Grammar[3].right = "T";
//     Grammar[4].left = T;
//     Grammar[4].right = "T*F";
//     Grammar[5].left = T;
//     Grammar[5].right = "T/F";
//     Grammar[6].left = T;
//     Grammar[6].right = "F";
//     Grammar[7].left = F;
//     Grammar[7].right = "(E)";
//     Grammar[8].left = F;
//     Grammar[8].right = "i";
// }

 void init_form()
 {
     //initGrammarFromFile(form, rows, columns);
     for (int i = 0; i < 16; i++)
     {
         for (int j = 0; j < 11; j++)
         {
             form[i][j] = "";
         }
     }
     form[0][0] = "s4";
     form[0][6] = "s5";
     form[0][8] = "g1";
     form[0][9] = "g2";
     form[0][10] = "g3";

     form[1][2] = "s6";
     form[1][3] = "s7";
     form[1][7] = "acc";

     form[2][1] = "r3";
     form[2][2] = "r3";
     form[2][3] = "r3";
     form[2][4] = "s8";
     form[2][5] = "s9";
     form[2][7] = "r3";

     form[3][1] = "r6";
     form[3][2] = "r6";
     form[3][3] = "r6";
     form[3][4] = "r6";
     form[3][5] = "r6";
     form[3][7] = "r6";

     form[4][0] = "s4";
     form[4][6] = "s5";
     form[4][8] = "g10";
     form[4][9] = "g2";
     form[4][10] = "g3";

     form[5][1] = "r8";
     form[5][2] = "r8";
     form[5][3] = "r8";
     form[5][4] = "r8";
     form[5][5] = "r8";
     form[5][7] = "r8";

     form[6][0] = "s4";
     form[6][6] = "s5";
     form[6][9] = "g11";
     form[6][10] = "g3";

     form[7][0] = "s4";
     form[7][6] = "s5";
     form[7][9] = "g12";
     form[7][10] = "g3";

     form[8][0] = "s4";
     form[8][6] = "s5";
     form[8][10] = "g13";

     form[9][0] = "s4";
     form[9][6] = "s5";
     form[9][10] = "g14";

     form[10][1] = "s15";
     form[10][2] = "s6";
     form[10][3] = "s7";

     form[11][1] = "r1";
     form[11][2] = "r1";
     form[11][3] = "r1";
     form[11][4] = "s8";
     form[11][5] = "s9";
     form[11][7] = "r1";

     form[12][1] = "r2";
     form[12][2] = "r2";
     form[12][3] = "r2";
     form[12][4] = "s8";
     form[12][5] = "s9";
     form[12][7] = "r2";

     form[13][1] = "r4";
     form[13][2] = "r4";
     form[13][3] = "r4";
     form[13][4] = "r4";
     form[13][5] = "r4";
     form[13][7] = "r4";

     form[14][1] = "r5";
     form[14][2] = "r5";
     form[14][3] = "r5";
     form[14][4] = "r5";
     form[14][5] = "r5";
     form[14][7] = "r5";

     form[15][1] = "r7";
     form[15][2] = "r7";
     form[15][3] = "r7";
     form[15][4] = "r7";
     form[15][5] = "r7";
     form[15][7] = "r7";
 }

void traverseStack(Stack *stack,bool isSymbol)
{
    if (isEmpty(stack))
    {
        printf("栈为空,遍历终止\n");
        return;
    }
    for (int i = 0; i <= stack->top; i++)
    {
        if (isSymbol)
            printf("%c-", map3[stack->items[i]]);
        else
            printf("%d-", stack->items[i]);
    }
}

void Split(string str, char *action, int *state)
{
    *action = str[0];
    *state = atoi(&str[1]);
}

void SLR1()
{
    // 初始化栈
    initialize(&StateStack);
    initialize(&SymbolStack);
    // 将状态S0和#分别压入状态站和符号栈
    push(&StateStack, 0);
    push(&SymbolStack, pound);

    init_map1();
    init_map2();
    init_map3();

    initGrammar();
    init_form();
    // 索引指针指向链表头结点
    auto p=wordsList.begin();
    
    // 链表尾部添加‘#’
    BinaryEquation data;
    data.Class = pound;

    wordsList.push_back(data);

    char action;
    int state;

    string item;

    int SerialNum = 1;

    while (true)
    {
        printf("%d\t", SerialNum++);
        traverseStack(&StateStack,false);
        printf("\t\t");
        traverseStack(&SymbolStack,true);
        printf("\t\t");
        //printf("\n");

        item = form[peek_stack(&StateStack)][map1[p->Class]];

        if (item=="")
        {
            printf("Error\n");
            break;
        }
        Split(item, &action, &state);
        if (action == 's')
        { // Sk
            // 将ai入栈，并将分析状态转为K
        
            push(&SymbolStack, p->Class);
            push(&StateStack, state);
            p++;
        }
        else if (action == 'r')
        {
            // 规约
            int length = Grammars[state].right.size();

            for (int i = 0; i < length; i++)
            {
                pop(&SymbolStack);
                pop(&StateStack);
            }
            push(&SymbolStack, Grammars[state].left);

            //语义分析
            execute(state,&(*(prev(p))));
            
            //push(&SymbolStack, Grammars[state].left.symbol);
            // 以状态栈和符号栈栈顶符号查goto分析表
            item = form[peek_stack(&StateStack)][map2[peek_stack(&SymbolStack)]];
            Split(item, &action, &state);
            push(&StateStack, state);
            
        }
        else
        {
            printf("Yes!\n");
            break;
        }
        printf("\n");
    }
}