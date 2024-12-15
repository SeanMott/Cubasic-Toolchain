

#include <Cubasic/Lexer.h>
#include <Cubasic/Parser.h>
#include <Cubasic/SemanticAnalysis.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_tokens(Token** tokens, int token_count) {
    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        Token* token = tokens[i];
        printf("Type: %d, Value: '%s', Line: %d, Column: %d\n",
            token->type, token->value, token->line, token->column);
    }
}

void display_ast(ASTNode* node, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("Node Type: %d, Value: '%s'\n", node->type, node->value ? node->value : "NULL");
    for (int i = 0; i < node->child_count; i++) {
        display_ast(node->children[i], depth + 1);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file> [--tokens] [--ast] [--symbols]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* source_file = argv[1];
    FILE* file = fopen(source_file, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", source_file);
        return EXIT_FAILURE;
    }

    // Read the source code
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* source_code = (char*)malloc(length);
    fread(source_code, 1, length, file);
    source_code[length] = '\0';
    fclose(file);

    // Lexical analysis
    Lexer* lexer = init_lexer(source_code);
    Token* token;
    Token** tokens = NULL;
    int token_count = 0;
    do {
        token = get_next_token(lexer);
        tokens = (Token**)realloc(tokens, sizeof(Token*) * (token_count + 1));
        tokens[token_count++] = token;
    } while (token->type != TOKEN_EOF);

    if (argc > 2 && strcmp(argv[2], "--tokens") == 0) {
        display_tokens(tokens, token_count);
    }

    // Parsing
    Parser* parser = init_parser(tokens, token_count);
    ASTNode* ast_root = parse_program(parser);

    if (argc > 2 && strcmp(argv[2], "--ast") == 0) {
        printf("AST:\n");
        display_ast(ast_root, 0);
    }

    // Semantic analysis
    validate_ast(ast_root, 0);

    if (argc > 2 && strcmp(argv[2], "--symbols") == 0) {
        printf("Symbol Table:\n");
        print_symbol_table();
    }

    // Cleanup
    for (int i = 0; i < token_count; i++) {
        free_token(tokens[i]);
    }
    free(tokens);
    free_lexer(lexer);
    free_ast_node(ast_root);
    free_symbol_table();
    free(source_code);

    return EXIT_SUCCESS;
}
