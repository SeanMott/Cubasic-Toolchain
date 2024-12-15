/*
Cubasic compiler
*/

#include <Cubasic/Lexer.h>
#include <Cubasic/Parser.h>
#include <Cubasic/SemanticAnalysis.h>

#include <Cubasic/TranslationUnit.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

    //compiler flags
    const bool printTokens = (argc > 2 && !strcmp(argv[2], "--tokens")),
        printAST = (argc > 2 && !strcmp(argv[2], "--ast")),
        printSymbolTable = !(argc > 2 && strcmp(argv[2], "--symbols"));

    //loads the code
    CodeFile code; code.code = NULL; code.codeLength = 0;
    if(!LoadFile(argv[1], &code))
        return EXIT_FAILURE;

    //parse code into Tokens
    Lexer* lexer = init_lexer(&code);
    TranslationUnit translationUnit; translationUnit.tokens = NULL; translationUnit.tokenCount = 0;
    do {
        Token* t = AddToken(&translationUnit, get_next_token(lexer));
        PrintToken(t);

        //break or unrecognized
        if (t->type == TOKEN_EOF || t->type == TOKEN_ERROR)
            break;

    } while (GetLatestToken(&translationUnit)->type != TOKEN_EOF);

    //generate AST
    Parser* parser = init_parser(&translationUnit);
    ASTNode* ast_root = parse_program(parser);
    validate_ast(ast_root, 0);

    //clean up tokens
    DestroyTranslationUnit(&translationUnit);
    free_lexer(lexer);

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

    //clean up AST
    free_ast_node(ast_root);

    //clean up Symbol Table
    free_symbol_table();
    
    //unloads code
    UnloadFile(&code);

    return EXIT_SUCCESS;
}
