#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <Cubasic/Parser.h>
#include <Cubasic/SemanticAnalysis.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations for code generation
void generate_code(ASTNode* root);
void write_prg_section(const char* prg_file);
void free_rom_sections();

#endif // CODEGENERATOR_H
