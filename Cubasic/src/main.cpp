/*
Cubasic compiler
*/

#include <Cubasic/Arguments/ArgumentParser.hpp>

#include <Cubasic/Util/TranslationUnit.hpp>

#include <Cubasic/Frontend/Token.hpp>



//entry point
int main(int argc, char* argv[])
{
    //if none
    if (argc < 2)
    {
        Cubasic::Arguments::PrintHelpScreen();
        getchar();
        return 0;
    }

    //parses the arguments
    Cubasic::Arguments::CompilerSettings settings = Cubasic::Arguments::ParseArguments(argc, argv);

    //initalizes a symbol map
    Cubasic::Symbol::SymbolMap map;

    //loads the code
    Cubasic::Util::TranslationUnit translationUnit;
    translationUnit.LoadRawCode(settings.inputCubasicFiles[0]);

    //lexes the code
    std::vector<Cubasic::Token::Token> tokens = Cubasic::Token::LexCodeIntoTokens(translationUnit.rawCode, map);
    fmt::print("\n\n---TOKENS---\n\n");
    for (size_t t = 0; t < tokens.size(); ++t)
        tokens[t].Print(&map);
    translationUnit.DeleteCode(); //cleans up raw code, as we don't need it to take up RAM anymore

    //goes through the tokens and flatten it out into a IR representation
    //this removes all functions and turns them into a flat stream

    //compress the tokens into expression segments

    //writes the symbol map to file
    map.WriteToDisc(settings.outputSymbolMapFilePath);

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

    ///getchar();
    return 0;
}
