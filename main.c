#include <stdlib.h>
#include <stdio.h>
#include "global.h"

//setting up our functions to call
void init();
void parse();
void semantic();
void insert(char s[], int tok);

//calls init for the needed states
//then calls parse to run everything else suck as the lexical
int main()
{
    init();
    parse();
    semantic();
    return 0;
}
