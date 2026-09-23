/*Error Handler is based of Aho Textbook Version*/

#include "global.h"
int errors = 0;
void error(char *m) /*generating error message*/
{
    fprintf(stderr, "line %d: %s\n", lineno, m);
    /*exit(1); /*unsuccessful termination*/ // We don't exit because I still want to have the program run instead of ending it when an error happens
    errors++;
}