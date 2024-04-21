#ifndef FILENAME_H
#define FILENAME_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <fstream>
#include<list>
#include <set>

using namespace std;
//�ʷ������ĵ�������
struct BinaryEquation
{
    int Class;
    char *Value;
    double Num;
};


//typedef struct Node
//{
//    BinaryEquation data;
//    struct Node *next;
//} Node;

// //ջ
// typedef struct
// {
//     int *items;
//     int top;
// } Stack;


/* �ķ�����ʽ */
struct Production
{
    char left;
    string right;
};

// /* �ķ��ṹ�� */
// struct Grammar
// {
//     int num;                  // ����ʽ����
//     vector<char> T;           // �ս��
//     vector<char> N;           // ���ս��
//     vector<Production> prods; // ����ʽ
// };


#define BEGIN 1
#define END 2
#define IF 3
#define THEN 4
#define ELSE 5
#define WHILE 6
#define DO 7

#define ID 8 //��ʶ��
#define INT 9 //����
#define LT 10 // <
#define LE 11 // <=
#define EQ 12// ==
#define NE 13// <>
#define GT 14// >
#define GE 15// >=
#define IS 16// =
#define PL 17// +
#define MI 18// -
#define MU 19// *
#define DI 20// /
#define STR 21// �ַ���str
#define FloatingPoint 22 //������
#define ScientificNotation 23 //��ѧ������
#define leftParenthesis 24 //������
#define RightParenthesis 25 //������
#define SEM 26 // ;
#define leftBrace 27 // {
#define rightBrace 28 // }
#define UnsignedNum 30 //�޷�����
#define MAX_WORD_LENGTH 20
#define TempVariable 31//��ʱ����(�������ʹ��)
#define pound '#' //#


#endif // FILENAME_H
