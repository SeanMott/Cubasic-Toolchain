#pragma once

//defines a lexer for cubebasic

#include <vector>
#include <string>

namespace Cube::Frontend
{
	//defines a token type
	enum class TokenType
	{
		Count
	};

	//defines a token
	struct Token
	{
		TokenType type = TokenType::Count;
		size_t lineCount = 0;
		std::string code = "";
	};

	//lexes tokens
	std::vector<std::string> LexTokens(const std::string& code);
}