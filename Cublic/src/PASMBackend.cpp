#include <Cublic/PASMBackend.hpp>

//generates a list of PASM instructions
std::string Cube::Backend::PASM::GeneratePASM(const std::vector<Token>& tokens, const CompilerSettings& settings)
{
	std::string str = "";

	//writes header
	str += "COMPILER_VERSION = " + settings.header.COMPILER_VERSION + "\n";
	str += "HEADER_CHIPSET = " + settings.header.HEADER_CHIPSET + "\n";
	str += "HEADER_LICENSEE = " + settings.header.HEADER_LICENSEE + "\n";
	str += "HEADER_MAGIC = " + settings.header.HEADER_MAGIC + "\n";
	str += "HEADER_RAMSIZE = " + settings.header.HEADER_RAMSIZE + "\n";
	str += "HEADER_ROMSIZE = " + settings.header.HEADER_ROMSIZE + "\n";
	str += "HEADER_RULEBREAKER = " + settings.header.HEADER_RULEBREAKER + "\n";
	str += "HEADER_TITLE = " + settings.header.HEADER_TITLE + "\n";
	str += "HEADER_VERSION = " + settings.header.HEADER_VERSION + "\n";
	str += "HEADER_ZIPDISKSIZE = " + settings.header.HEADER_ZIPDISKSIZE + "\n";
	str += "ROM_OUTPUT = " + settings.header.ROM_OUTPUT + "\n\n\n\n\n";

	return str;
}