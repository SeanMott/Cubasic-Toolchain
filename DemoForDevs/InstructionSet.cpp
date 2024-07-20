#include "InstructionSet.h"

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