#pragma once
#include <iostream>
#include <stdexcept>
#include <map>
#include <string>

typedef void (*OpCodeFunction)();

std::map<std::string, OpCodeFunction> OpCodes;

void NOP() { std::cout << "NOP executed\n"; }
void LOAD() { std::cout << "LOAD executed\n"; }
void STORE() { std::cout << "STORE executed\n"; }
void LOADIMM() { std::cout << "LOADIMM executed\n"; }
void LOADPTRIMM() { std::cout << "LOADPTRIMM executed\n"; }
void LOADPTR() { std::cout << "LOADPTR executed\n"; }
void STOREPTR() { std::cout << "STOREPTR executed\n"; }
void MOV() { std::cout << "MOV executed\n"; }
void MOVPTR() { std::cout << "MOVPTR executed\n"; }
void ADD() { std::cout << "ADD executed\n"; }
void ADDIMM() { std::cout << "ADDIMM executed\n"; }
void ADDPTR() { std::cout << "ADDPTR executed\n"; }
void ADDPTRIMM() { std::cout << "ADDPTRIMM executed\n"; }
void SUB() { std::cout << "SUB executed\n"; }
void SUBIMM() { std::cout << "SUBIMM executed\n"; }
void SUBPTR() { std::cout << "SUBPTR executed\n"; }
void SUBPTRIMM() { std::cout << "SUBPTRIMM executed\n"; }
void JMP() { std::cout << "JMP executed\n"; }
void JE() { std::cout << "JE executed\n"; }
void JNE() { std::cout << "JNE executed\n"; }
void JLT() { std::cout << "JLT executed\n"; }
void JGE() { std::cout << "JGE executed\n"; }
void JMPPTR() { std::cout << "JMPPTR executed\n"; }
void CALL() { std::cout << "CALL executed\n"; }
void RET() { std::cout << "RET executed\n"; }
void PUSH() { std::cout << "PUSH executed\n"; }
void PUSHPTR() { std::cout << "PUSHPTR executed\n"; }
void POP() { std::cout << "POP executed\n"; }
void POPPTR() { std::cout << "POPPTR executed\n"; }
void CMP() { std::cout << "CMP executed\n"; }
void CMPIMM() { std::cout << "CMPIMM executed\n"; }
void AND() { std::cout << "AND executed\n"; }
void ANDIMM() { std::cout << "ANDIMM executed\n"; }
void OR() { std::cout << "OR executed\n"; }
void ORIMM() { std::cout << "ORIMM executed\n"; }
void XOR() { std::cout << "XOR executed\n"; }
void XORIMM() { std::cout << "XORIMM executed\n"; }
void NOT() { std::cout << "NOT executed\n"; }
void HALT() { std::cout << "HALT executed\n"; }
void SYSCALL() { std::cout << "SYSCALL executed\n"; }