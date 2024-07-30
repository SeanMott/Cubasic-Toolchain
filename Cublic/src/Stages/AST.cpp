#include <Cublic/Stages/AST.hpp>

#include <map>

//generates a AST Node for HALT/STOP, stopping the program as soon as it is hit
static inline Cube::AST::ASTNode GenerateASTNode_Halt()
{
	Cube::AST::ASTNode node;
	node.type = Cube::AST::ASTNodeType::Halt;

	return node;
}

//generates a AST Node for NOP when a invalid token is hit
static inline Cube::AST::ASTNode GenerateASTNode_InvalidToken()
{
	Cube::AST::ASTNode node;
	node.type = Cube::AST::ASTNodeType::InvalidToken_NOP;

	return node;
}

//generates a AST Node for Pushing a Value from a General Purpose Register to the Stack
static inline Cube::AST::ASTNode GenerateASTNode_StackPush_ValueFromGeneralRegister(const uint8_t& registerIndex)
{
	Cube::AST::ASTNode node;
	node.type = Cube::AST::ASTNodeType::Stack_StoreGeneralRegisterValue;
	node.Metadata_GRegStoreOnStack.registerIndex = registerIndex;

	return node;
}

//generates a AST node for load immitate value into a register
static inline Cube::AST::ASTNode GenerateASTNode_LoadImmitateIntoRegister(const uint8_t& registerIndex, const std::string& value)
{
	Cube::AST::ASTNode node;
	node.type = Cube::AST::ASTNodeType::Load_ImmitateValueIntoGeneralRegister;
	node.Metadata_iValueLoadInGReg.registerIndex = registerIndex;
	node.Metadata_iValueLoadInGReg.value = value;

	return node;
}

//generates a AST node for printing
static inline Cube::AST::ASTNode GenerateASTNode_SystemIO_Print(const uint8_t& registerIndex)
{
	Cube::AST::ASTNode node;
	node.type = Cube::AST::ASTNodeType::System_Print;
	node.Metadata_systemPrint.registerIndex = registerIndex;

	return node;
}

//generates a AST of a translation unit
std::vector<Cube::AST::ASTNode> Cube::AST::GenerateASTFromTranslationUnit(const std::vector<Cube::Token>& tokens)
{
	std::vector<Cube::AST::ASTNode> AST;
	const size_t tokenCount = tokens.size();
	AST.reserve(tokenCount);

	//goes through the tokens and generate a first pass AST
	for (size_t t = 0; t < tokenCount; ++t)
	{
		//halt
		if(tokens[t].type == Cube::Keywords::TokenType::STOP)
		{
			AST.emplace_back(GenerateASTNode_Halt());
			continue;
		}

		//nop
		else if (tokens[t].type == Cube::Keywords::TokenType::INVALID)
		{
			AST.emplace_back(GenerateASTNode_InvalidToken());
			continue;
		}

		//include other code

		//print statment
		if (tokens[t].type == Cube::Keywords::TokenType::PRINT)
		{
			//if it's a string literal we itterlate through the string, first storing all the values of the registers we are going to use
			//then load immitate hex values of the string chars in thoses registers. Letting us print very quickly by using the CPU cache
			if (t + 1 < tokenCount && tokens[t + 1].type == Keywords::TokenType::STRING_LITERAL)
			{
				//stores the string value of the next token
				t++;
				register const std::string dataStr1 = tokens[t].value;
				register const size_t registersNeededInTotal = dataStr1.size(); //get the number of registers we need

				//based on the number of registers needed, we store the contents of the registers before we override them
				const bool registersNeedToBeReused = (registersNeededInTotal > 8 ? true : false);

				//itterate through the string literal and generate a array of what registers we will need to use
				//taking into account any duplicate chars we can save a instruction on
				std::map<char, uint8_t> registerToCharMap;
				uint8_t registerIndex = 0;
				for (size_t c = 0; c < registersNeededInTotal; ++c)
				{
					//if it already exists
					if (registerToCharMap.find(dataStr1[c]) != registerToCharMap.end())
						continue;

					registerToCharMap[dataStr1[c]] = registerIndex; //sets the register we will use

					//increment
					registerIndex++;
					if (registerIndex >= 8)
						registerIndex = 0;
				}

				//go through all the registers we need and generate Stack Push operations so we can store them for later
				bool registerAlreadyStored[8]; memset(registerAlreadyStored, false, sizeof(bool) * 8); //quick and dirty array for registers we have already stored the value of, since if we already have this is clearly a register we reuse later and can just nuke
				for (auto& reg : registerToCharMap)
				{
					if (registerAlreadyStored[reg.second])
						continue;

					AST.emplace_back(GenerateASTNode_StackPush_ValueFromGeneralRegister(reg.second));
					registerAlreadyStored[reg.second] = true;
				}

				//itterate through the string and write as many immitate hex values we can before needing to print
				//then load more values into the registers and print
				memset(registerAlreadyStored, false, sizeof(bool) * 8); //we're reusing this to know when we need to need to flush register data
				for (auto& reg : registerToCharMap)
				{
					//if data needs to be flushed
					if (registerAlreadyStored[reg.second])
					{
						for (uint8_t r = 0; r < 8; ++r)
						{
							if (registerAlreadyStored[r])
								AST.emplace_back(GenerateASTNode_SystemIO_Print(r));
						}
						memset(registerAlreadyStored, false, sizeof(bool) * 8);
					}

					//writes data
					AST.emplace_back(GenerateASTNode_LoadImmitateIntoRegister(reg.second,
						Cube::AST::ASTNodeMetadata_Load_ImmitateValue_GeneralPurposeRegister::ConvertValueToHexString(reg.first)));
					registerAlreadyStored[reg.second] = true;
				}
			}
		}
	}

	return AST;
}