#include "compile.h"

#define MAX_KEY_NUMBER 20                         
#define KEY_WORD_END "waiting for your expanding" 
const char *KeyWordTable[MAX_KEY_NUMBER] = {"begin", "end", "if", "then", "else", "while", "do", KEY_WORD_END};

int lookup(char *token)
{
    int n = 0;
    while (strcmp(KeyWordTable[n], KEY_WORD_END)) 
    {
        if (!strcmp(KeyWordTable[n], token)) 
        {
            return n + 1; 
            break;
        }
        n++;
    }
    return 0; 
}