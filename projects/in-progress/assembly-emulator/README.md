## Assembly Emulator

## Application
I want to make a program that emulate the behaviour assembly. Read in a ```.asm``` file and performs the expected output

## Implementation
There are three files in this project: ```assembly.h```, ```assembly.cpp```, and ```compiler.cpp```. Splitting the codebase into three separate files gains the ability to reuse codes to other different program without rewriting the original code, and easy to maintain.

* In ```assembly.h```:
    * This file contains all the class method prototypes, structs, and the standard library headers such as ```<iostream>``` and ```<fstream>```
* In ```asssembly.cpp```:
    * This file contains all the actual functions from the ```assembly.h```
* In ```compiler.cpp```:
    * This file contains the file reading and executing

## Process
How this works is that once compiled and provided a ```.asm``` code:
1. Prechecks if the ```.asm``` file is unaccessible, either the user is prompted to create the file or exit the program 
1. Initializes all the registers and stack pointers such as: eax, ebx, ecx, edx, esp, ebp, etc... 
1. Checks if the ```.asm``` file's template is correct
1. After all the checks are done and successfull, then it starts from ```asm_main:``` reading instruction and opcodes line by line.

## Progress
```
    Task:
        [] Overhaul:
            [] Registers
                [] Extended, high, low
            [] Parsing
            [] Instructions
                [] mov, movsx, add, sub, inc, dec
        [] Implement:
            [*] Regigsters
                [*] eax, ebx, ecx, edx
                    [*] lower bits for registers
            [] Stack Pointers
                [] eip, esp, ebp
                    [] lower bits for stack pointers
            [] Lables
            [] Instructions
                [] Data Movement:
                   >[] *mov, *movsx, movzx
                [] Arithmetic:
                    >[] *add, *sub, *inc, *dec, imul, mul, idiv, div
                [] Control Flow:
                    [] jmp, je, jz, jne, jnz, jg, jl, jge, jle, 
                [] Stack Operation:
                    [] push, pop, call, ret
                [] Syscall
            [] Stack
            [] Comment

        [] Rewrite:
            [*] mov, add, sub

    Issue:
        [] 8-bit registers are not initialized properly
        [] mov for 8-bit register is not working as intended

    Notes:
        Stack pointers are 16-bit register
        ESP keeps track of the top stack
```
## Code structure overview

### [```assembly.h```](https://gitlab.com/jcabarus/personal/-/blob/main/projects/assembly-emulator/assembly.h?ref_type=heads)
```
headers
using

enum

class
{
    public:
    private:
}
```

### [```assembly.cpp```](https://gitlab.com/jcabarus/personal/-/blob/main/projects/assembly-emulator/assembly.cpp?ref_type=heads)
```
header

class constructor
class methods
```

### [```compiler.cpp```](https://gitlab.com/jcabarus/personal/-/blob/main/projects/assembly-emulator/compiler.cpp?ref_type=heads)
```
header
function prototypes

main
functions
```



## How it works:
Given a program let's say: **test-program1.asm**, **test-program2.asm** **test-program3.asm**. Using the executable **compiler** it would output the proper out as if it was compiled in assembly. Basically it's just an interpreter and reads the file line by line.

Registers are implemented by using structs and instructions using class methods. The current issue I am facing is the implementation of variable defined by the user as well as lower registers like **al** or **ah**. Comments are not supported yet.

So far the only instructions are supported are **mov**, **add**, **sub**, **call**, and **movsx** 

## How to buidl:
Compile: <br> 
`g++ src/assembly.cpp src/compiler.cpp -o executable`