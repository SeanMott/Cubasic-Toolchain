#pragma once

//defines the compiler settings

#include <Cublic/PASMHeader.hpp>

#include <vector>

namespace Cube
{
	//defines compiler settings
	struct CompilerSettings
	{
		uint32_t threadCount = 1; //the number of threads to be used, if 1 is passed in we are running this thing single threaded

		PASMHeader header; //defines the header

		std::string outputDir = ""; //the output directory for PASM
		std::string workingDir = ""; //the working directory for where includes are relative to

		std::vector<std::string> cubasicFiles; //the .cubasic files to include
	};
}