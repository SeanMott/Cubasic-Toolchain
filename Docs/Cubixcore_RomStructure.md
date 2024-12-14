# CubixCore ROM Structure

## Overview
This document defines the structure of a ROM file for the CubixCore CPU. A ROM file acts as a container for assembly code and associated metadata, allowing the CubixCore CPU to interpret and execute programs effectively. It also introduces the **rule break option** that can enable advanced developer capabilities by bypassing standard CPU constraints.

---

## ROM File Structure
The ROM file for the CubixCore CPU is divided into the following sections:

### 1. **Header**
The header contains metadata about the ROM, including its version, developer information, and configuration options. Additionally, it supports advanced features and runtime configurations.

#### Header Fields:
| Field            | Description                                                       |
|------------------|-------------------------------------------------------------------|
| ROM_VERSION      | Specifies the ROM version.                                        |
| AUTHOR           | Name or identifier of the developer.                              |
| TITLE            | The name of the program.                                          |
| DATE             | Build date of the ROM.                                            |
| RULE_BREAK       | Indicates whether the rule break option is enabled (YES/NO).      |
| START_ADDRESS    | The starting address for the main program execution.              |
| SYMBOL_MAP       | Name of the accompanying symbol map file (if applicable).         |
| EMULATION_MODE   | Specifies hardware emulation mode (e.g., CLASSIC, ENHANCED).      |
| FEATURE_TOGGLES  | Enable or disable hardware features (e.g., SOUND=YES, GRAPHICS=NO).|

#### Example:
```
ROM_VERSION=1.0
AUTHOR=DeveloperName
TITLE=MyCubixProgram
DATE=2024-12-14
RULE_BREAK=YES
START_ADDRESS=0x1000
SYMBOL_MAP=myprogram.map
EMULATION_MODE=CLASSIC
FEATURE_TOGGLES=SOUND=YES, GRAPHICS=NO
```

### 2. **System Call Table (Optional)**
This table defines any additional system calls introduced by the program. Each entry includes:
- **System Call ID**: A unique identifier for the system call.
- **Description**: A brief summary of the functionality.
- **Entry Point**: Address or label for the system call handler.
- **Conditions**: Optional runtime conditions for enabling the system call.

#### Example:
```
SYSCALL_TABLE:
0x01=CustomDrawHandler ; Custom draw operation
0x02=AdvancedSoundAPI  ; Extended sound handling
CONDITIONS:
IF FEATURE_GRAPHICS_ENABLED THEN
    0x03=LayeredGraphicsHandler
ENDIF
```

### 3. **Program, Character, and Sound Banks**
The ROM file is split into three distinct sections for better organization and debugging.

#### 3.1 **PRG (Program Bank)**
- Contains the main program logic and assembly instructions.
- Includes labels and subroutine definitions for execution.

#### Example:
```
PRG_BANK:
START:
    LOADIMM R0, 10
    LOADIMM R1, 20
    ADD R0, R1
    SYSCALL 0x01
    HALT
```

#### 3.2 **CHR (Character Bank)**
- Stores graphical data like sprites and tile maps.
- Designed for quick access and rendering.

#### Example:
```
CHR_BANK:
SPRITE_1: .BYTE 0xFF, 0x81, 0xFF ; Simple 8x8 sprite data
TILE_MAP: .BYTE 0x00, 0x01, 0x02, 0x03
```

#### 3.3 **SRG (Sound Bank)**
- Contains sound effects and music sequences.
- Allows for modular audio data storage.

#### Example:
```
SRG_BANK:
SOUND_1: .BYTE 0x1A, 0x2B, 0x3C ; Sound effect data
MUSIC_TRACK: .BYTE 0x10, 0x20, 0x30
```

### 4. **Symbol Map (Optional)**
The symbol map is an auxiliary file that maps function names to memory addresses. It is referenced in the header for debugging purposes.

#### Example:
```
SYMBOL_MAP:
main=0x1000
function1=0x1040
function2=0x1080
```

### 5. **Debug Info (Optional)**
An optional section for embedding debugging metadata, such as:
- Source code references.
- Line-to-instruction mappings.
- Breakpoints or watch variables.

#### Example:
```
DEBUG_INFO:
SOURCE_LINE=15 INSTRUCTION=LOADIMM R0, 10
BREAKPOINT=0x1004 ; Halt execution at this address
```

---

## Rule Break Option

### Description
The rule break option allows developers to bypass standard CubixCore limitations, enabling custom hardware configurations or enhanced performance for advanced applications.

### Implementation
1. **Header Directive**:
   - The `RULE_BREAK` field in the header specifies if the rule break option is enabled.
   - Example: `RULE_BREAK=YES`.

2. **Custom Instruction Set**:
   - Developers can define their own instructions or overrides in the code section.

3. **Extended System Calls**:
   - Add custom functionality to the system call table.

4. **Hardware Access**:
   - Provides direct access to emulated hardware, such as expanded memory, additional registers, or custom graphics processors.

### Example ROM with Rule Break Enabled:
```
ROM_VERSION=1.0
AUTHOR=AdvancedDev
TITLE=ExperimentalROM
DATE=2024-12-14
RULE_BREAK=YES
START_ADDRESS=0x1000
SYMBOL_MAP=experimental.map

SYSCALL_TABLE:
0x01=ExperimentalGraphicsHandler

CHR_BANK:
SPRITE_1: .BYTE 0xFF, 0x81, 0xFF

SRG_BANK:
SOUND_1: .BYTE 0x1A, 0x2B, 0x3C

DEBUG_INFO:
SOURCE_LINE=42 INSTRUCTION=SYSCALL 0x01

PRG_BANK:
START:
    LOADIMM R0, 5
    SYSCALL 0x01
    HALT
```

---

## Validation
To ensure compatibility with the CubixCore CPU, ROM files must:
1. Include a valid header with all required fields.
2. Use recognized assembly instructions, unless `RULE_BREAK=YES` is specified.
3. Pass validation tests for:
   - **Field Presence**: Verify all required header fields are present.
   - **Instruction Validity**: Ensure all assembly instructions match the opcode table.
   - **Memory Constraints**: Confirm data sections do not exceed memory boundaries.
   - **Rule Break Conditions**: Verify that any custom instructions or features follow the specified extensions.

---

## Future Extensions
1. **Debugging Support**: Extend debugging metadata to include:
   - Watch variables.
   - Execution profiling data.
2. **Version History**: Support for multi-author contributions and a change log:
   ```
   VERSION_HISTORY:
   v1.0: Initial release
   v1.1: Added sprite handling
   v2.0: Introduced debugging metadata
   ```
3. **Advanced Metadata**: Define dependencies for modular ROM development:
   ```
   DEPENDENCIES:
   graphics_library.rom
   sound_library.rom
   ```

This structure provides a robust and extensible format for CubixCore ROMs, balancing simplicity and flexibility.

