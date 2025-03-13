#include "assembly.h"
#include <fstream>

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