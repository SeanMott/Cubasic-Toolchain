#pragma once

//defines Cubasic keywords

#include <string>

namespace Cube::Keywords
{
    // Token types
    enum class TokenType
    {
        INCLUDE = 0,

        PRINT,

        CALL,
        INPUT,

        IF,
        ELSE,

        GOTO,
        GOSUB,

        THEN,
        NEXT,
        FOR,
        IN,

        SET,

        FUNCTION,

        END,
        RETURN,

        STOP,

        STRING_LITERAL,
        DIGIT_LITERAL,
        //HEX_LITERAL,

        IDENTIFIER,

        OPERATOR,

        END_OF_FILE, INVALID
    };

    static TokenType keywordToTokenType(const char* value) {
        static const struct {
            const char* keyword;
            TokenType type;
        } keywords[] = {
            {"STOP", TokenType::STOP}, {"INCLUDE", TokenType::INCLUDE}, {"FUNCTION", TokenType::FUNCTION},
            {"END", TokenType::END}, {"PRINT", TokenType::PRINT}, {"CALL", TokenType::CALL}, {"RETURN", TokenType::RETURN},
            {"INPUT", TokenType::INPUT}, {"IF", TokenType::IF}, {"ELSE", TokenType::ELSE}, {"THEN", TokenType::THEN},
            {"NEXT", TokenType::NEXT}, {"FOR", TokenType::FOR}, {"IN", TokenType::IN}, {"SET", TokenType::SET},
            {"GOTO", TokenType::GOTO}, {"GOSUB", TokenType::GOSUB}
        };

        for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
            if (strcmp(value, keywords[i].keyword) == 0) {
                return keywords[i].type;
            }
        }
        return TokenType::IDENTIFIER;
    }
}