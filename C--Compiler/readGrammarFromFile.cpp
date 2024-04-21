#include "compile.h"
#include <set>

vector<Production> Grammars;
map<char, BinaryEquation *> PlaceMap;

void initGrammar()
{
    ifstream inputFile("grammar.txt");
    int num;
    inputFile >> num;
    string s;
    Production temp;
    for (int i = 0; i < num; i++)
    {
        inputFile >> s;

        temp.left=s[0];
        temp.right = s.substr(3);
        Grammars.push_back(temp);

        PlaceMap[s[0]] = NULL;
    }
}