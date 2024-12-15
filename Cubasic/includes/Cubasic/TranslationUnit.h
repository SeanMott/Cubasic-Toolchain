#pragma once

//defines a translation unit

#include <Cubasic/Frontend/Token.hpp>

//defines the translation unit
//each code file is a translation unit
typedef struct TranslationUnit {

	//counts
	size_t tokenCount; //the amount of tokens
	//the amount of AST Nodes

	//data
	Token** tokens; //the tokens
	//the AST

} TranslationUnit;

//destroys the translation unit
static inline void DestroyTranslationUnit(TranslationUnit* translationUnit)
{
	for (size_t i = 0; i < translationUnit->tokenCount; ++i)
		free_token(translationUnit->tokens[i]);
	free(translationUnit->tokens);
	translationUnit->tokenCount = 0;
}

//adds a token
static inline Token* AddToken(TranslationUnit* translationUnit, const Token* token)
{
	translationUnit->tokenCount++;
	translationUnit->tokens = (Token**)realloc(translationUnit->tokens, sizeof(Token*) * translationUnit->tokenCount);
	translationUnit->tokens[translationUnit->tokenCount - 1] = token;
	return translationUnit->tokens[translationUnit->tokenCount - 1];
}

//gets the latest token
static inline Token* GetLatestToken(TranslationUnit* translationUnit)
{
	return (translationUnit->tokenCount > 0 ? translationUnit->tokens[translationUnit->tokenCount - 1] : NULL);
}