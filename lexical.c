#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "global.h"


int tokenval = NONE;
int lineno = 1;
char lexbuf[BSIZE];

int lookup(char s[]);
int insert(char s[], int tok);
int error(char* m);


//lookup is from the symbol table - this checks to the previous token / character if it was 
//insert is also from the symbol table
//error is from the error handler


int lexical()
{
    int t;

    while(1)
    {
        //Removing Whitespace
        t = getchar();
        if(t == ' ' || t == '\t')
            ;
        //Checking if it is a newLine
        else if(t == '\n')
            lineno = lineno + 1;

        
        //Checking to see if the user types down a String
        //And then checks to see when it ends
        else if(t == '"')
        {
            int b = 0;
            t = getchar();
            while(t != '"' && t != EOF && t != '\n')
            {
                if(b < BSIZE - 1)
                    lexbuf[b++] = t;
                t = getchar();
            }
            //If the string end is not found return error then skip the character
            if(t != '"')
            {
                error("Unterminated string constant");
                return lexical();
            }
            lexbuf[b] = EOS;
            tokenval = insert(lexbuf, STRING);
            return STRING;
        }

        //Checking to see if the current character is a digit
        else if(isdigit(t))
        {
            //grabbing the character
            tokenval = t - '0';
            t = getchar();
            while(isdigit(t))
            {
                tokenval = tokenval * 10 + t - '0';
                t = getchar();
            }
            ungetc(t, stdin);
            return NUM;
        }
        
        //Checking to see if the current character is apart of the alphabet (letter)
        else if(isalpha(t))
        {
            //setting p and b to zero
            int b = 0;
            int p = 0;
            while(isalnum(t))
            {
                if(b < BSIZE - 1)
                    lexbuf[b++] = t;
                t = getchar();
            }
            lexbuf[b] = EOS;
            ungetc(t, stdin);
            if((p = lookup(lexbuf)) == 0)
            {
                tokenval = insert(lexbuf, ID);
                return ID;
            }
            
            //Now I need to check for keywords
            int symIndex = lookup(lexbuf);
                if(symIndex != 0)
                {
                    int tokenType = symtable[symIndex].token;
                    tokenval = (tokenType == ID) ? symIndex : NONE;
                    return tokenType;
                }
                else
                {
                    tokenval = insert(lexbuf, ID);
                    return ID;
                }
        }
        //checking if its not the end of line
        // or puts it inside the symbol pile
        else
        {
            if(t == EOF)
                return DONE;
            else
                return t;
        }
    }

}