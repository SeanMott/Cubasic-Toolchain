#pragma once

//defines a list of arguments

#include <Cubasic/Util/Logger.hpp>

namespace Cubasic::Arguments
{
	//---arguments

	//include a single source file
#define CUBASIC_ARG_STRING_NAME_INCLUDE_SOURCE_FILE "-s"
	//include a whole directory of source files
#define CUBASIC_ARG_STRING_NAME_INCLUDE_SOURCE_DIRECTORY "-sdir"

	//sets the output single file
#define CUBASIC_ARG_STRING_NAME_OUT_ASM_FILE "-o"
		//sets the output assembly directory
#define CUBASIC_ARG_STRING_NAME_OUT_ASM_FILES "-odir"

	//sets the mode to output a optimized binary ROM

	//sets the mode to output a plain text file

	//should we output a symbol map (default on)

	//---parsing

	//if no arguments are given print the help screen
	static inline void PrintHelpScreen()
	{
		fmt::print("Cubasic Compiler || Compiles Cubasic code into Cubix ASM.\n\n");
		fmt::print("---EXAMPLE USEAGE---\n\nCubasic -s \"src/helloworld.cbs\" -o \"asm/hello.cir\n\n");
		fmt::print("---ARGS---\n\n");
	}
}