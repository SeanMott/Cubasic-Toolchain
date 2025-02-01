#pragma once

//defines the list of keywords the Cubasic compiler needs to parse
//for a full list see https://github.com/SeanMott/Cubasic-Toolchain/blob/Cubasic2/Docs/CubasicLanguageInstructions.md

#include <string>

namespace Cubasic::Data
{
	//defines the keywords
	enum class KeywordTypes
	{
		Function = 0,
		Print,
		Dim,
		For,
		If,
		Else,
		EndIf,
		End,
		Call,
		While,
		Break,
		Continue,
		Goto,
		Return,
		Halt,
		Input,
		Set,
		Next,
		Swap,
		Clear,
		Try,
		Catch,
		Pause,
		View,
		In,
		Then,
		To,

		Count
	};

	//defines the keyword strings
	static const char* KEYWORD_STRS[(int)KeywordTypes::Count] = {
		"FUNCTION", "PRINT", "DIM", "FOR", "IF", "ELSE", "ENDIF", "END", "CALL", "WHILE",
		"BREAK", "CONTINUE", "GOTO", "RETURN", "HALT", "INPUT", "SET", "NEXT",
		"SWAP", "CLEAR", "TRY", "CATCH", "PAUSE", "VIEW", "IN", "THEN", "TO"
	};

	//converts a keyword type into a string
	static inline std::string ConvertKeywordTypeToStr(const KeywordTypes& type)
	{
		if (type == KeywordTypes::Count)
			return "";

		return KEYWORD_STRS[(int)type];
	}

	//checks for keyword and returns it's type
	static inline KeywordTypes IsCubasicKeyword(const char* str)
	{
		for (size_t i = 0; i < (int)KeywordTypes::Count; ++i)
		{
			if (!strcmp(str, KEYWORD_STRS[i]))
				return (KeywordTypes)i;
		}

		return KeywordTypes::Count;
	}
}