#pragma once

//defines a lexer for cubebasic

#include <Cublic/CubasicKeywords.hpp>

#include <vector>
#include <string>

#define FMT_HEADER_ONLY
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/os.h>

namespace Cube::Frontend
{
	//defines a token type
	enum class TokenType
	{
		Identifier = 0,

		Operator,

		Literal_String,
		Literal_Digit,
		Literal_Float,

		Function,
		ControlFlow,

		Count
	};

	//defines a token
	struct Token
	{
		TokenType type = TokenType::Count;
		size_t lineCount = 0;

		Keywords::CubasicKeyword keyword = Keywords::CubasicKeyword::Count; //metadata for types

		std::string data = "";

		//prints the token
		inline void Print()
		{
			switch (type)
			{
			case TokenType::Identifier:
				fmt::print("Line: {} || Identifier: {}\n", lineCount, data);
				break;

			case TokenType::Operator:
				fmt::print("Line: {} || Operator: {}\n", lineCount, data);
				break;
		
			case TokenType::Literal_String:
				fmt::print("Line: {} || String Literal: {}\n", lineCount, data);
				break;

			case TokenType::Literal_Digit:
				fmt::print("Line: {} || Digit Literal: {}\n", lineCount, data);
				break;

			case TokenType::Literal_Float:
				fmt::print("Line: {} || Float Literal: {}\n", lineCount, data);
				break;

			case TokenType::Function:
				fmt::print("Line: {} || Function: {}\n", lineCount, data);
				break;

			case TokenType::ControlFlow:
				fmt::print("Line: {} || Control Flow: {}\n", lineCount, data);
				break;

			default:
				fmt::print("Line: {} || UNKNOWN TOKEN: {}\n", lineCount, data);
				break;
			}
		}
	};

	//lexes tokens
	std::vector<Token> LexTokens(const std::string& code);
}