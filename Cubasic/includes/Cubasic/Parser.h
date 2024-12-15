#ifndef PARSER_H
#define PARSER_H

#include <Cubasic/Lexer.h>

// AST Node Types
typedef enum {
    AST_PROGRAM,
    AST_FUNCTION_DEF,
    AST_STATEMENT,
    AST_EXPRESSION,
    AST_ASSIGNMENT,
    AST_LOOP,
    AST_CONDITIONAL,
    AST_CALL,
    AST_ARRAY_ACCESS,
    AST_DIM,
    AST_GRAPHICS,
    AST_SOUND
} ASTNodeType;

// AST Node Structure
typedef struct ASTNode {
    ASTNodeType type;
    char* value; // Value of the node (e.g., identifier, literal)
    struct ASTNode** children; // Children nodes
    int child_count; // Number of children
} ASTNode;

// Parser State
typedef struct Parser {
    Token** tokens;
    int token_count;
    int current_token;
} Parser;

// Function Declarations
Parser* init_parser(Token** tokens, int token_count);
void free_parser(Parser* parser);
ASTNode* create_ast_node(ASTNodeType type, const char* value);
void add_child(ASTNode* parent, ASTNode* child);
ASTNode* parse_program(Parser* parser);
ASTNode* parse_function(Parser* parser);
ASTNode* parse_statement(Parser* parser);
ASTNode* parse_expression(Parser* parser);
ASTNode* parse_array_access(Parser* parser);
void free_ast_node(ASTNode* node);

#endif // PARSER_H
