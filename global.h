#include <stdio.h>
#include <ctype.h>

#define BSIZE 128
#define NONE -1
#define EOS '\0'
#define NUM 256
#define DIV 257
#define MOD 258
#define ID 259
#define DONE 260

#define INT 265
#define FLOAT 266
#define TESTING 267
#define EXIT 268
#define IF 269
#define ELSE 270
#define WHILE 271
#define FOR 272
#define PRINT 273
#define READ 274
#define STRING 275
#define FUNCTION 276

#define LT 300 // <
#define LE 301 // <=
#define GT 302 // >
#define GE 303 // >=
#define EQ 304 // ==
#define NE 305 // !=

#define SYMMAX 100
#define STRMAX 999


extern int tokenval;
extern int lineno;
//we create the structure to be used
struct entry
{
    char *lexptr;
    int token;
};
extern struct entry symtable[];

