#include <Cubasic/Frontend/Token.hpp>

std::string code = "";
size_t currentSourceIndex = 0, //the current token index
codeLength = 0, //the code length

lineCount = 1, charCount = 0; //the current line and char index

//resets the lexing data
static inline void SetCodeToLex(const std::string& rawCode)
{
	code = rawCode;
	codeLength = code.size();
	currentSourceIndex = 0;
	lineCount = 1; charCount = 0;
}

//peeks the next char
static inline char PeekNextChar()
{
	return (currentSourceIndex + 1 >= codeLength ? -1 : code[currentSourceIndex + 1]);
}

//gets the current char
static inline char GetCurrentChar()
{
	return (currentSourceIndex >= codeLength ? -1 : code[currentSourceIndex]);
}

//gets the next char
static inline char GetNextChar()
{
	charCount++;
	currentSourceIndex++;
	char current = GetCurrentChar();
	if (current == '\n')
	{
		lineCount++;
		charCount = 0;
	}
	return current;
}

//generates a new line token
static inline Cubasic::Token::Token GenerateToken_NewLine()
{
	Cubasic::Token::Token t;
	t.type = Cubasic::Token::TokenType::Newline;
	t.sourceIndex = currentSourceIndex;
	t.charIndex = charCount;
	t.line = lineCount;
	return t;
}

//generates a identifier token
static inline Cubasic::Token::Token GenerateToken_Identifier(const std::string& word)
{
	Cubasic::Token::Token t;
	t.type = Cubasic::Token::TokenType::Identifier;
	t.sourceIndex = currentSourceIndex;
	t.charIndex = charCount;
	t.line = lineCount;
	t.data = word;
	return t;
}

//lexes code into tokens
std::vector<Cubasic::Token::Token> Cubasic::Token::LexCodeIntoTokens(const std::string& rawCode)
{
	SetCodeToLex(rawCode);
	std::vector<Token> tokens; tokens.reserve(codeLength);

	//while there's still code to parse
	std::string wordData = "";
	while (currentSourceIndex < codeLength)
	{
		//skip white space or mark new line
		if (GetCurrentChar() == ' ' || GetCurrentChar() == '\n')
		{
			//takes whatever word data exists and parse it
			if (wordData != "")
			{
				tokens.emplace_back(GenerateToken_Identifier(wordData));
				wordData = "";
			}

			//if new line, generate a new line tokne
			if (GetCurrentChar() == '\n')
				tokens.emplace_back(GenerateToken_NewLine());

			//fmt::print(" ");
			//GetNextChar();
			//continue;
		}

		//stores the word data
		else
			wordData += GetCurrentChar();

		//gets the next char
		fmt::print("{}", GetCurrentChar());
		GetNextChar();
	}

	return tokens;
}