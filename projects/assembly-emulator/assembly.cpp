#include "assembly.h"

Assembly::Assembly()
{
    Register* eax = new Register;
    Register* ebx = new Register;
    Register* ecx = new Register;
    Register* edx = new Register;
}

void Assembly::error_handling(Type error_type)
{
    switch(error_type)
    {
        case(movt): cout << "Error: mov instruction failed" << endl; break;
        case(addt): cout << "Error: add instruction failed" << endl; break;
        case(subt): cout << "Error: sub instruction failed" << endl; break;
    }
}