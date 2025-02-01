#pragma once

//defines the argument parser

#include <Cubasic/Arguments/ArgumentList.hpp>
#include <Cubasic/Arguments/CompilerSettings.hpp>

namespace Cubasic::Arguments
{
	//parses the arguments
	static CompilerSettings ParseArguments(const int argc, char* argv[])
	{
		CompilerSettings settings;

		for (size_t i = 1; i < argc; ++i)
		{
			if (!strcmp(CUBASIC_ARG_STRING_NAME_INCLUDE_SOURCE_FILE, argv[i]))
			{
				i++;
				settings.inputCubasicFiles.emplace_back(argv[i]);
			}

			else if (!strcmp(CUBASIC_ARG_STRING_NAME_MAP_OUTPUT_FILE_NAME, argv[i]))
			{
				i++;
				settings.outputSymbolMapFilePath = argv[i];
			}
		}

		return settings;
	}
	 
}