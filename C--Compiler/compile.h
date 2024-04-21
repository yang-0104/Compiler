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
//词法分析的单词序列
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

// //栈
// typedef struct
// {
//     int *items;
//     int top;
// } Stack;


/* 文法产生式 */
struct Production
{
    char left;
    string right;
};

// /* 文法结构体 */
// struct Grammar
// {
//     int num;                  // 产生式数量
//     vector<char> T;           // 终结符
//     vector<char> N;           // 非终结符
//     vector<Production> prods; // 产生式
// };


#define BEGIN 1
#define END 2
#define IF 3
#define THEN 4
#define ELSE 5
#define WHILE 6
#define DO 7

#define ID 8 //标识符
#define INT 9 //整型
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
#define STR 21// 字符串str
#define FloatingPoint 22 //浮点型
#define ScientificNotation 23 //科学计数法
#define leftParenthesis 24 //左括号
#define RightParenthesis 25 //右括号
#define SEM 26 // ;
#define leftBrace 27 // {
#define rightBrace 28 // }
#define UnsignedNum 30 //无符号数
#define MAX_WORD_LENGTH 20
#define TempVariable 31//临时变量(语义分析使用)
#define pound '#' //#


#endif // FILENAME_H
