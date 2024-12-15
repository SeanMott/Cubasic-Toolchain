#include <Cubasic/SemanticAnalysis.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbol Table
#define SYMBOL_TABLE_SIZE 100
Symbol* symbol_table[SYMBOL_TABLE_SIZE];
int current_scope = 0;

// Utility: Hash a string for symbol table indexing
unsigned int hash(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % SYMBOL_TABLE_SIZE;
}

// Error handling function
void handle_semantic_error(const char* message) {
    fprintf(stderr, "Semantic Error: %s\n", message);
    free_symbol_table();
    exit(EXIT_FAILURE);
}

// Add a symbol to the table
void add_symbol(const char* name, const char* type, int size, int scope) {
    unsigned int index = hash(name);
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->name = _strdup(name);
    symbol->type = _strdup(type);
    symbol->size = size;
    symbol->scope = scope;
    symbol->next = symbol_table[index];
    symbol_table[index] = symbol;
}

// Find a symbol in the table
Symbol* find_symbol(const char* name) {
    unsigned int index = hash(name);
    Symbol* symbol = symbol_table[index];
    while (symbol) {
        if (strcmp(symbol->name, name) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }
    return NULL;
}

// Enter a new scope
void enter_scope() {
    current_scope++;
}

// Exit the current scope
void exit_scope() {
    current_scope--;
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        Symbol* symbol = symbol_table[i];
        Symbol* prev = NULL;
        while (symbol) {
            if (symbol->scope > current_scope) {
                if (prev) {
                    prev->next = symbol->next;
                }
                else {
                    symbol_table[i] = symbol->next;
                }
                Symbol* temp = symbol;
                symbol = symbol->next;
                free(temp->name);
                free(temp->type);
                free(temp);
            }
            else {
                prev = symbol;
                symbol = symbol->next;
            }
        }
    }
}

// Validate array access
void validate_array_access(ASTNode* node) {
    if (!node || node->type != AST_ARRAY_ACCESS) {
        return;
    }

    // Ensure the array is declared
    Symbol* symbol = find_symbol(node->value);
    if (!symbol || strcmp(symbol->type, "array") != 0) {
        char error_message[256];
        snprintf(error_message, sizeof(error_message), "Array '%s' not declared", node->value);
        handle_semantic_error(error_message);
    }

    // Ensure the index is within bounds
    ASTNode* index_node = node->children[0];
    if (index_node->type != AST_EXPRESSION || !index_node->value) {
        char error_message[256];
        snprintf(error_message, sizeof(error_message), "Invalid index for array '%s'", node->value);
        handle_semantic_error(error_message);
    }

    int index = atoi(index_node->value);
    if (index < 0 || index >= symbol->size) {
        char error_message[256];
        snprintf(error_message, sizeof(error_message), "Array index '%d' out of bounds for array '%s' (size: %d)", index, node->value, symbol->size);
        handle_semantic_error(error_message);
    }
}

// Validate and enrich the AST
void validate_ast(ASTNode* node, int scope) {
    if (!node) return;

    switch (node->type) {
    case AST_PROGRAM:
    case AST_FUNCTION_DEF:
    case AST_LOOP:
    case AST_CONDITIONAL:
        enter_scope();
        for (int i = 0; i < node->child_count; i++) {
            validate_ast(node->children[i], scope + 1);
        }
        exit_scope();
        break;

    case AST_DIM:
        // Ensure array name is unique in the current scope
        if (find_symbol(node->value)) {
            char error_message[256];
            snprintf(error_message, sizeof(error_message), "Array '%s' already declared", node->value);
            handle_semantic_error(error_message);
        }
        // Add array to symbol table with its size
        add_symbol(node->value, "array", atoi(node->children[0]->value), scope);
        break;

    case AST_ARRAY_ACCESS:
        validate_array_access(node);
        break;

    case AST_ASSIGNMENT:
    case AST_CALL:
    case AST_GRAPHICS:
    case AST_SOUND:
    case AST_STATEMENT:
    case AST_EXPRESSION:
        for (int i = 0; i < node->child_count; i++) {
            validate_ast(node->children[i], scope);
        }
        break;

    default:
        fprintf(stderr, "Error: Unhandled AST node type %d\n", node->type);
        exit(EXIT_FAILURE);
    }
}

// Print the symbol table
void print_symbol_table() {
    printf("Symbol Table:\n");
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        Symbol* symbol = symbol_table[i];
        while (symbol) {
            printf("  Name: %s, Type: %s, Size: %d, Scope: %d\n", symbol->name, symbol->type, symbol->size, symbol->scope);
            symbol = symbol->next;
        }
    }
}

// Free the symbol table
void free_symbol_table() {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        Symbol* symbol = symbol_table[i];
        while (symbol) {
            Symbol* next = symbol->next;
            free(symbol->name);
            free(symbol->type);
            free(symbol);
            symbol = next;
        }
        symbol_table[i] = NULL;
    }
}
