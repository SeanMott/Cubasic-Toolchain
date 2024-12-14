# CubixCore CPU Limitations and Features

## Overview
This document outlines the **features** and **limitations** of the CubixCore CPU and proposes strategies to enhance functionality for Cubasic developers. Additionally, it introduces the concept of a **rule break option** that allows developers to bypass preset CPU limitations.

---

## CubixCore Features

### Registers
- **8 General-Purpose Registers**: `R0` to `R7` for arithmetic and data manipulation.
- **2 Pointer Registers**: `PTR1`, `PTR2` for memory addressing.
- **Program Counter (PC)**: Tracks the next instruction.
- **Stack Pointer (SP)**: Manages stack operations.
- **Status Register**: Flags for conditional operations (e.g., zero, carry, negative).

### Memory Management
- Dynamic memory allocation using `ALLOC`.
- Manual deallocation with `FREEPTR`.
- Direct and indirect addressing via `LOAD`, `STORE`, `LOADPTR`, and `STOREPTR`.

### Instruction Set
- **Arithmetic**: `ADD`, `SUB`, `ADDIMM`, `SUBIMM`.
- **Logical**: `AND`, `OR`, `XOR`, `NOT`.
- **Control Flow**: `JMP`, `CALL`, `RET`, and conditional jumps (`JE`, `JNE`, `JLT`).
- **System Calls**: `SYSCALL` for external functions like graphics, sound, and input/output.

### Graphics Support
- Pixel-level drawing: `DRAWPIXEL`, `LINE`, `CIRCLE`, `FILL`.
- Sprite handling: `LOADSPRITE`, `DRAWSprite`.

### Input/Output
- **INPUT**: Accepts user input.
- **PRINT**: Outputs values or text.

### Extensibility
- The `SYSCALL` instruction allows for adding new system-level functions.

---

## CubixCore Limitations

### Finite Registers
- Only **8 general-purpose registers**, which can limit complex computations.

### Memory Constraints
- Simple memory model without garbage collection.
- Manual size management for arrays and strings.

### Basic Flow Control
- No native support for high-level constructs (e.g., `FOR`, `WHILE`, `IF`).

### Error Handling
- Limited to `TRY` and `CATCH`, with no built-in error codes or detailed debugging support.

### Graphics Constraints
- Operations limited to pixel and sprite-level control.
- No built-in support for layers, transformations, or advanced effects.

### Sound
- Basic commands (`BEEP`, `PLAY`) without support for multi-channel or polyphonic sound.

---

## Proposed Enhancements

### Memory Management
- Introduce Cubasic utilities for:
  - Automatic resizing of arrays.
  - Memory pooling to reduce allocation overhead.

### Flow Control
- Add pseudo-assembly macros for:
  - `INIT_LOOP`, `CHECK_LOOP` to simplify loops.
  - Conditional constructs like `IF` and `ELSE`.

### Graphics Layering
- Simulate virtual layers by grouping sprites in Cubasic and managing their rendering order.

### Sound Enhancements
- Extend the `PLAY` command to support:
  - Sequences of notes.
  - Multi-channel playback using `SYSCALL` extensions.

### Error Reporting
- Enhance `TRY` and `CATCH` to:
  - Include error codes and detailed messages.
  - Allow user-defined exceptions.

---

## Rule Break Option

### Concept
The **rule break option** will be defined in the ROM header and will allow developers to bypass specific CPU limitations for advanced use cases. It provides:
1. **Direct Access to Hardware**:
   - Override preset constraints, such as register limits or memory allocation caps.
2. **Custom Instruction Set**:
   - Developers can add or redefine instructions in the CPU emulation layer.
3. **Expanded Graphics and Sound**:
   - Access to advanced effects or external resources not included in the base system.

### Implementation
- **ROM Header Directive**:
  - A flag in the ROM header indicates if the rule break option is enabled.
  - Example:
    ```
    RULE_BREAK: ENABLED
    ```
- **System Call Hook**:
  - Extended `SYSCALL` table for custom developer hooks.

### Use Cases
- Experimentation with unoptimized algorithms.
- Advanced debugging tools.
- High-performance or resource-heavy applications.

---

## Next Steps

1. **Formalize Missing Features**:
   - Identify specific gaps between CubixCore and Cubasic requirements (e.g., enhanced string handling, advanced graphics).

2. **Extend Assembly Commands**:
   - Add new instructions for arrays, strings, and error handling.

3. **Build Abstractions in Cubasic**:
   - Develop high-level commands to encapsulate low-level operations.

4. **Implement Rule Break Support**:
   - Design the ROM header format and define custom instruction hooks.

This approach ensures CubixCore remains efficient while providing flexibility for advanced developers.

