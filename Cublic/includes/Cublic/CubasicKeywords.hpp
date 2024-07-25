#pragma once

//defines Cubasic keywords

#include <string>

namespace Cube::Keywords
{
	//defines keyword enums
	enum class CubasicKeyword
	{
		STOP = 0,
		INCLUDE,
		FUNCTION,
		END,
		PRINT,
		CALL,
		RETURN,
		INPUT,
		IF, ELSE, THEN,
		NEXT,
		FOR, IN,
		SET,
		GOTO, GOSUB,

		Count
	};

	//defines keyword strings
	static const uint32_t CUBASIC_KEYWORD_STR_COUNT = (uint32_t)CubasicKeyword::Count;
	static const char* CUBASIC_KEYWORD_STRS[CUBASIC_KEYWORD_STR_COUNT] = {"STOP", "INCLUDE", "FUNCTION", "END",
	"PRINT", "CALL", "RETURN", "INPUT", "IF", "ELSE", "THEN", "NEXT", "FOR", "IN", "SET", "GOTO", "GOSUB"};

	//is the keyword
	static inline bool IsCubasicKeyword(const char* str, CubasicKeyword& keyword)
	{
		for (uint32_t i = 0; i < CUBASIC_KEYWORD_STR_COUNT; ++i)
		{
			if (!strcmp(str, CUBASIC_KEYWORD_STRS[i]))
			{
				keyword = (CubasicKeyword)i;
				return true;
			}
		}

		return false;
	}
}