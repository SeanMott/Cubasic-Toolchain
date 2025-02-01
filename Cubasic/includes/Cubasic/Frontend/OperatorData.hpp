#pragma once

//defines operators in Cubasic

#include <string>

namespace Cubasic::Data
{
	//defines the operator
	enum class OperatorTypes
	{
		Left_Bracket = 0,
		Right_Bracket,

		Left_Param,
		Right_Param,

		Left_GreaterThen,
		Right_LessThen,

		Equals,
		Star,

		Count
	};

	//defines operators
	static const char* OPERATOR_STRS[(int)OperatorTypes::Count] = {
		"[", "]", "(", ")", "<", ">", "=", "*"
	};

	//converts a operator type into a string
	static inline std::string ConvertOperatorTypeToStr(const OperatorTypes& type)
	{
		if (type == OperatorTypes::Count)
			return "";

		return OPERATOR_STRS[(int)type];
	}

	//checks for a operator
	static inline OperatorTypes IsCubasicOperator(const char str)
	{
		for (size_t i = 0; i < (int)OperatorTypes::Count; ++i)
		{
			if (!strcmp(&str, OPERATOR_STRS[i]))
				return (OperatorTypes)i;
		}

		return OperatorTypes::Count;
	}
}