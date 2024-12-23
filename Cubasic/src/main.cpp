/*
Cubasic compiler
*/

//#include <Cubasic/Lexer.hpp>
//#include <Cubasic/Parser.hpp>
//#include <Cubasic/SemanticAnalysis.hpp>
//
//#include <Cubasic/TranslationUnit.hpp>
//
//#include <Cubasic/Frontend/Token.hpp>
//#include <Cubasic/Frontend/AST.hpp>

#include <Cubasic/Util/TranslationUnit.hpp>

#include <Cubasic/Frontend/Token.hpp>
//
////displays the AST
//static inline void display_ast(ASTNode* node, int depth)
//{
//    for (int i = 0; i < depth; i++)
//        printf("  ");
//
//    printf("Node Type: %d, Value: '%s'\n", node->type, node->value ? node->value : "NULL");
//
//    for (int i = 0; i < node->child_count; i++)
//        display_ast(node->children[i], depth + 1);
//}

//entry point
int main(int argc, char* argv[])
{
    //prints the arguments and how to use
    //if (argc < 2)
    //{
    //    fprintf(stderr, "Usage: %s <source_file> [--tokens] [--ast] [--symbols]\n", argv[0]);
    //    return EXIT_FAILURE;
    //}

    //compiler flags
    const bool printTokens = (argc > 2 && !strcmp(argv[2], "--tokens")),
        printAST = (argc > 2 && !strcmp(argv[2], "--ast")),
        printSymbolTable = !(argc > 2 && strcmp(argv[2], "--symbols"));

    //loads the code
    Cubasic::Util::TranslationUnit translationUnit;
    translationUnit.LoadRawCode("C:/Compilers/Cubasic2/Cubasic-Toolchain/simple.cbs");

    //lexes the code
    std::vector<Cubasic::Token::Token> tokens = Cubasic::Token::LexCodeIntoTokens(translationUnit.rawCode);
    fmt::print("\n\n---TOKENS---\n\n");
    for (size_t t = 0; t < tokens.size(); ++t)
        tokens[t].Print();
    translationUnit.DeleteCode(); //cleans up raw code, as we don't need it to take up RAM anymore

    //generate AST Node

    

    ////generate AST
    //Parser* parser = init_parser(&translationUnit);
    //ASTNode* ast_root = ASTTree_GenerateASTTree(parser);
    //validate_ast(ast_root, 0);

    ////clean up tokens
    //translationUnit.Destroy();
    //free_lexer(lexer);

    //if (printAST)
    //{
    //    printf("AST:\n");
    //    display_ast(ast_root, 0);
    //}

    //if (printSymbolTable)
    //{
    //    printf("Symbol Table:\n");
    //    print_symbol_table();
    //}

    ////clean up AST
    //free_ast_node(ast_root);

    ////clean up Symbol Table
    //free_symbol_table();

    getchar();
    return EXIT_SUCCESS;
}
