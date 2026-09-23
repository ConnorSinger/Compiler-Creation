#include "global.h"

int insert(char s[], int tok);

//here we make a structure full of the keywords that we would want the compiler to have
struct entry keywords[] = {
    {"div", DIV},
    {"mod", MOD},
    {"int", INT},
    {"float", FLOAT},
    {"exit", EXIT},
    {"testingFeature", TESTING},
    {"print", PRINT},
    {"read", READ},
    {"if", IF},
    {"else", ELSE},
    {"while", WHILE},
    {"string", STRING},
    {"for", FOR},
    {"function", FUNCTION},
    {0,      0}
};

//here we create the entry structure p and then loop it inserting all of the keywords we have in the entry structure
void init()
{
    struct entry *p;
    for(p = keywords; p -> token; p++)
        insert(p->lexptr, p->token);
}
