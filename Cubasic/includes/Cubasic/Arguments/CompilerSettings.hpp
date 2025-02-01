#pragma once

//defines the compiler settings

#include <filesystem>
#include <vector>

namespace Cubasic::Arguments
{
	//defines the settings
	struct CompilerSettings
	{
		std::filesystem::path outputSymbolMapFilePath = ""; //the symbol map file path

		std::vector<std::filesystem::path> inputCubasicFiles; //the source files
	};
}