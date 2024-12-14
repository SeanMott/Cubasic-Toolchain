==================
CubixCore Assembly Commands
==================

Arithmetic Operations
----------------------
- **ADD**: Add values.
- **SUB**: Subtract values.
- **ADDIMM**: Add an immediate value to a register.
- **SUBIMM**: Subtract an immediate value from a register.

Memory Operations
------------------
- **LOAD**: Load a value into a register.
- **STORE**: Store a register value into memory.
- **LOADIMM**: Load an immediate value into a register.
- **STOREPTR**: Store a value at a memory pointer.
- **LOADPTR**: Load a value from a memory pointer.
- **FREEPTR**: Free allocated memory at a pointer.

Control Flow
-------------
- **JMP**: Jump to a label.
- **CALL**: Call a function or subroutine.
- **RET**: Return from a function or subroutine.
- **JNE**: Jump if not equal.
- **JE**: Jump if equal.
- **JLT**: Jump if less than.
- **CMP**: Compare two values.
- **TRY**: Start a try block.
- **CATCH**: Start a catch block for exception handling.

System Calls
-------------
- **SYSCALL**: Execute a system-level function (e.g., graphics, memory allocation).
- **ALLOC**: Allocate memory dynamically.

Logical Operations
-------------------
- **AND**: Perform bitwise AND.
- **OR**: Perform bitwise OR.
- **XOR**: Perform bitwise XOR.
- **NOT**: Perform bitwise NOT.

Stack Operations
------------------
- **PUSH**: Push a value onto the stack.
- **POP**: Pop a value from the stack.

Utility
-------
- **HALT**: Stop execution.
- **NOP**: No operation.

Graphics Operations
---------------------
- **DRAWPIXEL**: Draw a pixel at specific coordinates.
- **LINE**: Draw a line between two points.
- **CIRCLE**: Draw a circle.
- **FILL**: Fill an area with color.
- **LOADSPRITE**: Load a sprite into memory.
- **DRAWSprite**: Draw a sprite at specific coordinates.

Input/Output
------------
- **PRINT**: Output text or values.
- **INPUT**: Accept user input.

String Handling
----------------
- **CONCAT**: Concatenate two strings into a register.
- **STRLEN**: Get the length of a string in a register.
- **SUBSTR**: Extract a substring from a string into a register.

Array Operations
-----------------
- **PUSH**: Add an element to an array.
- **POP**: Remove the last element from an array.
- **INSERT**: Insert an element at a specific index in an array.
- **REMOVE**: Remove an element at a specific index in an array.

Looping Constructs
-------------------
- **INIT_LOOP**: Initialize a loop counter with start and end values.
- **CHECK_LOOP**: Check the loop condition and decide whether to continue.

Sound Operations
-----------------
- **BEEP**: Emit a beep sound.
- **PLAY**: Play a note or sound sequence with duration.

Registers
---------
- General-purpose registers (`R0`, `R1`, ...).
- Pointer registers (`PTR1`, `PTR2`).

========================
End of Assembly Commands
========================

