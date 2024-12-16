#pragma once

//defines a translation unit

#include <Cubasic/Util/Logger.hpp>

#include <filesystem>
#include <string>

namespace Cubasic::Util
{
	//defines a translation unit
	struct TranslationUnit
	{
		std::filesystem::path filepath; //the file path
		std::string fileName = "", //the file name

			rawCode = "";//the code loaded

		//the tokens from lexing the code

		//the AST Nodes generated from the tokens

		//loads the raw code
		inline bool LoadRawCode(const std::filesystem::path& fp)
		{
			//if it exists
			if (!std::filesystem::exists(fp))
			{
				fmt::print("Wireframe Error: Desktop Swapchain || Create || Failed to create a Swapchain!\n");
			}

			return true;
		}
	};
}