#pragma once

//defines a translation unit

#include <Cublic/Stages/Lexer.hpp>

#include <string>
#include <fstream>

namespace Cube
{
	//defines a translation unit
	struct TranslationUnit
	{
		bool filepathIsRelative = false; //is the filepath relative (true) or absolute (false)

		std::string filepath = ""; //the filepath to the cubasic source
		std::string cubasicSource = ""; //the cubasic source code
		std::string PASMSource = ""; //the PASM source code

		//the AST

		std::vector<Cube::Token> tokens; //the lexed code

		//reads source code from the file
		inline bool ReadSource()
		{
			//if it's relative we generate the absolute

			//loads code
			std::ifstream t(filepath);
			t.seekg(0, std::ios::end);
			size_t size = t.tellg();
			cubasicSource = std::string(size, '\0');
			t.seekg(0);
			t.read(&cubasicSource[0], size);
			t.close();

			return true;
		}

		//qrites the PASM source code
		inline bool WritePASMToFile(const char* outputFilepath)
		{
			std::ofstream myfile;
			myfile.open(outputFilepath);
			myfile << PASMSource;
			myfile.close();

			return true;
		}
	};
}