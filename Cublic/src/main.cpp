//the compiler for making a "ROM" for the Cubeculator

#include <Cublic/CompilerSettings.hpp>
#include <Cublic/TranslationUnit.hpp>

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

// Token types
enum class TokenType
{
    INCLUDE = 0,
    
    PRINT,
    
    CALL,
    INPUT,

    IF,
    ELSE,

    GOTO,
    GOSUB,

    THEN,
    NEXT,
    FOR,
    IN,

    SET,

    FUNCTION,

    END,
    RETURN,

    STOP,

    STRING_LITERAL,
    DIGIT_LITERAL,
    //HEX_LITERAL,

    IDENTIFIER,
    
    OPERATOR,

    END_OF_FILE, INVALID
};

static TokenType keywordToTokenType(const char* value) {
    static const struct {
        const char* keyword;
        TokenType type;
    } keywords[] = {
        {"STOP", TokenType::STOP}, {"INCLUDE", TokenType::INCLUDE}, {"FUNCTION", TokenType::FUNCTION},
        {"END", TokenType::END}, {"PRINT", TokenType::PRINT}, {"CALL", TokenType::CALL}, {"RETURN", TokenType::RETURN},
        {"INPUT", TokenType::INPUT}, {"IF", TokenType::IF}, {"ELSE", TokenType::ELSE}, {"THEN", TokenType::THEN},
        {"NEXT", TokenType::NEXT}, {"FOR", TokenType::FOR}, {"IN", TokenType::IN}, {"SET", TokenType::SET},
        {"GOTO", TokenType::GOTO}, {"GOSUB", TokenType::GOSUB}
    };

    for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
        if (strcmp(value, keywords[i].keyword) == 0) {
            return keywords[i].type;
        }
    }
    return TokenType::IDENTIFIER;
}

// Token structure
struct Token
{
    TokenType type;
    std::string value = "";
};

//skips a comment
static void skipComment(const char* source, const size_t& sourceLength, size_t& charIndex) {
    while (charIndex < sourceLength && source[charIndex] != '\n')
    {
        charIndex++;

        // Skip the newline character if it exists
        if (source[charIndex] == '\n')
            break;
    }
}

//process a identifier
static char* readIdentifier(const char* source, const size_t& sourceLength, size_t& charIndex)
{
    size_t len = 0;
    char buffer[256];

    while (charIndex < sourceLength && source[charIndex] && (isalnum(source[charIndex]) || source[charIndex] == '_')) {
        buffer[len++] = source[charIndex];
        charIndex++;
    }

    buffer[len] = '\0'; //sets the end to zero
    charIndex--; //back a index
   
    char* result = (char*)malloc(len + 1);
    strncpy(result, buffer, len + 1);
    return result;
}

//reads a string literal
static char* readStringLiteral(const char* source, const size_t& sourceLength, size_t& charIndex) {
    size_t len = 0;
    char buffer[1024];


    while (charIndex < sourceLength && source[charIndex] && source[charIndex] != '"') {
        if (source[charIndex] == '\\') { // Handle escape sequences
            charIndex++; // Skip the backslash
            if (charIndex < sourceLength && source[charIndex] == '"' || source[charIndex] == '\\') {
                buffer[len++] = source[charIndex];
                charIndex++;
            }
            else {
                buffer[len++] = '\\'; // Just add backslash if escape is unknown
            }
        }
        else {
            buffer[len++] = source[charIndex];
            charIndex++;
        }
    }

    buffer[len] = '\0';

    if (source[charIndex] == '"') {
        charIndex++; // Skip the closing quote
    }

    char* result = (char*)malloc(len + 1);
    strncpy(result, buffer, len + 1);
    return result;
}

std::vector<Token> tokenize(const char* input)
{
    const size_t sourceLength = strlen(input);

    std::vector<Token> tokens; tokens.reserve(10);

    for(size_t c = 0; c < sourceLength; ++c)
    {
        //if white space or tab
        if (isspace(input[c]) || input[c] == '\t')
            continue;

        //leave if 0
        if (input[c] == '\0') break;

        // Handle comments
        if (c + 1 < sourceLength && input[c] == '/' && input[c + 1] == '/')
        {
            c += 1; // skip '/' and '/'
            skipComment(input, sourceLength, c);
            continue; // skip to the next iteration
        }

        // Handle string literals
         if (input[c] == '"') 
         {
            c++;
            char* token_value = readStringLiteral(input, sourceLength, c);

            Token* token = &tokens.emplace_back(Token());
            token->type = TokenType::STRING_LITERAL;
            token->value = token_value;
            free(token_value);
            continue;
        }

        //handles operators
         if (input[c] == '(' || input[c] == ')' || input[c] == '[' || input[c] == ']' || input[c] == '<' || input[c] == '>' ||
            input[c] == ',' || input[c] == ':' || input[c] == '.' || input[c] == '=')
        {
            Token* token = &tokens.emplace_back(Token());
            token->type = TokenType::OPERATOR;
            token->value = input[c];
            continue;
        }

        //process a digit
        if (isdigit(input[c]))
        {
            Token* token = &tokens.emplace_back(Token());
            token->type = TokenType::DIGIT_LITERAL;
            token->value = input[c];
            continue;
        }

        //process a identifier or keyword
        if (isalpha(input[c])) {
            
            char* token_value = readIdentifier(input, sourceLength, c);
            TokenType type = keywordToTokenType(token_value);

            Token* token = &tokens.emplace_back(Token());
            token->type = type;
            token->value = token_value;
            free(token_value);
            continue;
        }

        //sets a invalid index
        Token invalid_token = { TokenType::INVALID, ""};
        tokens.emplace_back(invalid_token);
    }

    //sets a end of file token
    Token eof_token = { TokenType::END_OF_FILE, ""};
    tokens.emplace_back(eof_token);

    return tokens;
}

//prints a list of tokens
void PrintStatements(const std::vector<Token>& tokens)
{
    for (size_t i = 0; i < tokens.size(); ++i) 
    {
        switch (tokens[i].type) 
        {
            case TokenType::STOP: printf("Parsing STOP statement\n"); break;
            case TokenType::INCLUDE: printf("Parsing INCLUDE statement\n"); break;
            case TokenType::FUNCTION: printf("Parsing FUNCTION statement\n"); break;
            case TokenType::END: printf("Parsing END statement\n"); break;
            case TokenType::PRINT: printf("Parsing PRINT statement\n"); break;
            case TokenType::CALL: printf("Parsing CALL statement\n"); break;
            case TokenType::RETURN: printf("Parsing RETURN statement\n"); break;
            case TokenType::INPUT: printf("Parsing INPUT statement\n"); break;
            case TokenType::IF: printf("Parsing IF statement\n"); break;
            case TokenType::ELSE: printf("Parsing ELSE statement\n"); break;
            case TokenType::THEN: printf("Parsing THEN statement\n"); break;
            case TokenType::NEXT: printf("Parsing NEXT statement\n"); break;
            case TokenType::FOR: printf("Parsing FOR statement\n"); break;
            case TokenType::IN: printf("Parsing IN statement\n"); break;
            case TokenType::SET: printf("Parsing SET statement\n"); break;
            case TokenType::GOTO: printf("Parsing GOTO statement\n"); break;
            case TokenType::GOSUB: printf("Parsing GOSUB statement\n"); break;
            
            case TokenType::STRING_LITERAL: printf("Parsing STRING LITERAL: %s\n", tokens[i].value.c_str()); break;
            case TokenType::DIGIT_LITERAL: printf("Parsing DIGIT LITERAL: %s\n", tokens[i].value.c_str()); break;
            
            case TokenType::IDENTIFIER: printf("Parsing IDENTIFIER: %s\n", tokens[i].value.c_str()); break;
            
            case TokenType::OPERATOR: printf("Parsing OPERATOR: %s\n", tokens[i].value.c_str()); break;

            case TokenType::END_OF_FILE: printf("----END OF FILE----\n"); break;
            case TokenType::INVALID: printf("Error: Invalid statement\n"); break;
            
            default: printf("Error: Unknown token type\n"); break;
        }
    }
}

int main() 
{
    //loads code
    std::ifstream t("C:/Compilers/Cubasic-Toolchain/DemoForDevs/TestProject/Main.cubasic");
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    std::string source(size, '\0');
    t.seekg(0);
    t.read(&source[0], size);
    t.close();

    //lex tokens
    std::vector<Token> tokens = tokenize(source.c_str());
    PrintStatements(tokens);
    tokens.clear();

    getchar();
    return 0;
}