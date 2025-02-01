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

//generates a EOF token
static inline Cubasic::Token::Token GenerateToken_EOF()
{
	Cubasic::Token::Token t;
	t.type = Cubasic::Token::TokenType::EndOfFile;
	t.sourceIndex = currentSourceIndex;
	t.charIndex = charCount;
	t.line = lineCount;
	return t;
}

//generates a new line token
static inline Cubasic::Token::Token GenerateToken_NewLine()
{
	Cubasic::Token::Token t;
	t.type = Cubasic::Token::TokenType::Newline;
	t.sourceIndex = currentSourceIndex;
	t.charIndex = charCount;
	t.line = lineCount;
	t.data = "";
	return t;
}

//generates a string literal token
static inline Cubasic::Token::Token GenerateToken_StringLiteral(const std::string& str)
{
	Cubasic::Token::Token t;
	t.type = Cubasic::Token::TokenType::StringLiteral;
	t.sourceIndex = currentSourceIndex;
	t.charIndex = charCount;
	t.line = lineCount;
	t.data = str;
	return t;
}

//generates a digit literal token
static inline Cubasic::Token::Token GenerateToken_DigitLiteral(const std::string& num)
{
	Cubasic::Token::Token t;
	t.type = Cubasic::Token::TokenType::DigitLiteral;
	t.sourceIndex = currentSourceIndex;
	t.charIndex = charCount;
	t.line = lineCount;
	t.data = num;
	return t;
}

//generates a identifier token
static inline Cubasic::Token::Token GenerateToken_Identifier(const uint64_t& symbolID)
{
	Cubasic::Token::Token t;
	t.type = Cubasic::Token::TokenType::Identifier;
	t.sourceIndex = currentSourceIndex;
	t.charIndex = charCount;
	t.line = lineCount;
	t.data = "";
	t.symbolID = symbolID;
	return t;
}

//generates a keyword token
static inline Cubasic::Token::Token GenerateToken_Keyword(const Cubasic::Data::KeywordTypes& type)
{
	Cubasic::Token::Token t;
	t.type = Cubasic::Token::TokenType::Keyword;
	t.keywordType = type;
	t.sourceIndex = currentSourceIndex;
	t.charIndex = charCount;
	t.line = lineCount;
	t.data = "";
	return t;
}

//generates a operator token
static inline Cubasic::Token::Token GenerateToken_Operator(const Cubasic::Data::OperatorTypes& type)
{
	Cubasic::Token::Token t;
	t.type = Cubasic::Token::TokenType::Operator;
	t.sourceIndex = currentSourceIndex;
	t.charIndex = charCount;
	t.line = lineCount;
	t.data = "";
	t.operatorType = type;
	return t;
}

//parses the word data
static inline void ParseWordData(std::string& wordData, std::vector<Cubasic::Token::Token>* tokens, Cubasic::Symbol::SymbolMap* map)
{
	//takes whatever word data exists and parse it
	Cubasic::Data::KeywordTypes keywordType;
	if (wordData != "")
	{
		//if the word is a keyword
		keywordType = Cubasic::Data::IsCubasicKeyword(wordData.c_str());
		if (keywordType != Cubasic::Data::KeywordTypes::Count)
			tokens->emplace_back(GenerateToken_Keyword(keywordType));

		//otherwise make a identifier
		else
		{
			Cubasic::Symbol::Symbol* sym = map->GetSymbol(wordData);
			if(!sym)
				sym = sym = &map->CreateNewSymbol(wordData);
			tokens->emplace_back(GenerateToken_Identifier(sym->ID));
		}
		
		
		wordData = "";
	}
}

//lexes code into tokens
std::vector<Cubasic::Token::Token> Cubasic::Token::LexCodeIntoTokens(const std::string& rawCode, Symbol::SymbolMap& symbolMap)
{
	SetCodeToLex(rawCode);
	std::vector<Token> tokens; tokens.reserve(codeLength);
	symbolMap.symbols.reserve(20);
	Symbol::SymbolMap* map = &symbolMap;

	//while there's still code to parse
	std::string wordData = ""; Data::OperatorTypes op = Data::OperatorTypes::Count;
	while (currentSourceIndex < codeLength)
	{
		//if it's a string literal
		if (GetCurrentChar() == '"')
		{
			//takes whatever word data exists and parse it
			ParseWordData(wordData, &tokens, map);

			//goes till the end of the string
			char lastChar = '"',
			currentChar = GetNextChar();
			while (currentChar != '"')
			{
				//if the current char is a " and last is not a backslash, we end the string
				if (lastChar != '\\' && currentChar == '"')
					break;

				//adds word data
				wordData += currentChar;

				//gets the next char
				lastChar = currentChar;
				currentChar = GetNextChar();
			}

			GetNextChar(); //skips the new char
			tokens.emplace_back(GenerateToken_StringLiteral(wordData));
			fmt::print("\"{}\"", wordData);
			wordData = "";
		}

		//if it's a digit literal
		else if (isdigit(GetCurrentChar()))
		{
			//takes whatever word data exists and parse it
			ParseWordData(wordData, &tokens, map);

			//generates a digit token
			tokens.emplace_back(GenerateToken_DigitLiteral(std::to_string(GetCurrentChar())));
		}

		//if it's a operator
		op = Data::IsCubasicOperator(GetCurrentChar());
		if (op != Data::OperatorTypes::Count)
		{
			//takes whatever word data exists and parse it
			ParseWordData(wordData, &tokens, map);

			//generates a operator token
			tokens.emplace_back(GenerateToken_Operator(op));
		}

		//skip white space or mark new line
		else if (GetCurrentChar() == ' ' || GetCurrentChar() == '\n')
		{
			//takes whatever word data exists and parse it
			ParseWordData(wordData, &tokens, map);

			//if new line, generate a new line tokne
			if (GetCurrentChar() == '\n')
				tokens.emplace_back(GenerateToken_NewLine());
		}

		//stores the word data
		else
			wordData += GetCurrentChar();

		//gets the next char
		fmt::print("{}", GetCurrentChar());
		GetNextChar();
	}

	//adds the last of the word data
	ParseWordData(wordData, &tokens, map);

	//adds end of file token
	tokens.emplace_back(GenerateToken_EOF());

	return tokens;
}