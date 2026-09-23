#include "global.h"
#include <string.h>
#define STRMAX 999
#define SYMMAX 100

char lexemes[STRMAX];
int lastchar = -1;
struct entry symtable[SYMMAX];
int lastentry = 0;

//error function from the error file
int error(char* m);


//here we have the character array and go through the whole array and check if the character iis inside the stmbol table
//if it is return the number of where it is else we return zero
int lookup(char s[])
{
    int p;
    for(p = lastentry; p > 0; p = p - 1)
        if(strcmp(symtable[p].lexptr, s) == 0)
            return p;
    return 0;
}

//here we take the character array and if the lastentry +1 is bigger than symmax if true catch an error
// then if that doesn't happen we check to see if the last character + length + 1 is bigger than strmax and if true catch an error
//then if we don't have any errors we increase the lastentry by one
//then we take the lastentry token and replaces it with the given token from the parameter
//next we take the lastentry and gets the lexptr and replaces it with the new last character of lexemes
//next we increase the lastchar by one
//then we copy the string of the last entry of the symtable lexpr to s
//then after we return the last entry
int insert(char s[], int tok)
{
    int len;
    len = strlen(s);
    if(lastentry + 1 >= SYMMAX)
        error("symbol table full");
    if(lastchar + len + 1 >= STRMAX)
        error("lexemes array full");
    lastentry = lastentry + 1;
    symtable[lastentry].token = tok;
    symtable[lastentry].lexptr = &lexemes[lastchar + 1];
    lastchar = lastchar + len + 1;
    strcpy(symtable[lastentry].lexptr, s);
    return lastentry;
}