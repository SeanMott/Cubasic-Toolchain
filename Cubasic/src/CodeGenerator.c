#include <Cubasic/CodeGenerator.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Output buffers for ROM sections
char* prg_section = NULL;
size_t prg_size = 0;

// Append to a section buffer
void append_to_section(char** section, size_t* size, const char* instruction) {
    size_t instruction_len = strlen(instruction);
    *section = (char*)realloc(*section, *size + instruction_len + 2); // +2 for newline and null terminator
    if (!*section) {
        fprintf(stderr, "Error: Memory allocation failed in append_to_section\n");
        exit(EXIT_FAILURE);
    }
    snprintf(*section + *size, instruction_len + 2, "%s\n", instruction);
    *size += instruction_len + 1;
}

// Generate assembly for an AST node
void generate_ast_node(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
    case AST_PROGRAM:
        for (int i = 0; i < node->child_count; i++) {
            generate_ast_node(node->children[i]);
        }
        break;

    case AST_FUNCTION_DEF:
        append_to_section(&prg_section, &prg_size, node->value); // Function label
        for (int i = 0; i < node->child_count; i++) {
            generate_ast_node(node->children[i]);
        }
        append_to_section(&prg_section, &prg_size, "RET");
        break;

    case AST_STATEMENT:
        if (strcmp(node->value, "PRINT") == 0) {
            char instruction[256];
            snprintf(instruction, sizeof(instruction), "PRINT \"%s\"", node->children[0]->value);
            append_to_section(&prg_section, &prg_size, instruction);
        }
        break;

    case AST_ASSIGNMENT:
    {
        char instruction[256];
        snprintf(instruction, sizeof(instruction), "SET %s = %s", node->value, node->children[0]->value);
        append_to_section(&prg_section, &prg_size, instruction);
    }
    break;

    case AST_ARRAY_ACCESS:
    {
        char instruction[256];
        snprintf(instruction, sizeof(instruction), "LOAD %s[%s]", node->value, node->children[0]->value);
        append_to_section(&prg_section, &prg_size, instruction);
    }
    break;

    case AST_DIM:
    {
        char instruction[256];
        snprintf(instruction, sizeof(instruction), "ALLOC %s, %s", node->value, node->children[0]->value);
        append_to_section(&prg_section, &prg_size, instruction);
    }
    break;

    case AST_LOOP:
        if (strcmp(node->value, "FOR") == 0) {
            char start_label[64], end_label[64];
            snprintf(start_label, sizeof(start_label), "LABEL_START_%s", node->children[0]->value);
            snprintf(end_label, sizeof(end_label), "LABEL_END_%s", node->children[0]->value);

            append_to_section(&prg_section, &prg_size, start_label);
            for (int i = 1; i < node->child_count; i++) {
                generate_ast_node(node->children[i]);
            }
            append_to_section(&prg_section, &prg_size, end_label);
        }
        break;

    case AST_CONDITIONAL:
        if (strcmp(node->value, "IF") == 0) {
            char else_label[64], end_label[64];
            snprintf(else_label, sizeof(else_label), "LABEL_ELSE_%d", rand());
            snprintf(end_label, sizeof(end_label), "LABEL_END_IF_%d", rand());

            char condition_instruction[256];
            snprintf(condition_instruction, sizeof(condition_instruction), "IF %s GOTO %s", node->children[0]->value, else_label);
            append_to_section(&prg_section, &prg_size, condition_instruction);

            for (int i = 1; i < node->child_count; i++) {
                generate_ast_node(node->children[i]);
            }
            append_to_section(&prg_section, &prg_size, end_label);
        }
        break;

    default:
        fprintf(stderr, "Error: Unhandled AST node type %d\n", node->type);
        break;
    }
}

// Write PRG section to file
void write_prg_section(const char* prg_file) {
    if (prg_section) {
        FILE* prg_fp = fopen(prg_file, "w");
        if (prg_fp) {
            fprintf(prg_fp, "%s", prg_section);
            fclose(prg_fp);
        }
        else {
            fprintf(stderr, "Error: Unable to write to file %s\n", prg_file);
        }
    }
}

// Free resources
void free_rom_sections() {
    free(prg_section);
}

// Main function for code generation
void generate_code(ASTNode* root) {
    generate_ast_node(root);
    write_prg_section("output.prg");
    free_rom_sections();
}
