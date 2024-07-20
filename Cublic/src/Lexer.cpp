#include <Cublic/Lex.hpp>

//lexes tokens
std::vector<Cube::Frontend::Token> Cube::Frontend::LexTokens(const std::string& code)
{
	std::vector<Cube::Frontend::Token> tokens; tokens.resize(20);

	//prints
	std::string line = ""; size_t lineCount = 1;
	for(size_t c = 0; c < code.size(); ++c)
	{ 
		//newline
		if (code[c] == '\n')
		{
			fmt::print(fmt::fg(fmt::color::cyan), "Line: {} ", lineCount);
			fmt::print(fmt::fg(fmt::color::fire_brick), " || ");
			fmt::print("{}\n", line);
			
			line = "";
			lineCount++;
			continue;
		}

		//skips tabs
		if (code[c] == '\t')
			continue;

		//adds line data
		line += code[c];
	}

	return tokens;
}