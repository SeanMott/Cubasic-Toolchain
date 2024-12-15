#pragma once

//defines a code file

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//defines a file of code
typedef struct CodeFile
{
    size_t codeLength; //the code length
    char* code; //the code
} CodeFile;

//loads a file
static inline bool LoadFile(const char* fileFP, CodeFile* code)
{
    FILE* file = fopen(fileFP, "r");
    if (!file)
    {
        fprintf(stderr, "Error: Cannot open file '%s'\n", fileFP);
        return false;
    }

    // Read the source code
    fseek(file, 0, SEEK_END);
    code->codeLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    code->code = (char*)malloc(code->codeLength);
    fread(code->code, 1, code->codeLength, file);
    code->code[code->codeLength] = '\0';
    fclose(file);

    return true;
}

//unloads a code file
static inline void UnloadFile(CodeFile* code)
{
    if (code->code)
        free(code);
    code->code = NULL;
    code->codeLength = 0;
}