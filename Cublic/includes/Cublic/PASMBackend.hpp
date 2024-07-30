#pragma once

//defines a generator for PASM Backend

#include <Cublic/Stages/AST.hpp>
#include <Cublic/Compiler/CompilerSettings.hpp>

#include <string>

namespace Cube::Backend::PASM
{
	//defines a PASM instruction type

	//defines a PASM instruction

	//generates a list of PASM instructions
	std::string GeneratePASM(const std::vector<AST::ASTNode>& AST, const CompilerSettings& settings);
}