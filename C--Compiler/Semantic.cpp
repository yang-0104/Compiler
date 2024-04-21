#include"compile.h"

extern map<char, BinaryEquation *> PlaceMap;

ostream &operator<<(ostream &os, const BinaryEquation &binaryEquation)
{
    if (binaryEquation.Class == INT || binaryEquation.Class == FloatingPoint || binaryEquation.Class == ScientificNotation || binaryEquation.Class == UnsignedNum)
        os << binaryEquation.Num;
    else
        os << binaryEquation.Value;
    return os;
}

struct Quaternion
{
    char op;
    BinaryEquation *arg1;
    BinaryEquation *arg2;
    BinaryEquation *result;
};

//中间代码
vector<Quaternion> IntermediateCode;

int TempVariableCnt = 1;
//产生临时变量
BinaryEquation* NewTemp()
{
    BinaryEquation *temp = new BinaryEquation;
    temp->Class = TempVariable ;
    temp->Value = new char[3];
    temp->Value[0] = 'T';
    temp->Value[1] = TempVariableCnt + '0';
    temp->Value[2] = '\0';
    TempVariableCnt++;
    return temp;
}

//生成四元式
Quaternion Gen(char op,BinaryEquation *arg1,BinaryEquation *arg2,BinaryEquation *result)
{
    Quaternion temp;
    temp.op = op;
    temp.arg1 = arg1;
    temp.arg2 = arg2;
    temp.result = result;
    IntermediateCode.push_back(temp);
    return temp;
}

//输出四元式
void printQuaternion(Quaternion q)
{
    cout << "(" << q.op << "," << *(q.arg1) << "," << *(q.arg2) << "," << *(q.result) << ")";
}

//输出中间代码
void printIntermediateCode()
{
    printf("本程序的中间代码四元式形式如下:\n");
    // for (int i = 0; i < IntermediateCode.size(); i++)
    // {
    //     printf("(%c,",IntermediateCode[i].op);
    //     if (IntermediateCode[i].arg1->Class==TempVariable)
    //         printf("%s,",IntermediateCode[i].arg1->Value);
    //     else
    //         printf("%.2f,",IntermediateCode[i].arg1->Num);
    //     if (IntermediateCode[i].arg2->Class==TempVariable)
    //         printf("%s,",IntermediateCode[i].arg2->Value);
    //     else
    //         printf("%.2f,",IntermediateCode[i].arg2->Num);
    //     printf("%s)\n",IntermediateCode[i].result->Value);
    // }
    for (int i = 0; i < IntermediateCode.size(); i++)
    {
        printQuaternion(IntermediateCode[i]);
        printf("\n");
    }
}

//语义分析
void execute(int index, BinaryEquation *i)
{
    BinaryEquation *temp = NULL;
    Quaternion q_new;
    switch (index)
    {
        case 0:
            break;
        case 1:
            temp = NewTemp();
            q_new = Gen('+', PlaceMap['E'], PlaceMap['T'], temp);
            PlaceMap['E'] = temp;
            // cout << "生成" << temp->Value << ",生成四元式";
            // printQuaternion(q_new);
            break;
        case 2:
            temp = NewTemp();
            q_new = Gen('-', PlaceMap['E'], PlaceMap['T'], temp);
            PlaceMap['E'] = temp;
            cout << "生成" << temp->Value << ",生成四元式";
            printQuaternion(q_new);
            break;
        case 3:
            PlaceMap['E'] = PlaceMap['T'];
            cout << "E.Place=" << *(PlaceMap['T']);
            //printQuaternion(q_new);
            break;
        case 4:
            temp = NewTemp();
            q_new = Gen('*', PlaceMap['T'], PlaceMap['F'], temp);
            PlaceMap['T'] = temp;
            cout << "生成" << temp->Value << ",生成四元式";
            printQuaternion(q_new);
            break;
        case 5:
            temp = NewTemp();
            q_new = Gen('/', PlaceMap['T'], PlaceMap['F'], temp);
            PlaceMap['T'] = temp;
            cout << "生成" << temp->Value << ",生成四元式";
            printQuaternion(q_new);
            break;
        case 6:
            PlaceMap['T'] = PlaceMap['F'];
            cout << "T.Place=" << *(PlaceMap['F']);
            break;
        case 7:
            PlaceMap['F'] = PlaceMap['E'];
            cout << "F.Place=" << *(PlaceMap['E']);
            break;
        case 8 :
            PlaceMap['F'] = i;
            cout << "F.Place=" << *i;
            break;
        default:
            printf("error\n");
            return;
        break;
    }
}