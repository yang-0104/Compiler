#include"compile.h"    //必写，其实就是c的#include <stdio.h>

extern int CurrentState;
extern int Index;
extern void scanner_example(FILE *fp, int state, int *index);
extern void printList();
void printIntermediateCode();
//extern Node *head;
extern list<BinaryEquation> wordsList;
extern void LL1();
extern void SLR1();

void Compile(FILE *fp)
{
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        fseek(fp, -1, 1);
        scanner_example(fp, CurrentState, &Index);
    }
}

int main()
{
    FILE *fp = fopen("program.txt", "r");
    Compile(fp);
    printList();
    //LL1();
    SLR1();
    printIntermediateCode();
    return 0;
}
