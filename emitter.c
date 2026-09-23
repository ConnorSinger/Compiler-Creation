#include "global.h"

void emit(int t, int tval) //tval is the token value, which is used to check
{
    switch(t)
    {
        case PRINT:
            printf("PRINT\n"); break;
        case NUM:
            printf("PUSH %d\n", tval); break;
        case ID:
            printf("PUSH %s\n", symtable[tval].lexptr); break;
        case '+':
            printf("ADD\n"); break;
        case '-':
            printf("SUB\n"); break;
        case '*':
            printf("MUL\n"); break;
        case '/':
            printf("DIV\n"); break;
        case '=':
            printf("ASSIGN %s\n", symtable[tval].lexptr); break;
        case EXIT:
            printf("EXIT\n"); break;    
        case DIV:
            printf("DIV\n"); break;
        case MOD:
            printf("MOD\n"); break;
        case INT:
            printf("INT\n"); break;
        case FLOAT:
            printf("FLOAT\n"); break;
        case READ:
            printf("READ\n"); break;
        case STRING:
            printf("STRING %s\n", symtable[tval].lexptr); break;
        case FUNCTION:
            //printf("FUNCTION %s\n", symtable[tval].lexptr); break;
                printf("FUNCTION\n"); break;
        default:
            printf("token %d, tokenval %d\n", t, tval);
    }
}