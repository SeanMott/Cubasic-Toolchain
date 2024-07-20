#pragma once

//defines PASM instructions

namespace Cube::Backend::Instructions
{
	//defines a enum
	enum class Instruction
	{
		NOP = 0, // Do nothing.
		LOAD, //Load a value from memory into a register.
		STORE, // Store a value in a register to memory.
		LOADIMM, // Load an immediate value into a register.
		LOADPTRIMM, // Load pointer register with an immediate value.
		LOADPTR, // Load a value from memory using a pointer register into a register.
		STOREPTR, // Store a value in a register to memory using a pointer register.
		MOV, // Copy a value from a register to another register.
		MOVPTR, // Copy a value from a pointer register to another pointer register.
		ADD, // Add a value from a source register to a destination register. Set zero if result is zero. Set carry if result overflows.
		ADDIMM, // Add an immediate value to a destination register. Set zero if result is zero. Set carry if result overflows.
		ADDPTR, // Add a value from a source register to a destination pointer register.
		ADDPTRIMM, // Add an immediate value to a destination pointer register.
		SUB, // Subtract a value in a source register from a destination register. Set zero if result is zero. Set carry if result underflows.
		SUBIMM, // Subtract an immediate value from a destination register. Set zero if result is zero. Set carry if result underflows.
		SUBPTR, // Subtract a value from a source register from a destination pointer register.
		SUBPTRIMM, // Subtract an immediate value from a destination pointer register.
		JMP, // Set the program counter to an immediate address value.
		JE, // Set the program counter to an immediate address value if zero flag is set; otherwise do nothing.
		JNE, // Set the program counter to an immediate address value if zero flag is not set; otherwise do nothing.
		JLT, // Set the program counter to an immediate address value if carry flag is set; otherwise do nothing.
		JGE, // Set the program counter to an immediate address value if carry flag is not set; otherwise do nothing.
		JMPPTR, // Set the program counter to a pointer register.
		CALL, // Push the current program counter to the stack and set the program counter to an immediate address value.
		RET, // Pop a 16-bit value from the stack and store it in the program counter.
		PUSH, // Push a value in a register to the stack.
		PUSHPTR, // Push a value in a pointer register to the stack.
		POP, // Pop a value from the stack and store it into a register.
		POPPTR,  // Pop a value from the stack and store it into a pointer register.
		CMP, // Subtract a value in a source register from a destination register; but don't store the result. Set zero if result is zero. Set carry if result underflows.
		CMPIMM, // Subtract an immediate value from a destination register; but don't store the result. Set zero if result is zero. Set carry if result underflows.
		AND, // Perform a bitwise and of a source and destination register. Set zero if result is zero. Clear carry.
		ANDIMM, // Perform a bitwise and of an immediate value and a destination register. Set zero if result is zero. Clear carry.
		OR, // Perform a bitwise or of a source and destination register. Set zero if result is zero. Clear carry.
		ORIMM, // Perform a bitwise or of an immediate value and a destination register. Set zero if result is zero. Clear carry.
		XOR, // Perform a bitwise xor of a source and destination register. Set zero if result is zero. Clear carry.
		XORIMM, // Perform a bitwise or of an immediate value and a destination register. Set zero if result is zero. Clear carry.
		NOT, // Calculate the two's compliment of a destination register. Set zero if result is zero. Clear carry.
		HALT, // Stops program execution.
		SYSCALL, // Calls a predefined system call; using r7 as the syscall number.

		Count
	};

	const char PASM_INSTRUCTION_KEYWORD_STRS[PASM_INSTRUCTION_KEYWORD_STR_COUNT] = {
		"NOP",
		"LOAD",
		"STORE",
		"LOADIMM",
		"LOADPTRIMM",
		"LOADPTR",
		"STOREPTR",
		"MOV",
		"MOVPTR",
		"ADD",
		"ADDIMM",
		"ADDPTR",
		"ADDPTRIMM",
		"SUB",
		"SUBIMM",
		"SUBPTR",
		"SUBPTRIMM",
		"JMP",
		"JE",
		"JNE",
		"JLT",
		"JGE",
		"JMPPTR",
		"CALL",
		"RET",
		"PUSH",
		"PUSHPTR",
		"POP",
		"POPPTR",
		"CMP",
		"CMPIMM",
		"AND",
		"ANDIMM",
		"OR",
		"ORIMM",
		"XOR",
		"XORIMM",
		"NOT",
		"HALT",
		"SYSCALL"
	}
}