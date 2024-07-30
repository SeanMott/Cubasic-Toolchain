#pragma once

//defines a AST graph

#include <Cublic/Stages/Lexer.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace Cube::AST
{
	//defines a AST type
	enum class ASTNodeType
	{
		Stack_Pop = 0, //poped a value from the Stack
		//pushed a value to the Stack

		Stack_StoreGeneralRegisterValue, //stored a value from a register on the Stack
		//stored a value from the Stack into a register

		//loads a immitate value into a register
		Load_ImmitateValueIntoGeneralRegister,

		System_Print, //Print operation

		Halt, //halts the program
		InvalidToken_NOP, //a invalid token was found so we inject a NOP

		Count
	};

	//defines a AST function metadata

	//defines a AST if metadata

	//defines metadata for printing based on a General Purpose Register
	struct ASTNodeMetadata_SystemIO_Print
	{
		uint8_t registerIndex = 0;
	};

	//defines metadata for pushing data from a General Purpose Register to the Stack for storage
	struct ASTNodeMetadata_StoreGeneralPurposeRegisterValueInStack
	{
		uint8_t registerIndex = 0;
	};

	//defines metadata for immitate loading a value into a General Purpose Register
	struct ASTNodeMetadata_Load_ImmitateValue_GeneralPurposeRegister
	{
		uint8_t registerIndex = 0;
		std::string value = "";

		//converts the value to Hex string
		static inline std::string ConvertValueToHexString(const char c)
		{
			std::stringstream ss;
			ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
			return ss.str();
		}
	};

	//defines a AST Node
	struct ASTNode
	{
		ASTNodeType type = ASTNodeType::Count;

		//metadata for the node
		ASTNodeMetadata_StoreGeneralPurposeRegisterValueInStack Metadata_GRegStoreOnStack;
		ASTNodeMetadata_Load_ImmitateValue_GeneralPurposeRegister Metadata_iValueLoadInGReg;
		ASTNodeMetadata_SystemIO_Print Metadata_systemPrint;
	};

	//defines a AST node of the program
	struct ASTTree
	{
		//defines all the register
	};

	//generates a AST of a translation unit
	std::vector<ASTNode> GenerateASTFromTranslationUnit(const std::vector<Cube::Token>& tokens);
}