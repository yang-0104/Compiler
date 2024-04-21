#include "compile.h"

void report_error(char ch)
{
    switch (ch)
    {
    case ' ':
        // printf("空格\n");
        break;
    case '\n':
        // printf("换行\n");
        break;
    default:
        printf("无法识别的符号：\"%c\"\n", ch);
        break;
    }
}

void report_error2(char *ch)
{
    printf("无法识别%s\n", ch);
}