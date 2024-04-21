#include"compile.h"

int CurrentState = 0;
int Index = 0;
double value1;
double value2;
double value3;
double value4;
double value;
int flag = 1;
int cnt = 0;

char TOKEN[20];

extern void out(int, const char *);
extern void out_numValue(int, double);
extern int report_error(char);
extern int report_error2(char *);
extern int lookup(char *);

int IsCharacterAtLineBegin(FILE *fp)
{ // 判断字符是否在行首
    // 判断是否在全文的首
    if (ftell(fp) == 1)
        return 1;
    fseek(fp, -2, 1);
    if (fgetc(fp) == '\n')
    {
        // 恢复原位置
        fseek(fp, 1, 1);
        return 1;
    }
    // 恢复原位置
    fseek(fp, 1, 1);
    return 0;
}

void scanner_example(FILE *fp, int state, int *index)
{
    char ch;
    int c;
    ch = fgetc(fp);
    switch (state)
    {
    case 0:
        if (isalpha(ch))
        {
            TOKEN[*index] = ch;
            (*index)++;
            CurrentState = 1;
        }
        else if (isdigit(ch))
        {
            TOKEN[*index] = ch;
            (*index)++;
            CurrentState = 3;
            value1 = ch - '0';
        }
        else
        {
            switch (ch)
            {
            case '.':
                TOKEN[*index] = ch;
                (*index)++;
                CurrentState = 11;
                break;
            case '<':
                CurrentState = 12;
                break;
            case '=':
                CurrentState = 16;
                break;
            case '>':
                CurrentState = 19;
                break;
            case '+':
                CurrentState = 22;
                break;
            case '-':
                CurrentState = 23;
                break;
            case '*':
                CurrentState = 24;
                break;
            case '/':
                CurrentState = 25;
                break;
            case '"':
                CurrentState = 26;
                break;
            case '(':
                CurrentState = 28;
                break;
            case ')':
                CurrentState = 29;
                break;
            case ';':
                CurrentState = 30;
                break;
            case '{':
                CurrentState = 31;
                break;
            case '}':
                CurrentState = 32;
                break;
            case '#':
                // 删除注释内容
                // 判断是否在一行的第一个符号
                if (IsCharacterAtLineBegin(fp))
                {
                    ch = fgetc(fp);
                    while (ch != '\n' && ch != EOF)
                        ch = fgetc(fp);
                }
                else
                {
                    report_error(ch);
                    CurrentState = 0;
                    *index = 0;
                }
                break;
            default:
                report_error(ch);
                CurrentState = 0;
                *index = 0;
                break;
            }
        }
        break;
    case 1:
        if (isalpha(ch) || isdigit(ch))
        {
            TOKEN[*index] = ch;
            (*index)++;
            CurrentState = 1;
        }
        else
        {
            fseek(fp, -1, SEEK_CUR);
            CurrentState = 2;
        }
        break;
    case 2:
        TOKEN[*index] = '\0';
        c = lookup(TOKEN);
        if (c == 0)
            out(ID, TOKEN);
        else
            out(c, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        *index = 0;
        break;
    case 3:
        if (isdigit(ch))
        {
            TOKEN[*index] = ch;
            (*index)++;
            CurrentState = 3;
            value1 = value1 * 10 + (ch - '0');
        }
        else
        {
            switch (ch)
            {
            case '.':
                TOKEN[*index] = ch;
                (*index)++;
                CurrentState = 5;
                break;
            case 'E':
                TOKEN[*index] = ch;
                (*index)++;
                CurrentState = 7;
                break;
            default:
                fseek(fp, -1, SEEK_CUR);
                CurrentState = 4;
                break;
            }
        }
        break;
    case 4:
        TOKEN[*index] = '\0';
        // out(INT, TOKEN);
        // printf("%f\n", value1);
        out_numValue(INT, value1);
        value1 = 0;
        // report_error(ch);
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        *index = 0;
        break;
    case 5:
        if (isdigit(ch))
        {
            TOKEN[*index] = ch;
            (*index)++;
            CurrentState = 5;
            cnt++;
            value2 = value2 + (ch - '0') * pow(10, -cnt);
            // value3 = value1 + value2;
        }
        else
        {
            switch (ch)
            {
            case 'E':
                TOKEN[*index] = ch;
                (*index)++;
                CurrentState = 7;
                // value3 = value1 + value2;
                break;
            default:
                fseek(fp, -1, SEEK_CUR);
                CurrentState = 6;
                break;
            }
        }
        break;
    case 6:
        TOKEN[*index] = '\0';
        value3 = value1 + value2;
        out_numValue(FloatingPoint, value3);
        value1 = value2 = value3 = cnt = 0;
        // report_error(ch);
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        *index = 0;
        break;
    case 7:
        // value3 = value1 + value2;
        switch (ch)
        {
        case '+':
            TOKEN[*index] = ch;
            (*index)++;
            CurrentState = 8;
            break;
        case '-':
            TOKEN[*index] = ch;
            (*index)++;
            CurrentState = 8;
            flag = 0;
            break;
        default:
            if (isdigit(ch))
            {
                TOKEN[*index] = ch;
                (*index)++;
                CurrentState = 9;
                value4 = ch - '0';
            }
            else
            {
                TOKEN[*index] = ch;
                (*index)++;
                TOKEN[*index] = '\0';
                report_error2(TOKEN);
                report_error(ch);
                CurrentState = 0;
                *index = 0;
            }
            break;
        }
        break;
    case 8:
        if (isdigit(ch))
        {
            TOKEN[*index] = ch;
            (*index)++;
            CurrentState = 9;
            value4 += value4 * 10 + (ch - '0');
        }
        else
        {
            TOKEN[*index] = ch;
            (*index)++;
            TOKEN[*index] = '\0';
            report_error2(TOKEN);
            report_error(ch);
            CurrentState = 0;
            *index = 0;
        }
        break;
    case 9:
        if (isdigit(ch))
        {
            TOKEN[*index] = ch;
            (*index)++;
            CurrentState = 9;
            // value3 = value1 + value2;
            value4 += value4 * 10 + (ch - '0');
        }
        else
        {
            fseek(fp, -1, SEEK_CUR);
            CurrentState = 10;
            break;
        }
        break;
    case 10:
        TOKEN[*index] = '\0';
        // out(ScientificNotation, TOKEN);
        // report_error(ch);
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        *index = 0;
        value3 = value1 + value2;
        if (flag == 1)
            value = value3 * pow(10, value4);
        else if (flag == 0)
            value = value3 * pow(10, -value4);
        else
            printf("Error!\n");
        // printf("%f\n", value);
        out_numValue(ScientificNotation, value);
        value1 = value2 = value3 = value4 = cnt = 0;
        flag = 1;
        break;
    case 11:
        if (isdigit(ch))
        {
            TOKEN[*index] = ch;
            (*index)++;
            CurrentState = 5;
            cnt++;
            value2 = value2 + (ch - '0') * pow(10, -cnt);
        }
        else
        {
            TOKEN[*index] = ch;
            (*index)++;
            TOKEN[*index] = '\0';
            report_error2(TOKEN);
            // report_error(ch);
            CurrentState = 0;
            *index = 0;
        }
        break;
    case 12:
        switch (ch)
        {
        case '=':
            CurrentState = 13;
            break;
        case '>':
            CurrentState = 14;
            break;
        default:
            CurrentState = 15;
            fseek(fp, -1, SEEK_CUR);
            break;
        }
        break;
    case 13:
        out(LE, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 14:
        out(NE, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 15:
        // 
        out(LT, " ");
        fseek(fp, -1, SEEK_CUR);
        //report_error(ch);
        CurrentState = 0;
        break;
    case 16:
        switch (ch)
        {
        case '=':
            CurrentState = 17;
            break;
        default:
            fseek(fp, -1, SEEK_CUR);
            CurrentState = 18;
            break;
        }
        break;
    case 17:
        out(EQ, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 18:
        out(IS, " ");
        fseek(fp, -1, SEEK_CUR);
        //report_error(ch);
        CurrentState = 0;
        break;
    case 19:
        switch (ch)
        {
        case '=':
            CurrentState = 20;
            break;
        default:
            CurrentState = 21;
            fseek(fp, -1, SEEK_CUR);
            break;
        }
        break;
    case 20:
        out(GE, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 21:
        // fseek(fp, -1, SEEK_CUR);
        out(GT, " ");
        fseek(fp, -1, SEEK_CUR);
        //report_error(ch);
        CurrentState = 0;
        break;
    case 22:
        out(PL, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 23:
        out(MI, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 24:
        out(MU, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 25:
        out(DI, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 26:
        switch (ch)
        {
        case '"':
            fseek(fp, -1, SEEK_CUR);
            CurrentState = 27;
            break;
        default:
            TOKEN[*index] = ch;
            (*index)++;
            CurrentState = 26;
            break;
        }
        break;
    case 27:
        TOKEN[*index] = '\0';
        out(STR, TOKEN);
        // fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        *index = 0;
        break;
    case 28:
        out(leftParenthesis, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 29:
        out(RightParenthesis, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 30:
        out(SEM, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 31:
        out(leftBrace, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    case 32:
        out(rightBrace, " ");
        fseek(fp, -1, SEEK_CUR);
        CurrentState = 0;
        break;
    default:
        printf("异常状态！\n");
        // fseek(fp, -1, SEEK_CUR);
        // CurrentState = 0;
        // report_error(ch);
        break;
    }
}
