#include <stdio.h>
#include <string.h>

#define MAX_VARS 100

#define INT 1
#define FLOAT 2
#define STRING 3
#define NONE 0

typedef struct {
    char name[32];
    int type;
} SemanticEntry;

// --- Semantic Table ---
SemanticEntry semanticTable[MAX_VARS];
int tableSize = 0;

// --- Operations ---
void addVariable(char* name, int type) {
    for (int i = 0; i < tableSize; i++) {
        if (strcmp(semanticTable[i].name, name) == 0) {
            printf("Semantic Error: Variable '%s' already declared\n", name);
            return;
        }
    }
    if (tableSize < MAX_VARS) {
        strcpy(semanticTable[tableSize].name, name);
        semanticTable[tableSize].type = type;
        tableSize++;
    } else {
        printf("Semantic Error: Table full, cannot add '%s'\n", name);
    }
}

int getVariableType(char* name) {
    for (int i = 0; i < tableSize; i++) {
        if (strcmp(semanticTable[i].name, name) == 0) {
            return semanticTable[i].type;
        }
    }
    return NONE;
}

void printSemanticTable() {
    printf("Semantic Table:\n");
    for (int i = 0; i < tableSize; i++) {
        char* typeStr;
        switch (semanticTable[i].type) {
            case INT: typeStr = "INT"; break;
            case FLOAT: typeStr = "FLOAT"; break;
            case STRING: typeStr = "STRING"; break;
            default: typeStr = "UNKNOWN"; break;
        }
        printf("  %s : %s\n", semanticTable[i].name, typeStr);
    }
}

// --- Example: semantic checks after parsing ---
void runSemanticChecks() {
    // Example: check all variables have been declared (if parser left some names)
    for (int i = 0; i < tableSize; i++) {
        if (semanticTable[i].type == NONE) {
            printf("Semantic Error: Variable '%s' has unknown type\n", semanticTable[i].name);
        }
    }
}

void semantic() {
    // This function would be called after parsing to perform semantic analysis
    runSemanticChecks();
    printSemanticTable();
}
