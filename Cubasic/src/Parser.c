#include <Cubasic/Parser.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Error handling function
void handle_parser_error(Parser* parser, const char* message) {
    fprintf(stderr, "Parser Error: %s\n", message);
    free_parser(parser);
    exit(EXIT_FAILURE);
}

// Utility: Get the current token
Token* current_token(Parser* parser) {
    if (parser->current_token < parser->token_count) {
        return parser->tokens[parser->current_token];
    }
    return NULL;
}

// Utility: Peek at the next token
Token* peek_next_token(Parser* parser) {
    if (parser->current_token + 1 < parser->token_count) {
        return parser->tokens[parser->current_token + 1];
    }
    return NULL;
}

// Utility: Advance to the next token
void parserAdvance(Parser* parser) {
    if (parser->current_token < parser->token_count) {
        parser->current_token++;
    }
}

// Initialize the parser
Parser* init_parser(Token** tokens, int token_count) {
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->tokens = tokens;
    parser->token_count = token_count;
    parser->current_token = 0;
    return parser;
}

// Free the parser
void free_parser(Parser* parser) {
    free(parser);
}

// Create a new AST node
ASTNode* create_ast_node(ASTNodeType type, const char* value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value ? _strdup(value) : NULL;
    node->children = NULL;
    node->child_count = 0;
    return node;
}

// Add a child to an AST node
void add_child(ASTNode* parent, ASTNode* child) {
    parent->children = (ASTNode**)realloc(parent->children, sizeof(ASTNode*) * (parent->child_count + 1));
    parent->children[parent->child_count++] = child;
}

// Parse an expression (basic implementation)
ASTNode* parse_expression(Parser* parser) {
    Token* token = current_token(parser);
    if (token && token->type == TOKEN_LITERAL) {
        ASTNode* node = create_ast_node(AST_EXPRESSION, token->value);
        parserAdvance(parser); // Consume the literal
        return node;
    }

    if (token && token->type == TOKEN_IDENTIFIER) {
        if (peek_next_token(parser) && strcmp(peek_next_token(parser)->value, "[") == 0) {
            return parse_array_access(parser); // Handle array indexing
        }
        ASTNode* node = create_ast_node(AST_EXPRESSION, token->value);
        parserAdvance(parser); // Consume the identifier
        return node;
    }

    handle_parser_error(parser, "Expected an expression");
    return NULL; // This line won't be reached due to exit in handle_parser_error
}

// Parse array access (e.g., arr[i])
ASTNode* parse_array_access(Parser* parser) {
    Token* array_name = current_token(parser);
    if (!array_name || array_name->type != TOKEN_IDENTIFIER) {
        handle_parser_error(parser, "Expected array name before '['");
    }

    ASTNode* array_node = create_ast_node(AST_EXPRESSION, array_name->value);
    parserAdvance(parser); // Consume array name

    Token* open_bracket = current_token(parser);
    if (!open_bracket || strcmp(open_bracket->value, "[") != 0) {
        handle_parser_error(parser, "Expected '[' after array name");
    }
    parserAdvance(parser); // Consume '['

    ASTNode* index_node = parse_expression(parser); // Parse the index expression
    add_child(array_node, index_node);

    Token* close_bracket = current_token(parser);
    if (!close_bracket || strcmp(close_bracket->value, "]") != 0) {
        handle_parser_error(parser, "Expected ']' after array index");
    }
    parserAdvance(parser); // Consume ']'

    return array_node;
}

// Parse a statement
ASTNode* parse_statement(Parser* parser) {
    Token* token = current_token(parser);
    if (!token) return NULL;

    if (token->type == TOKEN_KEYWORD && strcmp(token->value, "PRINT") == 0) {
        ASTNode* print_node = create_ast_node(AST_STATEMENT, "PRINT");
        parserAdvance(parser); // Consume PRINT
        Token* argument = current_token(parser);
        if (!argument || argument->type != TOKEN_STRING) {
            handle_parser_error(parser, "Expected string after PRINT");
        }
        add_child(print_node, create_ast_node(AST_EXPRESSION, argument->value));
        parserAdvance(parser); // Consume string
        return print_node;
    }

    if (token->type == TOKEN_KEYWORD && strcmp(token->value, "DIM") == 0) {
        ASTNode* dim_node = create_ast_node(AST_STATEMENT, "DIM");
        parserAdvance(parser); // Consume DIM

        Token* array_name = current_token(parser);
        if (!array_name || array_name->type != TOKEN_IDENTIFIER) {
            handle_parser_error(parser, "Expected array name after DIM");
        }
        add_child(dim_node, create_ast_node(AST_EXPRESSION, array_name->value));
        parserAdvance(parser); // Consume array name

        Token* open_bracket = current_token(parser);
        if (!open_bracket || strcmp(open_bracket->value, "(") != 0) {
            handle_parser_error(parser, "Expected '(' after array name");
        }
        parserAdvance(parser); // Consume '('

        ASTNode* size_node = parse_expression(parser);
        add_child(dim_node, size_node);

        Token* close_bracket = current_token(parser);
        if (!close_bracket || strcmp(close_bracket->value, ")") != 0) {
            handle_parser_error(parser, "Expected ')' after array size");
        }
        parserAdvance(parser); // Consume ')'

        return dim_node;
    }

    if (token->type == TOKEN_EOF) {
        // Handle end-of-file gracefully
        return NULL;
    }

    handle_parser_error(parser, "Unrecognized statement");
    return NULL; // This line won't be reached due to exit in handle_parser_error
}

// Parse a function
ASTNode* parse_function(Parser* parser) {
    Token* token = current_token(parser);
    if (!token || token->type != TOKEN_KEYWORD || strcmp(token->value, "FUNCTION") != 0) {
        handle_parser_error(parser, "Expected FUNCTION keyword");
    }

    parserAdvance(parser); // Consume FUNCTION
    Token* func_name = current_token(parser);
    if (!func_name || func_name->type != TOKEN_IDENTIFIER) {
        handle_parser_error(parser, "Expected function name after FUNCTION");
    }

    ASTNode* func_node = create_ast_node(AST_FUNCTION_DEF, func_name->value);
    parserAdvance(parser); // Consume function name

    while (current_token(parser) && strcmp(current_token(parser)->value, "END") != 0) {
        add_child(func_node, parse_statement(parser));
    }

    parserAdvance(parser); // Consume END
    return func_node;
}

// Parse a program
ASTNode* parse_program(Parser* parser) {
    ASTNode* root = create_ast_node(AST_PROGRAM, "Program");
    while (current_token(parser) && current_token(parser)->type != TOKEN_EOF) {
        add_child(root, parse_function(parser));
    }
    return root;
}

// Free an AST node and its children
void free_ast_node(ASTNode* node) {
    if (!node) return;
    for (int i = 0; i < node->child_count; i++) {
        free_ast_node(node->children[i]);
    }
    free(node->children);
    free(node->value);
    free(node);
}
