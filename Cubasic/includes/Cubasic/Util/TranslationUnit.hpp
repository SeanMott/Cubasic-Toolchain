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
			FILE* file = nullptr;
			if (!std::filesystem::exists(fp) || !(file = fopen(fp.string().c_str(), "r")))
			{
				fmt::print("Cubasic Compiler Error: IO || LoadRawCode || Failed to load a Cubasic file at \"{}\"\n",
					fp.string());
				return false;
			}
			filepath = fp;

			// Read the source code
			fseek(file, 0, SEEK_END);
			const long length = ftell(file);
			fseek(file, 0, SEEK_SET);
			rawCode.resize(length);
			fread(rawCode.data(), 1, length, file);
			fclose(file);

			return true;
		}

		//deletes the code
		inline void DeleteCode() { rawCode.clear(); }
	};
}