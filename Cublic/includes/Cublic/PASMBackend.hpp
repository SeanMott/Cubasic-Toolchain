#pragma once

//defines a generator for PASM Backend

#include <Cublic/Lexer.hpp>
#include <Cublic/CompilerSettings.hpp>

#include <string>

namespace Cube::Backend::PASM
{
	//defines a PASM instruction type

	//defines a PASM instruction

	//generates a list of PASM instructions
	std::string GeneratePASM(const std::vector<Token>& tokens, const CompilerSettings& settings);
}