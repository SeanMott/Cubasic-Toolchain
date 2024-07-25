#include <Cublic/Lex.hpp>

//generates a string literal
static inline Cube::Frontend::Token GenerateToken_Literal_String(const size_t& lineCount, const std::string& data)
{
	Cube::Frontend::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = Cube::Frontend::TokenType::Literal_String;
	return t;
}

//generates a keyword
static inline Cube::Frontend::Token GenerateToken_Keyword(const size_t& lineCount, const std::string& data,
	const Cube::Keywords::CubasicKeyword& keyword)
{
	Cube::Frontend::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = Cube::Frontend::TokenType::Function;
	t.keyword = keyword;
	return t;
}

//generates a operator

//generates a identifier
static inline Cube::Frontend::Token GenerateToken_Identifier(const size_t& lineCount, const std::string& data)
{
	Cube::Frontend::Token t;
	t.data = data; t.lineCount = lineCount;
	t.type = Cube::Frontend::TokenType::Identifier;
	return t;
}

//process word data
static inline void ProcessWord(size_t& lineCount, std::string& data, std::vector<Cube::Frontend::Token>& tokens)
{
	if (data.empty())
		return;

	Cube::Keywords::CubasicKeyword keyword = Cube::Keywords::CubasicKeyword::Count;

	//keyword
	if (Cube::Keywords::IsCubasicKeyword(data.c_str(), keyword))
	{
		tokens.emplace_back(GenerateToken_Keyword(lineCount, data, keyword));
		data = "";
	}
}

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

		//if space

		//if string literal
		if (code[c] == '"')
		{
			//process old stuff
			ProcessWord(lineCount, line, tokens);

			line = "";
			//goes till the "
			while (code[c] != '"')
			{
				c++;
				if (code[c] == '"')
					break;
				line += code[c];
			}
			c++;

			tokens.emplace_back(GenerateToken_Literal_String(lineCount, line));
			line = "";
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