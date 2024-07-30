#pragma once

//defines the header injected at the top of PASM

#include <string>

namespace Cube
{
	//sets the number of lines used for padding and filling the header for PASM.
	//this is defined in the spec
	#define PASM_HEADER_MIN_LINE_COUNT 17

	/*
	Example header

		COMPILER_VERSION = 1.0
		HEADER_CHIPSET = Basic
		HEADER_LICENSEE = DevName
		HEADER_MAGIC = FCUB
		HEADER_RAMSIZE = 4KB
		HEADER_ROMSIZE = 64KB
		HEADER_RULEBREAKER = False
		HEADER_TITLE = Example Game
		HEADER_VERSION = 1.0
		HEADER_ZIPDISKSIZE = 1.44MB
		ROM_OUTPUT = game.FCUB
	*/

	struct PASMHeader
	{
		std::string COMPILER_VERSION = "1.0";
		std::string HEADER_CHIPSET = "Basic";
		std::string HEADER_LICENSEE = "DevName";
		std::string HEADER_MAGIC = "FCUB";
		std::string HEADER_RAMSIZE = "4KB";
		std::string HEADER_ROMSIZE = "64KB";
		std::string HEADER_RULEBREAKER = "False";
		std::string HEADER_TITLE = "Example Game";
		std::string HEADER_VERSION = "1.0";
		std::string HEADER_ZIPDISKSIZE = "1.44MB";
		std::string ROM_OUTPUT = "game.FCUB";
	};

}