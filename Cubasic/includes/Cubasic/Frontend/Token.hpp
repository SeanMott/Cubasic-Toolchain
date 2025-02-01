#pragma once

//defines a token and lexer of source code into tokens

#include <Cubasic/Util/Logger.hpp>
#include <Cubasic/Frontend/KeywordData.hpp>
#include <Cubasic/Frontend/OperatorData.hpp>

#include <Cubasic/Map/SymbolMap.hpp>

#include <vector>

namespace Cubasic::Token
{
	//defines a token type
	enum class TokenType
	{
		Identifier = 0,

		StringLiteral,
		DigitLiteral,

		Operator,

		Keyword,

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

		//defines specific bits of token data
		Data::KeywordTypes keywordType = Data::KeywordTypes::Continue;
		Data::OperatorTypes operatorType = Data::OperatorTypes::Count;
		uint64_t symbolID = 0; //the symbol ID in the map

		//prints a token
		inline void Print(Symbol::SymbolMap* map)
		{
			switch (type)
			{
			case TokenType::Identifier:
				fmt::print(fmt::emphasis::bold | fg(fmt::color::blue), "Identifier || Line: {}, Char: {}, Data: {}\n", line, charIndex, map->GetSymbol(symbolID)->name);
				return;

			case TokenType::StringLiteral:
				fmt::print(fmt::emphasis::bold | fg(fmt::color::blanched_almond), "String Literal || Line: {}, Char: {}, String: {}\n", line, charIndex, data);
				return;

			case TokenType::DigitLiteral:
				fmt::print(fmt::emphasis::bold | fg(fmt::color::brown), "Digit Literal || Line: {}, Char: {}, Digit: {}\n", line, charIndex, data);
				return;

			case TokenType::Operator:
				fmt::print(fmt::emphasis::bold | fg(fmt::color::coral), "Operator || Line: {}, Char: {}, Operator: {}\n", line, charIndex, Data::ConvertOperatorTypeToStr(operatorType));
				return;

			case TokenType::Keyword:
				fmt::print(fmt::emphasis::bold | fg(fmt::color::dark_green), "Keyword || Line: {}, Char: {}, Keyword: {}\n", line, charIndex, Data::ConvertKeywordTypeToStr(keywordType));
				return;

			case TokenType::Newline:
				fmt::print(fmt::emphasis::bold | fg(fmt::color::orange), "Newline || Line: {}, Char: {}\n", line, charIndex);
				return;

			case TokenType::EndOfFile:
				fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "End Of File || Line: {}, Char: {}\n", line, charIndex);
				return;
			}
		}
	};

	//lexes source code into tokens
	std::vector<Token> LexCodeIntoTokens(const std::string& rawCode, Symbol::SymbolMap& symbolMap);
}