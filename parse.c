#include "global.h"
#include <stdlib.h>

int lookahead;
int lexical();
void error(char* m);


void emit(int t, int tval);

void parse(void);
void stmt(void);
void decl(void);
void expr(void);
void term(void);
void factor(void);
void match(int t);
void myFunction(void);

//match function checks to see if current token is what I expect else returns an error
void match(int t)
{
    if(lookahead == t)
        lookahead = lexical();
    else
    {
        printf("Match Error\nLookahead: %d, Expected: %d\n", lookahead, t);
        //call the error function and pass in the error message
        error("Match Error");
        //calling the lexical function to skip the current token and move on to the next one
        while(lookahead != t && lookahead != DONE && lookahead != ';' && lookahead != '}')
            lookahead = lexical();
        //then if the next token is what I expect then move on to the next token
        if(lookahead == t)
            lookahead = lexical();
    }
}


//when i need to declare a variable this would be the setup
void decl()
{
    //first here i consume the type
    int t;
    t = lookahead;
    match(t);

    //then i consume the identifier
    int index = tokenval;
    match(ID);

    //here i check to see if there was an assignment in the sentence
    if(lookahead == '=')
    {
        match('=');
        expr();
        emit('=', index);
    }

    emit(t, tokenval);
    match(';');
}

//handles lower precedence operators such as addition and subtraction
void expr()
{
    int t; // the next token
    term();//checking for the higher precedence operators first
    while((t = lookahead) == '+' || t == '-')
    {
        match(t);
        term();
        emit(t, NONE);
    }
}

//handles smallest things inside of the statements such as numbers, identifiers, and parenthesis
void factor()
{
    int tempTokenval;
    if(lookahead == '(')
    {
        match('(');
        expr();
        match(')');
    }
    else if(lookahead == NUM)
    {
        emit(NUM, tokenval);
        match(NUM);
    }
    else if(lookahead == ID)
    {
        emit(ID, tokenval);
        match(ID);
    }
    else if(lookahead == STRING)
    {
        emit(STRING, tokenval);
        match(STRING);
    }
    else
        error("Syntax Error in Factor");
}


void stmt()
{
    switch(lookahead)
    {
        case INT:
        case FLOAT:
            printf("Lookahead: %d\n", lookahead);
            decl(); break;
        //checking to see if there is an assignment
        case STRING:
                decl(); break;


        case ID:
        
            int index = tokenval;
            match(ID);
            if(lookahead == '=')
            {
                match('=');
                expr();
                emit('=', index);
                match(';');
            }
            else
                error("Syntax Error");
            break;
        
        case EXIT:
            exit(0); break;
        case PRINT:
            match(PRINT);
            match('(');
            expr();
            match(')');
            emit(PRINT, NONE); 
            match(';');
            break;
        case FUNCTION:
            int t = lookahead;
            match(t);
            index = tokenval;
            match(ID);
            match('(');
            //now a while loop since we don't know how many parameters there will be
            while(lookahead != ')')
            {
                int paramType = lookahead;
                match(paramType);
                int paramIndex = tokenval;
                match(ID);
                emit(paramType, paramIndex);
                if(lookahead == ',')
                    match(',');
            }
            match(')');
            match('{');
            while(lookahead != '}')
                stmt();
            emit(FUNCTION, NONE);
            match('}');
            break;
        default:
            error("Error: Statement");
            
            //need to skip over every bad token
            while(lookahead != ';' && lookahead != DONE)
                lookahead = lexical();
            if(lookahead == ';')
                lookahead = lexical();
            break;
    }
}


//this is for the higher precedence operators such as multiplication and division
void term()
{
    int t;
    factor();
    while((t = lookahead) == '*' || t == '/' || t == DIV || t == MOD)
    {
        match(t);
        factor();
        emit(t, NONE);
    }
}

//This is the function that runs everything else
void parse()
{
    lookahead = lexical();
    while(lookahead != DONE)
        stmt();
}

