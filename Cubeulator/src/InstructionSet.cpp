#include "Cubeulator/InstructionSet.h"

void InitOpcodeTable()
{
	OpCodes["NOP"] = NOP; // Do nothing.
	OpCodes["LOAD"] = LOAD; // Load a value from memory into a register.
	OpCodes["STORE"] = STORE; // Store a value in a register to memory.
	OpCodes["LOADIMM"] = LOADIMM; // Load an immediate value into a register.
	OpCodes["LOADPTRIMM"] = LOADPTRIMM; // Load pointer register with an immediate value.
	OpCodes["LOADPTR"] = LOADPTR; // Load a value from memory using a pointer register into a register.
	OpCodes["STOREPTR"] = STOREPTR; // Store a value in a register to memory using a pointer register.
	OpCodes["MOV"] = MOV; // Copy a value from a register to another register.
	OpCodes["MOVPTR"] = MOVPTR; // Copy a value from a pointer register to another pointer register.
	OpCodes["ADD"] = ADD; // Add a value from a source register to a destination register. Set zero if result is zero. Set carry if result overflows.
	OpCodes["ADDIMM"] = ADDIMM; // Add an immediate value to a destination register. Set zero if result is zero. Set carry if result overflows.
	OpCodes["ADDPTR"] = ADDPTR; // Add a value from a source register to a destination pointer register.
	OpCodes["ADDPTRIMM"] = ADDPTRIMM; // Add an immediate value to a destination pointer register.
	OpCodes["SUB"] = SUB; // Subtract a value in a source register from a destination register. Set zero if result is zero. Set carry if result underflows.
	OpCodes["SUBIMM"] = SUBIMM; // Subtract an immediate value from a destination register. Set zero if result is zero. Set carry if result underflows.
	OpCodes["SUBPTR"] = SUBPTR; // Subtract a value from a source register from a destination pointer register.
	OpCodes["SUBPTRIMM"] = SUBPTRIMM; // Subtract an immediate value from a destination pointer register.
	OpCodes["JMP"] = JMP; // Set the program counter to an immediate address value.
	OpCodes["JE"] = JE; // Set the program counter to an immediate address value if zero flag is set; otherwise do nothing.
	OpCodes["JNE"] = JNE; // Set the program counter to an immediate address value if zero flag is not set; otherwise do nothing.
	OpCodes["JLT"] = JLT; // Set the program counter to an immediate address value if carry flag is set; otherwise do nothing.
	OpCodes["JGE"] = JGE; // Set the program counter to an immediate address value if carry flag is not set; otherwise do nothing.
	OpCodes["JMPPTR"] = JMPPTR; // Set the program counter to a pointer register.
	OpCodes["CALL"] = CALL; // Push the current program counter to the stack and set the program counter to an immediate address value.
	OpCodes["RET"] = RET; // Pop a 16-bit value from the stack and store it in the program counter.
	OpCodes["PUSH"] = PUSH; // Push a value in a register to the stack.
	OpCodes["PUSHPTR"] = PUSHPTR; // Push a value in a pointer register to the stack.
	OpCodes["POP"] = POP; // Pop a value from the stack and store it into a register.
	OpCodes["POPPTR"] = POPPTR;  // Pop a value from the stack and store it into a pointer register.
	OpCodes["CMP"] = CMP; // Subtract a value in a source register from a destination register; but don't store the result. Set zero if result is zero. Set carry if result underflows.
	OpCodes["CMPIMM"] = CMPIMM; // Subtract an immediate value from a destination register; but don't store the result. Set zero if result is zero. Set carry if result underflows.
	OpCodes["AND"] = AND; // Perform a bitwise and of a source and destination register. Set zero if result is zero. Clear carry.
	OpCodes["ANDIMM"] = ANDIMM; // Perform a bitwise and of an immediate value and a destination register. Set zero if result is zero. Clear carry.
	OpCodes["OR"] = OR; // Perform a bitwise or of a source and destination register. Set zero if result is zero. Clear carry.
	OpCodes["ORIMM"] = ORIMM; // Perform a bitwise or of an immediate value and a destination register. Set zero if result is zero. Clear carry.
	OpCodes["XOR"] = XOR; // Perform a bitwise xor of a source and destination register. Set zero if result is zero. Clear carry.
	OpCodes["XORIMM"] = XORIMM; // Perform a bitwise or of an immediate value and a destination register. Set zero if result is zero. Clear carry.
	OpCodes["NOT"] = NOT; // Calculate the two's compliment of a destination register. Set zero if result is zero. Clear carry.
	OpCodes["HALT"] = HALT; // Stops program execution.
	OpCodes["SYSCALL"] = SYSCALL; // Calls a predefined system call; using r7 as the syscall number.
};

void ExecuteOpcode(const std::string& hexString)
{
	if (OpCodes.find(hexString) != OpCodes.end())
	{
		OpCodes[hexString]();
	}
	else
	{
		OpCodes["default"]();
	}
}

void NOP() 
{ 
	//Nothing happens
}

void LOAD() 
{ 
	std::cout << "LOAD executed\n"; 
}

void STORE() 
{ 
	std::cout << "STORE executed\n"; 
}

void LOADIMM() 
{ 
	std::cout << "LOADIMM executed\n"; 
}

void LOADPTRIMM() 
{ 
	std::cout << "LOADPTRIMM executed\n"; 
}

void LOADPTR() 
{ 
	std::cout << "LOADPTR executed\n"; 
}

void STOREPTR() 
{ 
	std::cout << "STOREPTR executed\n"; 
}

void MOV() 
{ 
	std::cout << "MOV executed\n"; 
}

void MOVPTR() 
{ 
	std::cout << "MOVPTR executed\n"; 
}

void ADD() 
{ 
	std::cout << "ADD executed\n"; 
}

void ADDIMM() 
{ 
	std::cout << "ADDIMM executed\n"; 
}

void ADDPTR() 
{ 
	std::cout << "ADDPTR executed\n"; 
}

void ADDPTRIMM() 
{ 
	std::cout << "ADDPTRIMM executed\n"; 
}

void SUB() 
{ 
	std::cout << "SUB executed\n"; 
}

void SUBIMM() 
{ 
	std::cout << "SUBIMM executed\n"; 
}

void SUBPTR() 
{ 
	std::cout << "SUBPTR executed\n"; 
}

void SUBPTRIMM() 
{ 
	std::cout << "SUBPTRIMM executed\n"; 
}

void JMP() 
{ 
	std::cout << "JMP executed\n"; 
}

void JE() 
{ 
	std::cout << "JE executed\n"; 
}

void JNE() 
{ 
	std::cout << "JNE executed\n"; 
}

void JLT() 
{ 
	std::cout << "JLT executed\n"; 
}

void JGE() 
{ 
	std::cout << "JGE executed\n"; 
}

void JMPPTR() 
{ 
	std::cout << "JMPPTR executed\n"; 
}

void CALL() 
{ 
	std::cout << "CALL executed\n"; 
}

void RET() 
{ 
	std::cout << "RET executed\n"; 
}

void PUSH() 
{ 
	std::cout << "PUSH executed\n"; 
}

void PUSHPTR() 
{ 
	std::cout << "PUSHPTR executed\n"; 
}

void POP() 
{ 
	std::cout << "POP executed\n"; 
}

void POPPTR() 
{ 
	std::cout << "POPPTR executed\n"; 
}

void CMP() 
{ 
	std::cout << "CMP executed\n"; 
}

void CMPIMM() 
{ 
	std::cout << "CMPIMM executed\n"; 
}

void AND() 
{ 
	std::cout << "AND executed\n"; 
}

void ANDIMM() 
{ 
	std::cout << "ANDIMM executed\n"; 
}

void OR() 
{ 
	std::cout << "OR executed\n"; 
}

void ORIMM() 
{ 
	std::cout << "ORIMM executed\n"; 
}

void XOR() 
{ 
	std::cout << "XOR executed\n"; 
}

void XORIMM() 
{ 
	std::cout << "XORIMM executed\n"; 
}

void NOT() 
{ 
	std::cout << "NOT executed\n"; 
}

void HALT() 
{ 
	std::cout << "HALT executed\n"; 
}

void SYSCALL() 
{ 
	std::cout << "SYSCALL executed\n"; 
}