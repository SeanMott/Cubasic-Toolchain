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
        PrintToken(tokens[i]);
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

//entry point
int main(int argc, char* argv[])
{
    //prints the arguments and how to use
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <source_file> [--tokens] [--ast] [--symbols]\n", argv[0]);
        return EXIT_FAILURE;
    }

    //compiler tags
    bool printTokens = (argc > 2 && !strcmp(argv[2], "--tokens")),
        printAST = (argc > 2 && !strcmp(argv[2], "--ast")),
        printSymbolTable = !(argc > 2 && strcmp(argv[2], "--symbols"));

    //loads the code
    CodeFile code;
    if(!LoadFile(argv[1], &code))
        return EXIT_FAILURE;

    //parse tokens
    Lexer* lexer = init_lexer(&code);
    Token* token;
    Token** tokens = NULL;
    int token_count = 0;
    do {
        token = get_next_token(lexer);
        tokens = (Token**)realloc(tokens, sizeof(Token*) * (token_count + 1));
        tokens[token_count++] = token;
        PrintToken(token);

        //break or unrecognized
        if (token->type == TOKEN_EOF || token->type == TOKEN_ERROR)
            break;

    } while (token->type != TOKEN_EOF);

    if (printTokens)
        display_tokens(tokens, token_count);

    //generate AST
    Parser* parser = init_parser(tokens, token_count);
    ASTNode* ast_root = parse_program(parser);
    validate_ast(ast_root, 0);

    if (printAST)
    {
        printf("AST:\n");
        display_ast(ast_root, 0);
    }

    if (printSymbolTable)
    {
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
