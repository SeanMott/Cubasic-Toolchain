#ifndef CUBASIC_LEXER_H
#define CUBASIC_LEXER_H

#include <Cubasic/CodeFile.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <Cubasic/Frontend/Token.hpp>

// Lexer State
typedef struct {
    int position;
    int line;
    int column;

    CodeFile* codeFile; //the file we are processing

} Lexer;

// Function declarations
Lexer* init_lexer(CodeFile* code);
Token* get_next_token(Lexer* lexer);
void free_token(Token* token);
void free_lexer(Lexer* lexer);

#endif // CUBASIC_LEXER_H
