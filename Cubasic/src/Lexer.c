#include <Cubasic/Lexer.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

// Define token patterns
const char* keywords[] = {
    "FUNCTION", "PRINT", "DIM", "FOR", "IF", "ELSE", "ENDIF", "END", "CALL", "WHILE",
    "BREAK", "CONTINUE", "GOTO", "RETURN", "HALT", "INPUT", "SET", "NEXT",
    "SWAP", "CLEAR", "TRY", "CATCH", "PAUSE", "VIEW", NULL
};

const char operators[] = "+-*/=<>";
const char punctuation[] = "(),[]"; // Added '[' and ']'

// Initialize Lexer
Lexer* init_lexer(const char* source) {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    lexer->source = source;
    lexer->position = 0;
    lexer->line = 1;
    lexer->column = 1;
    lexer->sourceLength = strlen(source);
    return lexer;
}

// Check if a string is a keyword
int is_keyword(const char* str) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Create a new token
Token* create_token(TokenType type, const char* value, int line, int column) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->value = _strdup(value);
    token->line = line;
    token->column = column;
    return token;
}

// Free a token
void free_token(Token* token) {
    free(token->value);
    free(token);
}

// Error handling function
void handle_error(Lexer* lexer, const char* message) {
    fprintf(stderr, "Error at line %d, column %d: %s\n", lexer->line, lexer->column, message);
    free_lexer(lexer);  // Ensure cleanup
    exit(EXIT_FAILURE); // Optional, for critical failures
}

// Advance the lexer by one character
char lexerAdvance(Lexer* lexer) {
    if (lexer->position >= lexer->sourceLength)
        return EOF;
    
    char current = lexer->source[lexer->position];
    lexer->position++;
    lexer->column++;
    if (current == '\n') {
        lexer->line++;
        lexer->column = 1;
    }
    return current;
}

// Peek at the next character without consuming it
char peek(Lexer* lexer) {
    if (lexer->position >= lexer->sourceLength)
        return EOF;

    return lexer->source[lexer->position];
}

// Skip whitespace and comments
void skip_whitespace_and_comments(Lexer* lexer) {
    while (isspace((unsigned char)peek(lexer)) || (peek(lexer) == '/' && lexer->source[lexer->position + 1] == '/')) {
        if (peek(lexer) == '/') {
            while (peek(lexer) != '\n' && peek(lexer) != '\0') {
                lexerAdvance(lexer);
            }
        }
        else {
            lexerAdvance(lexer);
        }
    }
}

// Get the next token from the source code
Token* get_next_token(Lexer* lexer) {
    skip_whitespace_and_comments(lexer);

    char current = peek(lexer);
    if (current == '\0' || current == EOF) {
        // Ensure EOF token is emitted only once
       // if (lexer->position > strlen(lexer->source)) {
            return create_token(TOKEN_EOF, "", lexer->line, lexer->column);
        //}
    }

    // Keywords and Identifiers
    if (isalpha((unsigned char)current) || current == '_') {
        int start = lexer->position;
        int start_column = lexer->column;
        while (isalnum((unsigned char)peek(lexer)) || peek(lexer) == '_') {
            lexerAdvance(lexer);
        }
        char* value = (char*)malloc(lexer->position - start + 1);
        strncpy_s(value, lexer->position - start + 1, lexer->source + start, lexer->position - start);
        value[lexer->position - start] = '\0';
        TokenType type = is_keyword(value) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
        return create_token(type, value, lexer->line, start_column);
    }

    // Numbers (Literals)
    if (isdigit((unsigned char)current)) {
        int start = lexer->position;
        int start_column = lexer->column;
        while (isdigit((unsigned char)peek(lexer))) {
            lexerAdvance(lexer);
        }
        char* value = (char*)malloc(lexer->position - start + 1);
        strncpy_s(value, lexer->position - start + 1, lexer->source + start, lexer->position - start);
        value[lexer->position - start] = '\0';
        return create_token(TOKEN_LITERAL, value, lexer->line, start_column);
    }

    // Strings
    if (current == '"') {
        lexerAdvance(lexer); // Consume opening quote
        int start = lexer->position;
        int start_column = lexer->column;
        while (peek(lexer) != '"' && peek(lexer) != '\0') {
            lexerAdvance(lexer);
        }
        if (peek(lexer) == '"') {
            lexerAdvance(lexer); // Consume closing quote
        }
        else {
            handle_error(lexer, "Unterminated string literal");
        }
        char* value = (char*)malloc(lexer->position - start);
        strncpy_s(value, lexer->position - start + 1, lexer->source + start, lexer->position - start);
        value[lexer->position - start - 1] = '\0';
        return create_token(TOKEN_STRING, value, lexer->line, start_column);
    }

    // Operators
    if (strchr(operators, current)) {
        char value[2] = { current, '\0' };
        lexerAdvance(lexer);
        return create_token(TOKEN_OPERATOR, value, lexer->line, lexer->column - 1);
    }

    // Punctuation
    if (strchr(punctuation, current)) {
        char value[2] = { current, '\0' };
        lexerAdvance(lexer);
        return create_token(TOKEN_PUNCTUATION, value, lexer->line, lexer->column - 1);
    }

    // Unrecognized Token
    handle_error(lexer, "Unrecognized token encountered");
    return NULL; // Will not reach here due to exit in handle_error
}

// Free the lexer
void free_lexer(Lexer* lexer) {
    free(lexer);
}
