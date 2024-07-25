#pragma once

//defines a translation unit

#include <Cublic/Lex.hpp>

#include <string>

namespace Cube
{
	//defines a translation unit
	struct TranslationUnit
	{
		std::string cubasicSource = ""; //the cubasic source code

		//the AST

		std::vector<Cube::Frontend::Token> tokens; //the lexed code
	};
}