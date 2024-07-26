#pragma once

//defines a lexer for cubebasic

#include <Cublic/CubasicKeywords.hpp>

#include <vector>
#include <string>

#define FMT_HEADER_ONLY
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/os.h>

namespace Cube
{
    //defines token
    struct Token
    {
        Keywords::TokenType type;
        std::string value = "";
    };

    //lexes the string into tokens
    std::vector<Token> Lex(const char* source);

    //prints a list of tokens
    void Print(const std::vector<Token>& tokens);
}