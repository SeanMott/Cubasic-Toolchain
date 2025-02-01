#pragma once

//defines the compiler settings

#include <filesystem>
#include <vector>

namespace Cubasic::Arguments
{
	//defines the settings
	struct CompilerSettings
	{
		std::vector<std::filesystem::path> inputCubasicFiles;
	};
}