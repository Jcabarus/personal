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