# Cubasic Programming Language and CubixCore CPU Design Document

## Project Vision
To create a simple yet modern programming language (Cubasic) for a retro-inspired virtual console (CubixCore). The goal is to blend the simplicity of retro systems like NES and Game Boy with modern programming conveniences such as named functions, function maps, and structured flow control. The system should be approachable for beginners while offering enough power for advanced users.

## Project Overview

There are three components to Cube eco-system.

- Cubasic || The higher level language akin to Basic.
- CubASM || The psudo assembly that runs in the emulator.
- Cubix || The emulator for the fake console.

## Futhur Docs

Docs breaking down each component. The source code itself also has more docs that will be linked here.

### Cubasic
- [Intro Programmers Guide]() explains how to make your first program in Cubasic and run it in the emulator.
- [Cubasic Example Programs](), more programs written in Cubasic and example FCube build scripts for larger scale projects.
- [Cubasic User's Manual]() the entire list of keywords and syntax for Cubasic.

### CubASM
- [Hello World in CubASM](), how to write a Hello World program in raw CubASM. For when you really wanna get down and dirty in the CPU's language.
- [CubASM Example Programs](), more programs written in CubASM.
- [CubASM Assembler Guide](), lists every instructions and how they handle data.

### Cubix
- [Cubix CPU]() || The CPU's specs and it's designed limitations.
- [Cubix ROM Spec]() || The structure of a ROM.

## Project Overview
- [Design Doc](Docs/CubasicDesignDoc.md)
- [Cubasic Language Instructions](Docs/CubasicLanguageInstructions.md)
- [Cubix Core CPU](Docs/CubixCoreCPULimitations_Features.md)
- [Cubix ROM Structure](Docs/Cubixcore_RomStructure.md)
- [Cubix Core ASM Commands](Docs/CubixCoreAssemblyCommands.md)

## Toochain Overview
- 

## Building

## Windows

### Step 1: Deps
- Python 3, Visual Studio 2022 or beyond, and CMake is required

- MsBuild must be in the System Path. It can be found after installing Visual Studio, roughly at `C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin`

### Step 2: Build/Gen

- run `ProjectSetup.py` in the root of the folder (ie where this README is)

- wait for `ProjectSetup` to download everything, build SDL 3, generate the project, perform a test build and move SDL to the bin folder.

- open Visual Studio and build

- go into `Venders/SDL/Build` and pick a flavor of SDL by grabbing the DLL in `Release`, `RelWithDebInfo`, or `MinSizeRel`. Throw it next to `FamicubeEmulator.exe` build in `bin/BuildTypeOfYourChoiceHere/Famicube-Emulator`

- Enjoy :3


## Credits

-------Insert Jinxy Stuff here---------