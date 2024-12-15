#pragma once

//defines a token

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

//converts a token type into a string
static inline const char* TokenTypeToStr(const TokenType t)
{
    switch (t)
    {
    case TOKEN_KEYWORD:
        return "Keyword";

    case TOKEN_IDENTIFIER:
        return "Identifier";

    case TOKEN_OPERATOR:
        return "Operator";

    case TOKEN_LITERAL:
        return "Literal";

    case TOKEN_STRING:
        return "String";

    case TOKEN_PUNCTUATION:
        return "Punctuation";

    case TOKEN_COMMENT:
        return "Comment";

    case TOKEN_EOF:
        return "End Of File";

    case TOKEN_EXPRESSION:
        return "Expression";

    case TOKEN_ERROR:
        return "Error";

    default:
        return "UNKNOWN_TOKEN_TYPE";
    }
}

// Token structure
typedef struct {
    TokenType type;
    char* value;
    int line;
    int column;
} Token;

//prints a token
static inline void PrintToken(const Token* token)
{
    printf("Type: %s, Value: '%s', Line: %d, Column: %d\n",
        TokenTypeToStr(token->type), token->value, token->line, token->column);
}