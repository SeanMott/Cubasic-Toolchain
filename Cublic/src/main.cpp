//the compiler for making a "ROM" for the Cubeculator

#include <Cublic/CompilerSettings.hpp>
#include <Cublic/TranslationUnit.hpp>
#include <Cublic/PASMBackend.hpp>

#include <string>
#include <iostream>
#include <istream>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

///----COMMANDS----///

//prints help
const char* COMMAND_STR_LONG_HELP = "--help";
const char* COMMAND_STR_SHORT_HELP = "-h";

//takes in a .cubasic file
const char* COMMAND_STR_LONG_SOURCE_SINGLE_FILE = "--single-source";
const char* COMMAND_STR_SHORT_SOURCE_SINGLE_FILE = "-ss";

//takes in a directory of .cubasic files
const char* COMMAND_STR_LONG_SOURCE_FILES = "--source";
const char* COMMAND_STR_SHORT_SOURCE_FILES = "-s";

//sets the output directory for PASM || defaults to the directory where the .cubasic file is

//sets the Chipset || defaults to Basic

//sets the Dev Name/License || defaults to "DevName"

//sets the RAM size || defaults to 4KB

//sets the ROM size || defaults to 64KB

//sets if rule breaker is enabled || defaults to false

//sets the title || defaults to "Game"

//sets the zip disk size || defaults to 1.44MB

//prints the help menu
static inline void PrintHelp()
{
	//name and version
	fmt::print("Cublic - Cubeulator Compiler Verstion: {}.{}.{} (major.minor.hotFix)\n\n\n", "0", "1", "0");

	//prints the help screen

	//takes in a .cubasic file

	//takes in a directory of .cubasic files

	//sets the output directory for PASM || defaults to the directory where the .cubasic file is

	//sets the Chipset || defaults to Basic

	//sets the Dev Name/License || defaults to "DevName"

	//sets the RAM size || defaults to 4KB

	//sets the ROM size || defaults to 64KB

	//sets if rule breaker is enabled || defaults to false

	//sets the title || defaults to "Game"

	//sets the zip disk size || defaults to 1.44MB
	
}

//parses the arguments
static inline bool ParseArguments(int args, const char* argv[], Cube::CompilerSettings& compilerSettings)
{
	//if no arguments
	if (args == 1)
	{
		//print help screen
		PrintHelp();
		return false;
	}

	//parse the arguments
	for (uint32_t i = 1; i < args; ++i)
	{
		//help menu
		if (!strcmp(argv[i], COMMAND_STR_LONG_HELP) || !strcmp(argv[i], COMMAND_STR_SHORT_HELP))
		{
			PrintHelp();
			return true;
		}

		//make sure we have enough arguments
		if (i + 1 < args)
		{
			//include a single file
			if (!strcmp(argv[i], COMMAND_STR_LONG_SOURCE_SINGLE_FILE) || !strcmp(argv[i], COMMAND_STR_SHORT_SOURCE_SINGLE_FILE))
			{
				//skip to the next argument and get the file path
				i++;

				//realistically we should check if the path is absolute and exists, but we can do that later cuz I am lazy :3

				compilerSettings.cubasicFiles.emplace_back(argv[i]);
				continue;
			}

			//include a whole directory
			//else if (!strcmp(argv[i], COMMAND_STR_LONG_SOURCE_FILES) || !strcmp(argv[i], COMMAND_STR_SHORT_SOURCE_FILES))
			//{
			//	//skip to the next argument and get the directory path
			//	i++;
			//	
			//	//go through the whole directory and add each to the cubasic files
			//
			//	continue;
			//}
		}

		//if we find something that isn't a fail command, if everything is ran correctly we should never see this
		fmt::print("\"{}\" is not a valid argument. Pass \"{}\" or \"{}\" or just run the exe with no flags to print the help screen.\n",
			argv[i], COMMAND_STR_LONG_HELP, COMMAND_STR_SHORT_HELP);
	}

	return true;
}

/*
//process the threads
static void Thread_Process(std::vector<Cube::TranslationUnit>& translationUnits)
{
	//lex Cubasic
	for (uint32_t i = 0; i < translationUnits.size(); ++i)
	{
		translationUnits[i].tokens = Cube::Frontend::LexTokens(translationUnits[i].cubasicSource);
		for (uint32_t t = 0; t < translationUnits[i].tokens.size(); ++t)
			translationUnits[i].tokens[t].Print();

		//generate AST

		//choice backend

			//PASM generate

			//C++ generate
	}
}

//entry point
int main(int args, const char* argv[])
{
	Cube::CompilerSettings compilerSettings;
	
	//override the aruments
	std::vector<const char*> argOverride = {
		argv[0],
		COMMAND_STR_LONG_SOURCE_SINGLE_FILE,
		"C:/Compilers/Cubasic-Toolchain/DemoForDevs/TestProject/Main.cubasic"
	};

	//parse arguments
	//if (!ParseArguments(args, argv, compilerSettings))
	if (!ParseArguments(argOverride.size(), argOverride.data(), compilerSettings))
	{
		getchar();
		return 0;
	}

	//we override the compiler settings to add three threads
	compilerSettings.threadCount = 1; //DO NOT CHANGE THIS, FOR LOOP WILL BREAK
	*/

	/*
	Every cubasic file is converted into a Translation Unit.
	Each thread stores a list of Translation Units and parses them.
	*/
	/*std::vector<std::vector<Cube::TranslationUnit>> translationUnitsPerThread; translationUnitsPerThread.resize(compilerSettings.threadCount); //the translation units stored per thread
	std::vector<std::thread> threads; threads.resize(compilerSettings.threadCount); //the thread for the group of translation units
	std::vector<bool> threadIsDone; threadIsDone.resize(compilerSettings.threadCount, false); //the per thread flag for when it's done
	uint32_t threadDoneCount = 0; //are the threads done?
	
	uint32_t currentThreadIndex = 0; //the current thread we are in
	for (uint32_t f = 0; f < compilerSettings.cubasicFiles.size(); ++f) //goes through the files
	{
		//reserves space
		if (f < compilerSettings.threadCount)
			translationUnitsPerThread[currentThreadIndex].reserve(5);

		Cube::TranslationUnit tu;

		//we do read the files in the main thread though, cuz I didn't feel like writing a IO thread manager for this compiler at the moment.
		//we could optimize a bit by not reading everything all at once
		std::ifstream t(compilerSettings.cubasicFiles[f]);
		t.seekg(0, std::ios::end);
		size_t size = t.tellg();
		tu.cubasicSource = std::string(size, '\0');
		t.seekg(0);
		t.read(&tu.cubasicSource[0], size);
		t.close();

		//adds the file to the current thread
		translationUnitsPerThread[currentThreadIndex].emplace_back(tu);

		//increment to the next thread
		currentThreadIndex++;
		if (currentThreadIndex >= compilerSettings.threadCount)
			currentThreadIndex = 0;
	}

	fmt::print("----Generating Lex Tokens and AST....\n\n\n\n");

	//goes through the threads and runs them
	//the reason we have the translation unit vector in a std::ref is since it is passed by refrence
	//we do this since each Translation Unit stores their source, lexed tokens, and AST
	for (uint32_t t = 0; t < compilerSettings.threadCount; ++t)
		threads[t] = std::thread(Thread_Process, std::ref(translationUnitsPerThread[t]));

	//wait for the threads to be done
	while (true)
	{
		for (uint32_t t = 0; t < compilerSettings.threadCount; ++t)
		{
			if (!threadIsDone[t] && threads[t].joinable())
			{
				threads[t].join();
				threadIsDone[t] = true;
				threadDoneCount++;
			}
		}
	
		//if all threads are done
		if (threadDoneCount >= compilerSettings.threadCount)
			break;
	}

	fmt::print("\n\nDone generating Lex Tokens and AST :3\n");

	getchar();
	return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//entry point
int main() 
{
    //compiler settings
    Cube::CompilerSettings compilerSettings;

    compilerSettings.cubasicFiles.emplace_back("C:/Compilers/Cubasic-Toolchain/DemoForDevs/TestProject/Main.cubasic");
    compilerSettings.workingDir = "C:/Compilers/Cubasic-Toolchain/DemoForDevs/TestProject";
    compilerSettings.outputDir = "C:/Compilers/Cubasic-Toolchain/DemoForDevs/TestProject/ASMTest";

	//loads code
	Cube::TranslationUnit translationUnit;
	translationUnit.filepathIsRelative = false;
	translationUnit.filepath = compilerSettings.cubasicFiles[0];
	translationUnit.ReadSource();

    //lex tokens
	translationUnit.tokens = Cube::Lex(translationUnit.cubasicSource.c_str());
    Cube::Print(translationUnit.tokens);

    //generate AST

    //generate ASM backend
	translationUnit.PASMSource = Cube::Backend::PASM::GeneratePASM(translationUnit.tokens, compilerSettings);

	//writes to file
	translationUnit.WritePASMToFile(std::string(compilerSettings.outputDir + "/PASM.s").c_str());

    getchar();
    return 0;
}