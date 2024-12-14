# Cubasic Programming Language and CubixCore CPU Design Document

## Project Vision
To create a simple yet modern programming language (Cubasic) for a retro-inspired virtual console (CubixCore). The goal is to blend the simplicity of retro systems like NES and Game Boy with modern programming conveniences such as named functions, function maps, and structured flow control. The system should be approachable for beginners while offering enough power for advanced users.

---

## Core Components

### 1. Cubasic Programming Language
#### Key Principles:
- **Retro Feel**: Minimalist instruction set mimicking the constraints of older hardware.
- **Modern Features**: Enhanced syntax and commands for better readability and ease of use.
- **Beginner Friendly**: Inspired by BASIC, focusing on clarity and simplicity.

#### Example Syntax:
```basic
FUNCTION DrawSquare(x, y, size)
    DIM points(size * 4)
    FOR i IN 0 TO size * 4
        SET points[i] = (x + i, y + i)
    NEXT i
    PRINT "Square drawn at ", x, ", ", y
END
```

#### Core Commands:
| Command    | Description                                                                 |
|------------|-----------------------------------------------------------------------------|
| FUNCTION   | Define reusable named blocks of code.                                       |
| CALL       | Call a function with arguments.                                            |
| PRINT      | Display text or variable values on the screen.                             |
| DIM        | Declare arrays with a fixed or dynamic size.                               |
| FOR/WHILE  | Loop constructs for iterative operations.                                  |
| IF/ELSE    | Conditional branching with nested support.                                 |
| HALT       | End program execution.                                                    |
| SPRITE     | Draw and manage graphical sprites.                                         |
| INPUT      | Accept user input.                                                        |

---

### 2. CubixCore CPU
#### Architecture:
- **Registers**: 8 general-purpose registers, 2 pointer registers, program counter, stack pointer, and status register.
- **Memory**: Managed dynamically using a virtual MemoryManager.
- **Instruction Set**:
  - Arithmetic: `ADD`, `SUB`, `ADDIMM`, `SUBIMM`
  - Memory: `LOAD`, `STORE`, `LOADIMM`, `STOREPTR`
  - Control Flow: `JMP`, `CALL`, `RET`
  - System Calls: `SYSCALL` for graphics, sound, and I/O operations.

#### Example Assembly:
```assembly
LOADIMM R0, x
LOADIMM R1, y
SYSCALL DRAWPIXEL
```

---

### 3. Compiler Design
#### Key Steps:
1. **Lexer**:
   - Tokenizes Cubasic source code into manageable chunks.

2. **Parser**:
   - Converts tokens into an Abstract Syntax Tree (AST).

3. **Code Generator**:
   - Transforms AST into pseudo-assembly compatible with CubixCore.

4. **Symbol Mapping**:
   - Maps function names and variables to memory locations for debugging and runtime execution.

#### Compiler Features:
- Error handling with detailed feedback.
- Verbose mode for debugging.
- Modular design to separate tokenization, parsing, and code generation.

---

### 4. System Enhancements
#### Graphics:
- Commands like `SPRITE`, `DRAWPIXEL`, and `CLS` for retro-style rendering.
- Support for layers and palettes to simulate hardware limitations.

#### Sound:
- Commands like `BEEP` and `PLAY` for basic audio functionality.

#### Input:
- `INPUT` command for user interactions.

#### System Calls:
| Command       | Description                                    |
|---------------|------------------------------------------------|
| DRAWPIXEL     | Draws a pixel at specified coordinates.        |
| PLAYTONE      | Plays a single tone with specified duration.   |
| GETINPUT      | Fetches user input.                           |

---

## Proposed Architecture
### 1. Modular Refactoring
- **CubasicCompiler**:
  - Encapsulates parsing and code generation.
- **TokenProcessor**:
  - Handles specific command translations.
- **PatternFinder**:
  - Identifies functions and includes dependencies.
- **SymbolMapWriter**:
  - Outputs symbol mappings for debugging.
- **CubixCore**:
  - Executes the generated pseudo-assembly.

### 2. Feature Layers
- **Core Features**: Basic commands (`PRINT`, `DIM`, `FUNCTION`).
- **Flow Control**: Loops (`FOR`, `WHILE`) and conditionals (`IF`, `ELSE`).
- **Advanced Features**: Graphics, sound, and system calls.

---

## Development Plan

### Milestones:
1. **Core Language Features**:
   - Implement `PRINT`, `DIM`, `FUNCTION`, and `CALL`.
   - Validate opcode generation and execution.

2. **Flow Control**:
   - Add loops (`FOR`, `WHILE`) and branching (`IF`, `GOTO`).

3. **Graphics and Sound**:
   - Extend system calls for sprite management and sound effects.

4. **Testing Framework**:
   - Write unit tests for each component.
   - Validate with mock programs.

### Testing Example:
```basic
PRINT "Hello, World!"
FUNCTION Add(a, b)
    RETURN a + b
END
CALL Add(3, 4)
```
Expected Output:
```
Hello, World!
7
```

---

## Future Enhancements
- **Debugger**: Step-through execution of Cubasic code.
- **Extended Graphics**: Tile-based rendering.
- **Advanced Sound**: Multi-channel support.
- **Web-Based Emulator**: Run Cubasic programs in a browser.

---

This design document will serve as a reference for the development and future iterations of the Cubasic programming language and CubixCore CPU emulator.

