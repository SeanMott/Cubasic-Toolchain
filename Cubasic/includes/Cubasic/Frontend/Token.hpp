#pragma once

//defines a token and lexer of source code into tokens

#include <string>
#include <vector>

namespace Cubasic::Token
{
	//defines the keyword count
	static const size_t KEYWORD_STRINGS_COUNTS = 24;

	//defines the keywords
	static const char* KEYWORD_STRINGS[KEYWORD_STRINGS_COUNTS] = {
		"FUNCTION", "PRINT", "DIM", "FOR", "IF", "ELSE", "ENDIF", "END", "CALL", "WHILE",
		"BREAK", "CONTINUE", "GOTO", "RETURN", "HALT", "INPUT", "SET", "NEXT",
		"SWAP", "CLEAR", "TRY", "CATCH", "PAUSE", "VIEW"
	};

	// Check if a string is a keyword
	static inline bool IsString_Keyword(const char* str)
	{
		for (size_t i = 0; i < KEYWORD_STRINGS_COUNTS; i++)
		{
			if (!strcmp(str, KEYWORD_STRINGS[i]))
				return true;
		}
		return false;
	}

	//defines a token type
	enum class TokenType
	{
		Comment = 0,

		StringLiteral,
		DigitLiteral,

		Identifier,

		Operator,
		Punctuation,

		Keyword,

		Expression,

		Newline,

		EndOfFile,
		Count
	};

	//defines a token
	struct Token
	{
		TokenType type = TokenType::Count;
		size_t line = 0, charIndex = 0, sourceIndex = 0;
		std::string data = "";
	};

	//lexes source code into tokens
	std::vector<Token> LexCodeIntoTokens(const std::string& rawCode);
}