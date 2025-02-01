==================
Cubasic Commands
==================

General Statements
------------------

FUNCTION
<br>
Description: ```Define a function with arguments.```
<br>
Syntax: ``FUNCTION funcName(arg1, arg2, ...)``

; ASM	
; Function definition
FUNCTION funcName:
; Save arguments to the stack or registers
PUSH R1     ; Assuming arg1 is in R1
PUSH R2     ; Assuming arg2 is in R2
; Function body goes here

; Restore arguments or handle return value
POP R2
POP R1
RET

CALL
    Description: Call a defined function with arguments.
    Syntax: CALL funcName(arg1, arg2, ...)

; Push arguments to the stack or set them in registers
LOADIMM R1, arg1    ; Load immediate value of arg1 into register R1
LOADIMM R2, arg2    ; Load immediate value of arg2 into register R2

; Call the function
CALL funcName

; Optionally, handle return value if the function returns one
; Assuming the return value is in R0

CLEAR
    Description: Reset variables or arrays.
    Syntax: CLEAR variable/array

; Resetting a Variable

LOADIMM R0, 0        ; Load immediate value 0 into register R0
STORE R0, variable   ; Store 0 in the variable

; Resetting an Array
; Assuming arrayName is an array of size N starting at memory location arrayBase:

LOADIMM R1, 0        ; Load immediate value 0 into register R1
LOADIMM R2, arrayBase ; Load the base address of the array into R2
LOADIMM R3, N        ; Load the size of the array into R3
clear_loop:
STORE R1, [R2]    ; Store 0 at the current address in R2
ADDIMM R2, 1      ; Move to the next address in the array
SUBIMM R3, 1      ; Decrease the counter
JNE clear_loop    ; If counter is not zero, repeat the loop

DIM
    Description: Declare an array with a specified size.
    Syntax: DIM arrayName(size)

; Let's declare an array arr of size 10 starting at memory location 0x1000.
; Step 1: Allocate Memory
; Load the size of the array into a register
LOADIMM R1, size        ; Load the size into R1

; Call the ALLOC system call to allocate memory
LOADIMM R7, ALLOC_SYSCALL ; Load the syscall number for memory allocation
SYSCALL                  ; Perform the system call

; The allocated address is returned in a pointer register (assuming PTR1)
MOVPTR PTR1, R0          ; Move the allocated address from R0 to PTR1
STORE PTR1, arrayName    ; Store the base address of the array in arrayName

; Step 2: Initialize Memory (Optional)
LOADIMM R2, 0           ; Load 0 into R2 (initial value)
LOADPTR PTR2, arrayName ; Load the base address of the array into PTR2
MOV R3, size            ; Load the size of the array into R3
init_loop:
    STOREPTR R2, PTR2    ; Store 0 at the current address in PTR2
    ADDPTRIMM PTR2, 1    ; Move to the next address
    SUBIMM R3, 1         ; Decrease the counter
    JNE init_loop        ; If counter is not zero, repeat the loop

FREE
    Description: Free memory allocated to variables or arrays.
    Syntax: FREE variable/array

WHILE ... DO
    Description: Execute a block of code as long as a condition is true.
    Syntax: WHILE condition DO ... ENDWHILE

BREAK
    Description: Exit the current loop prematurely.
    Syntax: BREAK

CONTINUE
    Description: Skip the current iteration of a loop and continue to the next.
    Syntax: CONTINUE

STRING HANDLING
----------------

CONCAT
    Description: Concatenate two or more strings.
    Syntax: CONCAT(string1, string2, ...)

LEN
    Description: Get the length of a string or array.
    Syntax: LEN(variable)

SUBSTR
    Description: Extract a substring from a string.
    Syntax: SUBSTR(string, start, length)

MATHEMATICAL FUNCTIONS
-----------------------

POW
    Description: Raise a number to a power.
    Syntax: POW(base, exponent)

SQRT
    Description: Compute the square root of a number.
    Syntax: SQRT(value)

MOD
    Description: Compute the remainder of a division operation.
    Syntax: MOD(a, b)

TIMER
    Description: Measure execution time or create time delays.
    Syntax: TIMER start/end

LOG
    Description: Write debugging information to a log.
    Syntax: LOG "message", variable

ARRAY OPERATIONS
-----------------

PUSH
    Description: Add an element to the end of an array.
    Syntax: PUSH array, value

POP
    Description: Remove and return the last element of an array.
    Syntax: POP array

INSERT
    Description: Insert an element into an array at a specific position.
    Syntax: INSERT array, index, value

REMOVE
    Description: Remove an element from an array at a specific position.
    Syntax: REMOVE array, index

GRAPHICS ENHANCEMENTS
----------------------

LINE
    Description: Draw a line between two points.
    Syntax: LINE x1, y1, x2, y2, color

CIRCLE
    Description: Draw a circle with a given radius.
    Syntax: CIRCLE centerX, centerY, radius, color

FILL
    Description: Fill a shape or area with a color.
    Syntax: FILL x, y, color

FILE HANDLING
-------------

READFILE
    Description: Read data from a file into a variable or array.
    Syntax: READFILE "filename", variable/array

WRITEFILE
    Description: Write data from a variable or array into a file.
    Syntax: WRITEFILE "filename", variable/array

ERROR HANDLING
--------------

TRY ... CATCH
    Description: Handle runtime errors gracefully.
    Syntax: TRY ... CATCH error ... ENDTRY

SYSCALL
    Description: Execute a system call with parameters.
    Syntax: SYSCALL command, parameters

END
    Description: Mark the end of the program.
    Syntax: END
	
HALT
	
GOSUB
    Description: Call a subroutine.
    Syntax: GOSUB lineNumber

Step 1: Call the Subroutine
CALL subroutine_label

Step 2: Define the Subroutine
subroutine_label:
    ; Subroutine body
    RET

GOTO
    Description: Jump to a line of code.
    Syntax: GOTO lineNumber

JMP target_label

FOR ... IN
    Description: Modern loop iterating over a range or collection.
    Syntax: FOR var IN range

; Step 1: Initialize Loop Variables
LOADIMM R1, start     ; Load the start value into register R1
LOADIMM R2, end       ; Load the end value into register R2

; Step 2: Define the Loop
loop_start:
    ; Loop body
    ; Example: increment another register
    ADDIMM R3, 1       ; Increment register R3 (some operation)

    ; Update loop variable
    ADDIMM R1, 1       ; Increment the loop variable

    ; Compare loop variable to end value
    CMP R1, R2
    JLT loop_start     ; If R1 < R2, jump to loop_start

IF ... THEN ... ELSE
    Description: Conditional execution with extended branching.
    Syntax: IF condition THEN action [ELSEIF condition THEN action] [ELSE action]

INPUT
    Description: Read formatted user input.
    Syntax: INPUT "format"; variables

PRINT
    Description: Display formatted output.
    Syntax: PRINT "format", variables

//
    Description: Add a comment.
    Syntax: // comment

RETURN
    Description: Return from a function.
    Syntax: RETURN [value]

SWAP
    Description: Efficiently exchange values of two variables.
    Syntax: SWAP var1, var2

STOP
    Description: Halt program execution.
    Syntax: STOP

Arithmetic Operations
---------------------

SET
    Description: Assign a value to a variable or perform an arithmetic operation.
    Syntax: SET var = expression

Loop Control
------------

NEXT
    Description: Mark the end of a FOR loop.
    Syntax: NEXT var

=========================
Cubasic Screen Control Statements
=========================

CGEN
    Description: Simplified command to specify background character sprites.
    Syntax: CGEN spriteID
    Note: May be simplified or removed based on emulator capabilities.

CGSET
    Description: Set the background for sprites.
    Syntax: CGSET spriteID, backgroundID
    Note: Depends on emulator's graphic handling capacity.

CLS
    Description: Clear the entire screen.
    Syntax: CLS

COLOR
    Description: Set the color at a specific screen location.
    Syntax: COLOR column, row, colorCode

LOCATE
    Description: Move the cursor to specific screen coordinates.
    Syntax: LOCATE column, row

PALET
    Description: Define the color palette to be used.
    Syntax: PALET paletteID, color1, color2, color3, color4
    Note: Adapted for limited color palette of Famicube.

=================
Cubasic Movement Commands
=================

CUT
    Description: Stops the movement of the character sprite.
    Syntax: CUT spriteID

DEF MOVE
    Description: Define the movement parameters for a character sprite.
    Syntax: DEF MOVE spriteID = SPRITE (parameters)

ERA
    Description: Stop and remove the character sprite from the screen.
    Syntax: ERA spriteID

MOVE
    Description: Initiate or control the movement of a defined character sprite.
    Syntax: MOVE spriteID, [parameters]

POSITION
    Description: Set the character sprite's coordinates.
    Syntax: POSITION spriteID, column, row

==================
Cubasic Special Statements
==================

KEY
    Description: Assign a specific function to a function key.
    Syntax: KEY keyNumber, "function"
    Note: keyNumber (1-8) corresponds to F1-F8.

PAUSE
    Description: Delay program execution for a specified duration.
    Syntax: PAUSE duration
    Note: Duration is in milliseconds.

VIEW
    Description: Toggle between different graphics layers.
    Syntax: VIEW
    Note: Simplified to suit the Famicube's graphic capabilities.

========================
Cubasic Sound Control Statements
========================

BEEP
    Description: Emit a simple beep sound.
    Syntax: BEEP

PLAY
    Description: Play a sequence of musical notes.
    Syntax: PLAY "noteSequence"
    Note: "noteSequence" comprises simple note representations (e.g., A, B, C) and durations.

=========================
Cubasic Sprite Control Statements
=========================

DEF SPRITE
    Description: Define sprite graphics.
    Syntax: DEF SPRITE spriteID, (graphicData)
    Note: graphicData represents sprite design parameters.

SPRITE
    Description: Position a defined sprite on the screen.
    Syntax: SPRITE spriteID, xPosition, yPosition

SPRITE OFF
    Description: Disable sprite display.
    Syntax: SPRITE OFF

SPRITE ON
    Description: Enable sprite display.
    Syntax: SPRITE ON

============
Cubasic Value Functions
============

ABS
    Description: Compute the absolute value of a number.
    Syntax: ABS(number)

RND
    Description: Generate a random number.
    Syntax: RND(seed)
    Note: 'seed' is optional; if omitted, uses a default seed.

SGN
    Description: Determine the sign of a number.
    Syntax: SGN(number)

-------------------------
End of Cubasic Documentation
-------------------------

