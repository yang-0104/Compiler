#include "compile.h"

void report_error(char ch)
{
    switch (ch)
    {
    case ' ':
        // printf("�ո�\n");
        break;
    case '\n':
        // printf("����\n");
        break;
    default:
        printf("�޷�ʶ��ķ��ţ�\"%c\"\n", ch);
        break;
    }
}

void report_error2(char *ch)
{
    printf("�޷�ʶ��%s\n", ch);
}