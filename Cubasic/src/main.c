/*
Cubasic compiler
*/

#include <Cubasic/Lexer.h>
#include <Cubasic/Parser.h>
#include <Cubasic/SemanticAnalysis.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//displays the tokens
static inline void display_tokens(Token** tokens, int token_count)
{
    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++)
    {
        Token* token = tokens[i];
        printf("Type: %d, Value: '%s', Line: %d, Column: %d\n",
            token->type, token->value, token->line, token->column);
    }
}

//displays the AST
static inline void display_ast(ASTNode* node, int depth) 
{
    for (int i = 0; i < depth; i++)
        printf("  ");

    printf("Node Type: %d, Value: '%s'\n", node->type, node->value ? node->value : "NULL");
    
    for (int i = 0; i < node->child_count; i++)
        display_ast(node->children[i], depth + 1);
}

//defines a file of code
typedef struct CodeFile
{
    size_t codeLength; //the code length
    char* code; //the code
} CodeFile;

//loads a file
static inline bool LoadFile(const char* fileFP, CodeFile* code)
{
    FILE* file = fopen(fileFP, "r");
    if (!file)
    {
        fprintf(stderr, "Error: Cannot open file '%s'\n", fileFP);
        return false;
    }

    // Read the source code
    fseek(file, 0, SEEK_END);
    code->codeLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    code->code = (char*)malloc(code->codeLength);
    fread(code->code, 1, code->codeLength, file);
    code->code[code->codeLength] = '\0';
    fclose(file);

    return true;
}

//unloads a code file
static inline void UnloadFile(CodeFile* code)
{
    if (code->code)
        free(code);
    code->code = NULL;
    code->codeLength = 0;
}

//entry point
int main(int argc, char* argv[])
{
    //prints the arguments
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <source_file> [--tokens] [--ast] [--symbols]\n", argv[0]);
        return EXIT_FAILURE;
    }

    //loads the code
    CodeFile code;
    if(!LoadFile(argv[1], &code))
        return EXIT_FAILURE;

    // Lexical analysis
    Lexer* lexer = init_lexer(code.code);
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
    for (int i = 0; i < token_count; i++)
        free_token(tokens[i]);
    free(tokens);
    free_lexer(lexer);
    free_ast_node(ast_root);
    free_symbol_table();
    
    //unloads code
    UnloadFile(&code);

    return EXIT_SUCCESS;
}
