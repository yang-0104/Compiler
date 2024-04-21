#include"compile.h"

//单词二元式链表
list<BinaryEquation> wordsList;


void printList()
{
    for (auto it = wordsList.begin();it!=wordsList.end();it++) {
        if (it->Class!=INT&&it->Class!=FloatingPoint&&it->Class!=ScientificNotation)
            printf("(%d,%s)\n", it->Class, it->Value);
        else
            printf("(%d,%.2f)\n", it->Class, it->Num);
    }
}

void out(int c, const char *value)
{
    BinaryEquation data;
    data.Class = c;
    char *ch = (char *)malloc(sizeof(char) * MAX_WORD_LENGTH);
    strcpy(ch, value);
    data.Value = ch;
    wordsList.push_back(data);
}

void out_numValue(int c, double value)
{
    BinaryEquation data;
    data.Class = c;
    data.Num = value;
    data.Value = NULL;
    wordsList.push_back(data);
}