## Assembly Emulator Project

## Application
I want to make a program that emulate the behaviour assembly. Read in a ```.asm``` file and performs the expected output

## Implementation
There are three files in this project: ```assembly.h```, ```assembly.cpp```, and ```compiler.cpp```. Splitting the codebase into three separate files gains the abilithy to reuse codes to other different program without rewriting the original code. As well as easy-to-maintain.

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
        [] Implement:
            [] Regigsters
                [] eax, ebx, ecx, edx
                    [] lower bits for registers
            [] Stack Pointers
                [] eip, esp, ebp
                    [] lower bits for stack pointers
            [] Stack
            [] Lables
            [] Instructions
                [] mov, add, sub, imul, mul, idiv, div, cmp
                [] extentions
                [] push, pop, ret

    Issue:
        [] Lower registers are not accounted for

    Notes:
        Stack pointers are 16-bit register
```
## Code structure overview
### ```assembly.h```:
```
headers
using namespace

enum

class
{
    public:
    private:
}
```

```cpp
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum Type
{
    eax, ebx, ecx, edx, esp, ebp, emov, adde, sube, calle
};

class Assembly
{
    public:
        Assembly(); // Constructor
        void mov(string arg_left, string arg_right);
        void add(string arg_left, string arg_right);
        void sub(string arg_left, string arg_right);
        void call(string arg_left);
        void error_handling(Type error_type);
        void end_program();
        
    private:
        struct Lable
        {
            string lable_name;

            int int_value;
            string str_value;
        };

        struct Register
        {
            int int_value;
            string str_value;
            Register* pointer;
        };

        struct StackPointer
        {
            void* pointer;
        };

        Register* InitializeRegister(Register *register_lable);
        StackPointer* InitializeStackPointer(StackPointer *stackpointer_lable);

        void MOV(Register *register_name, string arg_right);
        void ADD(Register *register_name, string arg_right);
        void SUB(Register *register_name, string arg_right);
        
        void CALL(Register *register_name, string arg_left);
        void PRINT_INT(Register *register_name);
        void PRINT_STRING(Register *register_name);
        void REG_DUMP(Register *register_name);
        void REG_DUMP(StackPointer *stackpointer_name);
        void PRINT_NL();

        Register* eax;
        Register* ebx;
        Register* ecx;
        Register* edx;
        StackPointer* esp;
        StackPointer* ebp;
};
```

### ```assembly.cpp```
```
header

class contructor
class methods
```
```cpp
#include "assembly.h"

Assembly::Assembly()
{
    eax = InitializeRegister(eax);
    ebx = InitializeRegister(ebx);
    ecx = InitializeRegister(ecx);
    edx = InitializeRegister(edx);

    esp = InitializeStackPointer(esp);
    ebp = InitializeStackPointer(ebp);
}

void Assembly::mov(string arg_left, string arg_right)
{
    if(arg_left == "eax," || arg_left == "EAX,")
    {
        MOV(eax, arg_right);
    }
    else if(arg_left == "ebx," || arg_left == "EBX,")
    {
        MOV(ebx, arg_right);
    }
    else if(arg_left == "ecx," || arg_left == "ECX,")
    {
        MOV(ecx, arg_right);
    }
    else if(arg_left == "edx," || arg_left == "EDX,")
    {
        MOV(edx, arg_right);
    }
    else
    {
        error_handling(emov);
    }
}

void Assembly::add(string arg_left, string arg_right)
{
    if(arg_left == "eax," || arg_left == "EAX,")
    {
        ADD(eax, arg_right);
    }
    else if(arg_left == "ebx," || arg_left == "EBX,")
    {
        ADD(ebx, arg_right);
    }
    else if(arg_left == "ecx," || arg_left == "ECX,")
    {
        ADD(ecx, arg_right);
    }
    else if(arg_left == "edx," || arg_left == "EDX,")
    {
        ADD(edx, arg_right);
    }
    else
    {
        error_handling(adde);
    }
}

void Assembly::sub(string arg_left, string arg_right)
{
    if(arg_left == "eax," || arg_left == "EAX,")
    {
        SUB(eax, arg_right);
    }
    else if(arg_left == "ebx," || arg_left == "EBX,")
    {
        SUB(ebx, arg_right);
    }
    else if(arg_left == "ecx," || arg_left == "ECX,")
    {
        SUB(ecx, arg_right);
    }
    else if(arg_left == "edx," || arg_left == "EDX,")
    {
        SUB(edx, arg_right);
    }
    else
    {
        error_handling(sube);
    }
}

void Assembly::call(string arg_left)
{
    if(arg_left == "print_int" || arg_left == "PRINT_INT")
    {
        CALL(eax, "print_int");
    }
    else if(arg_left == "print_string" || arg_left == "PRINT_STRING")
    {
        CALL(eax, "print_string");
    }
    else if(arg_left == "reg_dump" || arg_left == "REG_DUMP")
    {
        CALL(eax, "reg_dump");
    }
    else if(arg_left == "print_nl" || arg_left == "PRINT_NL")
    {
        CALL(eax, "print_nl");
    }
    else
    {
        error_handling(calle);
    }   
}

void Assembly::error_handling(Type error_type)
{
    switch(error_type)
    {
        case(emov): cout << "Error: mov instruction failed" << endl; break;
        case(adde): cout << "Error: add instruction failed" << endl; break;
        case(sube): cout << "Error: sub instruction failed" << endl; break;
        case(calle): cout << "Error: call instruction failed" << endl; break;
    }
}

void Assembly::end_program()
{
    delete eax;
    delete ebx;
    delete ecx;
    delete edx;
    delete esp;
    delete ebp;
}

Assembly::Register* Assembly::InitializeRegister(Register *register_lable)
{
    register_lable = new Register;
    register_lable->int_value = 0;
    register_lable->str_value = "(empty)";
    register_lable->pointer = NULL;
    
    return register_lable;
}

Assembly::StackPointer* Assembly::InitializeStackPointer(StackPointer *stackpointer_lable)
{
    stackpointer_lable = new StackPointer;
    stackpointer_lable->pointer = NULL;
    
    return stackpointer_lable;
}

void Assembly::MOV(Register *register_name, string arg_right)
{
    if(arg_right == "eax" || arg_right == "EAX")
    {
        *register_name = *eax;
    }
    else if(arg_right == "ebx" || arg_right == "EBX")
    {
        *register_name = *ebx;
    }
    else if(arg_right == "ecx" || arg_right == "ECX")
    {
        *register_name = *ecx;
    }
    else if(arg_right == "edx" || arg_right == "EDX")
    {
        *register_name = *edx;
    }
    else
    {
        register_name->int_value = stoi(arg_right);
    }
}

void Assembly::ADD(Register *register_name, string arg_right)
{
    if(arg_right == "eax" || arg_right == "EAX")
    {
        register_name->int_value += eax->int_value;
    }
    else if(arg_right == "ebx" || arg_right == "EBX")
    {
        register_name->int_value += ebx->int_value;
    }
    else if(arg_right == "ecx" || arg_right == "ECX")
    {
        register_name->int_value += ecx->int_value;
    }
    else if(arg_right == "edx" || arg_right == "EDX")
    {
        register_name->int_value += edx->int_value;
    }
    else
    {
        register_name->int_value += stoi(arg_right);
    }
}

void Assembly::SUB(Register *register_name, string arg_right)
{
    if(arg_right == "eax" || arg_right == "EAX")
    {
        register_name->int_value -= eax->int_value;
    }
    else if(arg_right == "ebx" || arg_right == "EBX")
    {
        register_name->int_value -= ebx->int_value;
    }
    else if(arg_right == "ecx" || arg_right == "ECX")
    {
        register_name->int_value -= ecx->int_value;
    }
    else if(arg_right == "edx" || arg_right == "EDX")
    {
        register_name->int_value -= edx->int_value;
    }
    else
    {
        register_name->int_value -= stoi(arg_right);
    }
}

void Assembly::CALL(Register *register_name, string arg_left)
{
    if(arg_left == "print_int")
    {
        PRINT_INT(eax);
    }
    else if(arg_left == "print_string")
    {
        PRINT_STRING(eax);
    }
    else if(arg_left == "reg_dump")
    {
        cout << "EAX: " << eax << endl;
        REG_DUMP(eax);
        cout << endl;
        
        cout << "EBX: " << ebx << endl;
        REG_DUMP(ebx);
        cout << endl;
        
        cout << "ECX: " << ecx << endl;
        REG_DUMP(ecx);
        cout << endl;
        
        cout << "EDX: " << edx << endl;
        REG_DUMP(edx);
        cout << endl;
        
        cout << "ESP: " << esp << endl;
        REG_DUMP(esp);
        cout << endl;
        
        cout << "EBP: " << ebp << endl;
        REG_DUMP(ebp);
    }
    else if(arg_left == "print_nl" || arg_left == "PRINT_NL")
    {
        PRINT_NL();
    }
    else
    {
        error_handling(calle);
    }
}

void Assembly::PRINT_INT(Register *register_name)
{
    cout << register_name->int_value;    
}

void Assembly::PRINT_STRING(Register *register_name)
{
    cout << register_name->str_value;    
}

void Assembly::REG_DUMP(Register *register_name)
{
    cout << "   int_value: " <<register_name->int_value << endl;
    cout << "   str_value: " << register_name->str_value << endl;
    cout << "   ptr_value: " << register_name->pointer << endl;
}

void Assembly::REG_DUMP(StackPointer *stackpointer_name)
{
    cout << "   ptr_value: " << stackpointer_name->pointer << endl;
}

void Assembly::PRINT_NL()
{
    cout << endl;
}
```


### ```compiler.cpp```
```
header
function prototypes

main
functions
```

```cpp
#include "assembly.h"

void Interpreter(char argv[]);
int Execute(Assembly assembly, string instruction, string opcode_left, string opcode_right);
void Information();

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        if(argc < 2)
        {
            cout << "./compiler [program]" << endl;
            cout << "./compiler info" << endl;
        }
        else
        {
            cout << "Error: only one program supported" << endl;
        }
    }
    else
    {
        string input_check = argv[1];
        
        if(input_check == "info")
        {
            Information();
        }
        else
        {
            ifstream read_test;
    
            read_test.open(argv[1]);
    
            if(read_test.fail())
            {
                read_test.close();

                char user_input;
                
                cout << "Error: unable to open file " << argv[1] << endl;
                cout << "Create: " << argv[1] << "?" << endl;
                cout << "[y / N]" << endl;
                cout << ">: ";
                cin >> user_input;
    
                if(user_input == 'y' || user_input == 'Y') // Generates a template
                {
                    ofstream create_file;
                    create_file.open(argv[1]);
    
                    create_file << "%include <assembly.cpp>" << endl;
                    create_file << endl;
                    create_file << "segment .data" << endl;
                    create_file << endl;
                    create_file << "segment .bss" << endl;
                    create_file << endl;
                    create_file << "segment .text" << endl;
                    create_file << "    global asm_main" << endl;
                    create_file << endl;
                    create_file << "asm_main:" << endl;
                    create_file << "    ";
    
                    create_file.close();
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                read_test.close();
                Interpreter(argv[1]);
            }
        }
    }

    return 0;
}

void Information()
{
    cout << "Made by: Jerome Cabarus" << endl;
    cout << endl;

    cout << "Supported features:" << endl;
    cout << "   Instructions:" << endl;
    cout << "       mov" << endl;
    cout << "       sub" << endl;
    cout << "       add" << endl;
    cout << "       call" << endl;
    cout << endl;
    cout << "   Registers: " << endl;
    cout << "       eax, ebx, ecx, edx, esp, ebp" << endl;
    cout << endl;
    
    cout << "Usupported features:" << endl;
    cout << "   lables, loops" << endl;
}

void Interpreter(char argv[])
{
    ifstream read_open; // Input file stream

    Assembly assembly; // Defined class
    string instruction, opcode_left, opcode_right, buffer; // Variable
    int execute_check, temp = 0;
    
    read_open.open(argv);

    while(buffer != "asm_main:") // Off set check
    {
        read_open >> buffer;
        if(buffer == "<assembly.cpp>")
        {
            temp++;
        }
    }

    if(temp == 0) // Template program check
    {
        cout << "Error: program template error" << endl;
        read_open.close();
    }
    else
    {
        while(!read_open.eof() && execute_check != -1)
        {
            read_open >> instruction;
            
            if(instruction != "") // Empty instruction check
            {
                if(instruction == "call")
                {
                    read_open >> opcode_left;
                }
                else
                {
                    read_open >> opcode_left >> opcode_right;
                }
        
                execute_check = Execute(assembly, instruction, opcode_left, opcode_right);
            }
        }
    }

    assembly.end_program(); // Free memory
}

int Execute(Assembly assembly, string instruction, string opcode_left, string opcode_right)
{
    if(instruction == "mov" || instruction == "MOV")
    {
        assembly.mov(opcode_left, opcode_right);
    }
    else if(instruction == "add" || instruction == "ADD")
    {
        assembly.add(opcode_left, opcode_right);
    }
    else if(instruction == "sub" || instruction == "SUB")
    {
        assembly.sub(opcode_left, opcode_right);
    }
    else if(instruction == "call")
    {
        assembly.call(opcode_left);
    }
    else
    {
        cout << "Error: [" << instruction << "] invalid instruction" << endl;
        return -1;
    }

    return 0;
}
```