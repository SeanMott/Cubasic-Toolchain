//the compiler for making a "ROM" for the Cubeculator

#include <string>
#include <iostream>
#include <istream>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//entry point
int main()
{
	const std::string basicCubasic = "C:/Compilers/Cubasic-Toolchain/DemoForDevs/TestProject/Main.cubasic";

	//reads the code and sorts into a thread
	std::ifstream t(basicCubasic);
	t.seekg(0, std::ios::end);
	size_t size = t.tellg();
	std::string code(size, '\0');
	t.seekg(0);
	t.read(&code[0], size);
	t.close();

	//lex Cubasic
	//std::vector<Cube::Frontend::Token> tokens = Cube::Frontend::LexCode(code);

	//generate AST

	//choice backend

		//PASM generate

		//C++ generate

	return 0;
}