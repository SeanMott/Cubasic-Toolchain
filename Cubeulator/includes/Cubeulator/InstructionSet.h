#pragma once
#include <iostream>
#include <stdexcept>
#include <map>
#include <string>

typedef void (*OpCodeFunction)();

std::map<std::string, OpCodeFunction> OpCodes;

void ExecuteOpcode(const std::string& hexString);

void NOP();
void LOAD();
void STORE();
void LOADIMM();
void LOADPTRIMM();
void LOADPTR();
void STOREPTR();
void MOV();
void MOVPTR();
void ADD();
void ADDIMM();
void ADDPTR();
void ADDPTRIMM();
void SUB();
void SUBIMM();
void SUBPTR();
void SUBPTRIMM();
void JMP();
void JE();
void JNE();
void JLT();
void JGE();
void JMPPTR();
void CALL();
void RET();
void PUSH();
void PUSHPTR();
void POP();
void POPPTR();
void CMP();
void CMPIMM();
void AND();
void ANDIMM();
void OR();
void ORIMM();
void XOR();
void XORIMM();
void NOT();
void HALT();
void SYSCALL();
