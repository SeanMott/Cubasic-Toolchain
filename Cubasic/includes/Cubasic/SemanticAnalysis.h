#ifndef CUBASIC_SEMANTIC_ANALYSIS_H
#define CUBASIC_SEMANTIC_ANALYSIS_H

#include <Cubasic/Parser.h>

// Symbol Table Entry
typedef struct Symbol {
    char* name;
    char* type; // "function", "variable", "array"
    int size;   // Array size, 0 for non-array variables
    int scope;  // Scope level (0 = global, 1+ = nested)
    struct Symbol* next; // Linked list for symbol collisions
} Symbol;

// Function Declarations
void add_symbol(const char* name, const char* type, int scope);
Symbol* find_symbol(const char* name);
void enter_scope();
void exit_scope();
void validate_ast(ASTNode* node, int scope);
void print_symbol_table();
void free_symbol_table();

#endif // CUBASIC_SEMANTIC_ANALYSIS_H
