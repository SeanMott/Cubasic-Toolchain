# Intro Programmers Guide

Cubasic is a higher level language that gets compiled down to CubASM.

Every Cubasic file ends in .cbs. This file defines the functions and variables that will be compiled down to CubASM.

## Writing the Cubasic file

Hello.cbs
```
#this is a comment
FUNCTION main() #this is the main function
    PRINT "Hello, Cubasic!" #this prints the string literal, Hello, Cubasic! to the screen
END #this ends the function
```

Like Python, Cubasic doesn't have semi-colons. Every expression is split into lines.

All reserved keywords are in all caps. For a full list of [Cubasic Reserved Keywords]().

This guide will walk you through creating your first program, compiling, assembling, and running on the emulator.

1. Create a file named `Hello.cbs`, open it in your editor of choice.

2. Write `FUNCTION main()`
`FUNCTION` defines the start of a function block. It will always be followed by the name of the function. In this case `main`. The `()` are where any arguments you wanted to pass into the function would go. The `()` will always be after the function name. Having a space between the name and `(` will cause a error.

`FUNCTION main()` IS VALID.

`FUNCTION main ()` IS NOT.

Tabs are not required for a valid program. But help with readability.

`PRINT "Hello, Cubasic!"` will print any strings to the screen. It automatically adds a new line to it.

The last part of our program is the `END` keyword. This marks the end of our function.

```
FUNCTION main()
    PRINT "Hello, Cubasic!"
END
```
Is the entire hello world program.

If you wish you can add comments.

```
#this is the main function, the entry point of our program
FUNCTION main()

    #this prints Hello, Cubasic! to the screen
    PRINT "Hello, Cubasic!"

#ends the function
END
```

## Compiling the Cubasic file into CubASM

Get the [latest release]() of the Cubasic compiler. Open a command prompt.

```
Cubasic -s Hello.cbs -o Hello.csm
```
This invokes the compiler and takes a single Cubasic file with the `-s` flag. It will then output the assembly file with the name `Hello`. CubASM files end with the `.csm` extension.

## Inspecting the CubASM file

The default arguments is to output a plain text assembly file named `Hello.csm`.

If you open this file you will see

```
LOAD R1 'H'
```