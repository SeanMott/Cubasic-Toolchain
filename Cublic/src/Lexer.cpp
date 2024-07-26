#include <Cublic/Lexer.hpp>

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

std::vector<Cube::Token> Cube::Lex(const char* source)
{
    const size_t sourceLength = strlen(source);

    std::vector<Token> tokens; tokens.reserve(10);

    for (size_t c = 0; c < sourceLength; ++c)
    {
        //if white space or tab
        if (isspace(source[c]) || source[c] == '\t')
            continue;

        //leave if 0
        if (source[c] == '\0') break;

        // Handle comments
        if (c + 1 < sourceLength && source[c] == '/' && source[c + 1] == '/')
        {
            c += 1; // skip '/' and '/'
            skipComment(source, sourceLength, c);
            continue; // skip to the next iteration
        }

        // Handle string literals
        if (source[c] == '"')
        {
            c++;
            char* token_value = readStringLiteral(source, sourceLength, c);

            Token* token = &tokens.emplace_back(Token());
            token->type = Keywords::TokenType::STRING_LITERAL;
            token->value = token_value;
            free(token_value);
            continue;
        }

        //handles operators
        if (source[c] == '(' || source[c] == ')' || source[c] == '[' || source[c] == ']' || source[c] == '<' || source[c] == '>' ||
            source[c] == ',' || source[c] == ':' || source[c] == '.' || source[c] == '=')
        {
            Token* token = &tokens.emplace_back(Token());
            token->type = Keywords::TokenType::OPERATOR;
            token->value = source[c];
            continue;
        }

        //process a digit
        if (isdigit(source[c]))
        {
            Token* token = &tokens.emplace_back(Token());
            token->type = Keywords::TokenType::DIGIT_LITERAL;
            token->value = source[c];
            continue;
        }

        //process a identifier or keyword
        if (isalpha(source[c])) {

            char* token_value = readIdentifier(source, sourceLength, c);
            Keywords::TokenType type = Keywords::keywordToTokenType(token_value);

            Token* token = &tokens.emplace_back(Token());
            token->type = type;
            token->value = token_value;
            free(token_value);
            continue;
        }

        //sets a invalid index
        Token invalid_token = { Keywords::TokenType::INVALID, "" };
        tokens.emplace_back(invalid_token);
    }

    //sets a end of file token
    Token eof_token = { Keywords::TokenType::END_OF_FILE, "" };
    tokens.emplace_back(eof_token);

    return tokens;
}

//prints a list of tokens
void Cube::Print(const std::vector<Cube::Token>& tokens)
{
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        switch (tokens[i].type)
        {
        case Keywords::TokenType::STOP: printf("Parsing STOP statement\n"); break;
        case Keywords::TokenType::INCLUDE: printf("Parsing INCLUDE statement\n"); break;
        case Keywords::TokenType::FUNCTION: printf("Parsing FUNCTION statement\n"); break;
        case Keywords::TokenType::END: printf("Parsing END statement\n"); break;
        case Keywords::TokenType::PRINT: printf("Parsing PRINT statement\n"); break;
        case Keywords::TokenType::CALL: printf("Parsing CALL statement\n"); break;
        case Keywords::TokenType::RETURN: printf("Parsing RETURN statement\n"); break;
        case Keywords::TokenType::INPUT: printf("Parsing INPUT statement\n"); break;
        case Keywords::TokenType::IF: printf("Parsing IF statement\n"); break;
        case Keywords::TokenType::ELSE: printf("Parsing ELSE statement\n"); break;
        case Keywords::TokenType::THEN: printf("Parsing THEN statement\n"); break;
        case Keywords::TokenType::NEXT: printf("Parsing NEXT statement\n"); break;
        case Keywords::TokenType::FOR: printf("Parsing FOR statement\n"); break;
        case Keywords::TokenType::IN: printf("Parsing IN statement\n"); break;
        case Keywords::TokenType::SET: printf("Parsing SET statement\n"); break;
        case Keywords::TokenType::GOTO: printf("Parsing GOTO statement\n"); break;
        case Keywords::TokenType::GOSUB: printf("Parsing GOSUB statement\n"); break;

        case Keywords::TokenType::STRING_LITERAL: printf("Parsing STRING LITERAL: %s\n", tokens[i].value.c_str()); break;
        case Keywords::TokenType::DIGIT_LITERAL: printf("Parsing DIGIT LITERAL: %s\n", tokens[i].value.c_str()); break;

        case Keywords::TokenType::IDENTIFIER: printf("Parsing IDENTIFIER: %s\n", tokens[i].value.c_str()); break;

        case Keywords::TokenType::OPERATOR: printf("Parsing OPERATOR: %s\n", tokens[i].value.c_str()); break;

        case Keywords::TokenType::END_OF_FILE: printf("----END OF FILE----\n"); break;
        case Keywords::TokenType::INVALID: printf("Error: Invalid statement\n"); break;

        default: printf("Error: Unknown token type\n"); break;
        }
    }
}