#ifndef CUBASIC_LEXER_H
#define CUBASIC_LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define token types
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_LITERAL,
    TOKEN_STRING,
    TOKEN_PUNCTUATION,
    TOKEN_COMMENT,
    TOKEN_EOF,
    TOKEN_EXPRESSION,
    TOKEN_ERROR
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char* value;
    int line;
    int column;
} Token;

// Lexer State
typedef struct {
    const char* source;
    int position;
    int line;
    int column;
    size_t sourceLength;
} Lexer;

// Function declarations
Lexer* init_lexer(const char* source);
Token* get_next_token(Lexer* lexer);
void free_token(Token* token);
void free_lexer(Lexer* lexer);

#endif // CUBASIC_LEXER_H
