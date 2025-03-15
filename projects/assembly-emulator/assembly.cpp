#include "assembly.h"

Assembly::Assembly()
{
    eax = InitializeERegister(eax);
    ax = InitializeARegister(ax);
    al = InitializeLRegister(al);
    ah = InitializeLRegister(ah);
    
    ebx = InitializeERegister(ebx);
    bx = InitializeARegister(bx);
    bl = InitializeLRegister(bl);
    bh = InitializeLRegister(bh);
    
    ecx = InitializeERegister(ecx);
    cx = InitializeARegister(cx);
    cl = InitializeLRegister(cl);
    ch = InitializeLRegister(ch);
    
    edx = InitializeERegister(edx);
    dx = InitializeARegister(dx);
    dl = InitializeLRegister(dl);
    dh = InitializeLRegister(dh);

    // esp = InitializeStackPointer(esp);
    // ebp = InitializeStackPointer(ebp);
}

void Assembly::mov(string arg_left, string arg_right)
{
    if(arg_left[0] == 'e') // Check if register is 32-bit
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
    }
    else if(arg_left[1] == 'x') // Check if register is 16-bit
    {
        if(arg_left == "ax," || arg_left == "AX,")
        {
            MOV(ax, arg_right);
        }
        else if(arg_left == "bx," || arg_left == "BX,")
        {
            MOV(bx, arg_right);
        }
        else if(arg_left == "cx," || arg_left == "CX,")
        {
            MOV(cx, arg_right);
        }
        else if(arg_left == "dx," || arg_left == "DX,")
        {
            MOV(dx, arg_right);
        }
    }
    else if(arg_left[1] == 'l' || arg_left[1] == 'h') // Check if register is 8-bit
    {
        if(arg_left[1] == 'l') // lower bit
        {
            if(arg_left == "al," || arg_left == "AL,")
            {
                MOV(al, arg_right);
            }
            else if(arg_left == "bl," || arg_left == "BL,")
            {
                MOV(bl, arg_right);
            }
            else if(arg_left == "cl," || arg_left == "CL,")
            {
                MOV(cl, arg_right);
            }
            else if(arg_left == "dl," || arg_left == "DL,")
            {
                MOV(dl, arg_right);
            }
        }
        else // higher bit
        {
            if(arg_left == "ah," || arg_left == "AH,")
            {
                MOV(ah, arg_right);
            }
            else if(arg_left == "bh," || arg_left == "BH,")
            {
                MOV(bh, arg_right);
            }
            else if(arg_left == "ch," || arg_left == "CH,")
            {
                MOV(cx, arg_right);
            }
            else if(arg_left == "dh," || arg_left == "DH,")
            {
                MOV(dx, arg_right);
            }
        }
    }
    else
    {

        error_handling(emov);
    }
}

void Assembly::add(string arg_left, string arg_right)
{
    if(arg_left[0] == 'e') // Check if register is 32-bit
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
    }
    else if(arg_left[1] == 'x') // Check if register is 16-bit
    {
        if(arg_left == "ax," || arg_left == "AX,")
        {
            ADD(ax, arg_right);
        }
        else if(arg_left == "bx," || arg_left == "BX,")
        {
            ADD(bx, arg_right);
        }
        else if(arg_left == "cx," || arg_left == "CX,")
        {
            ADD(cx, arg_right);
        }
        else if(arg_left == "dx," || arg_left == "DX,")
        {
            ADD(dx, arg_right);
        }
    }
    else if(arg_left[1] == 'l' || arg_left[1] == 'h') // Check if register is 8-bit
    {
        if(arg_left[1] == 'l') // lower bit
        {
            if(arg_left == "al," || arg_left == "AL,")
            {
                ADD(al, arg_right);
            }
            else if(arg_left == "bl," || arg_left == "BL,")
            {
                ADD(bl, arg_right);
            }
            else if(arg_left == "cl," || arg_left == "CL,")
            {
                ADD(cl, arg_right);
            }
            else if(arg_left == "dl," || arg_left == "DL,")
            {
                ADD(dl, arg_right);
            }
        }
        else // higher bit
        {
            if(arg_left == "ah," || arg_left == "AH,")
            {
                ADD(ah, arg_right);
            }
            else if(arg_left == "bh," || arg_left == "BH,")
            {
                ADD(bh, arg_right);
            }
            else if(arg_left == "ch," || arg_left == "CH,")
            {
                ADD(ch, arg_right);
            }
            else if(arg_left == "dh," || arg_left == "DH,")
            {
                ADD(dh, arg_right);
            }
        }
    }
    else
    {

        error_handling(adde);
    }
}

void Assembly::sub(string arg_left, string arg_right)
{
    if(arg_left[0] == 'e') // Check if register is 32-bit
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
    }
    else if(arg_left[1] == 'x') // Check if register is 16-bit
    {
        if(arg_left == "ax," || arg_left == "AX,")
        {
            SUB(ax, arg_right);
        }
        else if(arg_left == "bx," || arg_left == "BX,")
        {
            SUB(bx, arg_right);
        }
        else if(arg_left == "cx," || arg_left == "CX,")
        {
            SUB(cx, arg_right);
        }
        else if(arg_left == "dx," || arg_left == "DX,")
        {
            SUB(dx, arg_right);
        }
    }
    else if(arg_left[1] == 'l' || arg_left[1] == 'h') // Check if register is 8-bit
    {
        if(arg_left[1] == 'l') // lower bit
        {
            if(arg_left == "al," || arg_left == "AL,")
            {
                SUB(al, arg_right);
            }
            else if(arg_left == "bl," || arg_left == "BL,")
            {
                SUB(bl, arg_right);
            }
            else if(arg_left == "cl," || arg_left == "CL,")
            {
                SUB(cl, arg_right);
            }
            else if(arg_left == "dl," || arg_left == "DL,")
            {
                SUB(dl, arg_right);
            }
        }
        else // higher bit
        {
            if(arg_left == "ah," || arg_left == "AH,")
            {
                SUB(ah, arg_right);
            }
            else if(arg_left == "bh," || arg_left == "BH,")
            {
                SUB(bh, arg_right);
            }
            else if(arg_left == "ch," || arg_left == "CH,")
            {
                SUB(ch, arg_right);
            }
            else if(arg_left == "dh," || arg_left == "DH,")
            {
                SUB(dh, arg_right);
            }
        }
    }
    else
    {

        error_handling(sube);
    }
}

void Assembly::inc(string arg_left)
{
    if(arg_left == "eax" || arg_left == "EAX")
    {
        INC(eax);
    }
    else if(arg_left == "ebx" || arg_left == "EBX")
    {
        INC(ebx);
    }
    else if(arg_left == "ecx" || arg_left == "ECX")
    {
        INC(ecx);
    }
    else if(arg_left == "edx" || arg_left == "EDX")
    {
        INC(edx);
    }
    else
    {
        error_handling(einc);
    }
}

void Assembly::dec(string arg_left)
{
    if(arg_left == "eax" || arg_left == "EAX")
    {
        DEC(eax);
    }
    else if(arg_left == "ebx" || arg_left == "EBX")
    {
        DEC(ebx);
    }
    else if(arg_left == "ecx" || arg_left == "ECX")
    {
        DEC(ecx);
    }
    else if(arg_left == "edx" || arg_left == "EDX")
    {
        DEC(edx);
    }
    else
    {
        error_handling(edec);
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

// void Assembly::push()
// void Assembly::pop()
// void Assembly::ret()

void Assembly::error_handling(Type error_type)
{
    switch(error_type)
    {
        case(emov): cout << "Error: mov instruction failed" << endl; break;
        case(adde): cout << "Error: add instruction failed" << endl; break;
        case(sube): cout << "Error: sub instruction failed" << endl; break;
        case(calle): cout << "Error: call instruction failed" << endl; break;
        case(einc): cout << "Error: inc instruction failed" << endl; break;
        case(edec): cout << "Error: dec instruction failed" << endl; break;
    }
}

void Assembly::end_program()
{
    delete eax;
    delete ebx;
    delete ecx;
    delete edx;
    // delete esp;
    // delete ebp;
}

Assembly::ERegister* Assembly::InitializeERegister(ERegister *register_lable)
{
    register_lable = new ERegister;
    register_lable->int_value = 0xffffffff;
    register_lable->str_value = "(empty)";
    
    return register_lable;
}

Assembly::ARegister* Assembly::InitializeARegister(ARegister *register_lable)
{
    register_lable = new ARegister;
    register_lable->int_value = 0xffff;
    
    return register_lable;
}

Assembly::LRegister* Assembly::InitializeLRegister(LRegister *register_lable)
{
    register_lable = new LRegister;
    register_lable->int_value = 0xff;
    
    return register_lable;
}

// Assembly::StackPointer* Assembly::InitializeStackPointer(StackPointer *stackpointer_lable)
// {
//     stackpointer_lable = new StackPointer;
//     stackpointer_lable->pointer = NULL;
    
//     return stackpointer_lable;
// }

void Assembly::MOV(ERegister *register_name, string arg_right) // 32-bit register
{
    if(arg_right == "eax" || arg_right == "EAX") // eax
    {
        *register_name = *eax;
    }
    else if(arg_right == "ebx" || arg_right == "EBX") // ebx
    {
        *register_name = *ebx;
    }
    else if(arg_right == "ecx" || arg_right == "ECX") // ecx
    {
        *register_name = *ecx;
    }
    else if(arg_right == "edx" || arg_right == "EDX") // edx
    {
        *register_name = *edx;
    }
    else
    {
        register_name->int_value = stoi(arg_right);
    }
}

void Assembly::MOV(ARegister *register_name, string arg_right) // 16-bit register
{
    if(arg_right == "ax" || arg_right == "AX") // ax
    {
        *register_name = *ax;
    }
    else if(arg_right == "bx" || arg_right == "BX") // bx
    {
        *register_name = *bx;
    }
    else if(arg_right == "cx" || arg_right == "CX") // cx
    {
        *register_name = *cx;
    }
    else if(arg_right == "dx" || arg_right == "DX") // dx
    {
        *register_name = *dx;
    }
    else
    {
        register_name->int_value = stoi(arg_right);
    }
}

void Assembly::MOV(LRegister *register_name, string arg_right) // 8-bit register
{
    if(arg_right[1] = 'l')
    {
        if(arg_right == "al" || arg_right == "AL") // al
        {
            *register_name = *al;
        }
        else if(arg_right == "bl" || arg_right == "BL") // bl
        {
            *register_name = *bl;
        }
        else if(arg_right == "cl" || arg_right == "CL") // cl
        {
            *register_name = *cl;
        }
        else if(arg_right == "dl" || arg_right == "DL") // dl
        {
            *register_name = *dl;
        }
    }
    else if(arg_right[1] == 'h')
    {
        if(arg_right == "ah" || arg_right == "AH") // ah
        {
            *register_name = *ah;
        }
        else if(arg_right == "bh" || arg_right == "BH") // bh
        {
            *register_name = *bh;
        }
        else if(arg_right == "ch" || arg_right == "CH") // ch
        {
            *register_name = *ch;
        }
        else if(arg_right == "dh" || arg_right == "DH") // dh
        {
            *register_name = *dh;
        }
    }
    else
    {
        register_name->int_value = stoi(arg_right);
    }
}

void Assembly::ADD(ERegister *register_name, string arg_right) // 32-bit operation
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

void Assembly::ADD(ARegister *register_name, string arg_right) // 16-bit operation
{
    if(arg_right == "ax" || arg_right == "AX")
    {
        register_name->int_value += ax->int_value;
    }   
    else if(arg_right == "bx" || arg_right == "BX")
    {
        register_name->int_value += bx->int_value;
    }
    else if(arg_right == "cx" || arg_right == "CX")
    {
        register_name->int_value += cx->int_value;
    }
    else if(arg_right == "dx" || arg_right == "DX")
    {
        register_name->int_value += dx->int_value;
    }
    else
    {
        register_name->int_value += stoi(arg_right);
    }
}

void Assembly::ADD(LRegister *register_name, string arg_right) // 8-bit operation
{
    if(arg_right[1] = 'l') // lower
    {
        if(arg_right == "al" || arg_right == "AL") // al
        {
            register_name->int_value += al->int_value;
        }
        else if(arg_right == "bl" || arg_right == "BL") // bl
        {
            register_name->int_value += bl->int_value;
        }
        else if(arg_right == "cl" || arg_right == "CL") // cl
        {
            register_name->int_value += cl->int_value;
        }
        else if(arg_right == "dl" || arg_right == "DL") // dl
        {
            register_name->int_value += dl->int_value;
        }
    }
    else if(arg_right[1] == 'h') // higher
    {
        if(arg_right == "ah" || arg_right == "AH") // ah
        {
            register_name->int_value += ah->int_value;
        }
        else if(arg_right == "bh" || arg_right == "BH") // bh
        {
            register_name->int_value += bh->int_value;
        }
        else if(arg_right == "ch" || arg_right == "CH") // ch
        {
            register_name->int_value += ch->int_value;
        }
        else if(arg_right == "dh" || arg_right == "DH") // dh
        {
            register_name->int_value += dh->int_value;
        }
    }
    else
    {
        register_name->int_value += stoi(arg_right);
    }
}

void Assembly::SUB(ERegister *register_name, string arg_right) // 32-bit operation
{
    if(arg_right == "ax" || arg_right == "AX")
    {
        register_name->int_value -= ax->int_value;
    }   
    else if(arg_right == "bx" || arg_right == "BX")
    {
        register_name->int_value -= bx->int_value;
    }
    else if(arg_right == "cx" || arg_right == "CX")
    {
        register_name->int_value -= cx->int_value;
    }
    else if(arg_right == "dx" || arg_right == "DX")
    {
        register_name->int_value -= dx->int_value;
    }
    else
    {
        register_name->int_value -= stoi(arg_right);
    }
}

void Assembly::SUB(ARegister *register_name, string arg_right) // 16-bit operation
{
    if(arg_right == "ax" || arg_right == "AX")
    {
        register_name->int_value -= ax->int_value;
    }   
    else if(arg_right == "bx" || arg_right == "BX")
    {
        register_name->int_value -= bx->int_value;
    }
    else if(arg_right == "cx" || arg_right == "CX")
    {
        register_name->int_value -= cx->int_value;
    }
    else if(arg_right == "dx" || arg_right == "DX")
    {
        register_name->int_value -= dx->int_value;
    }
    else
    {
        register_name->int_value -= stoi(arg_right);
    }
}

void Assembly::SUB(LRegister *register_name, string arg_right) // 8-bit operation
{
    if(arg_right[1] = 'l') // lower
    {
        if(arg_right == "al" || arg_right == "AL") // al
        {
            register_name->int_value -= al->int_value;
        }
        else if(arg_right == "bl" || arg_right == "BL") // bl
        {
            register_name->int_value -= bl->int_value;
        }
        else if(arg_right == "cl" || arg_right == "CL") // cl
        {
            register_name->int_value -= cl->int_value;
        }
        else if(arg_right == "dl" || arg_right == "DL") // dl
        {
            register_name->int_value -= dl->int_value;
        }
    }
    else if(arg_right[1] == 'h') // higher
    {
        if(arg_right == "ah" || arg_right == "AH") // ah
        {
            register_name->int_value -= ah->int_value;
        }
        else if(arg_right == "bh" || arg_right == "BH") // bh
        {
            register_name->int_value -= bh->int_value;
        }
        else if(arg_right == "ch" || arg_right == "CH") // ch
        {
            register_name->int_value -= ch->int_value;
        }
        else if(arg_right == "dh" || arg_right == "DH") // dh
        {
            register_name->int_value -= dh->int_value;
        }
    }
    else
    {
        register_name->int_value -= stoi(arg_right);
    }
}

void Assembly::INC(ERegister *register_name)
{
    register_name->int_value =+ 1;
}

void Assembly::DEC(ERegister *register_name)
{
    register_name->int_value -= 1;
}

void Assembly::CALL(ERegister *register_name, string arg_left)
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
        
        // cout << "ESP: " << esp << endl;
        // REG_DUMP(esp);
        // cout << endl;
        
        // cout << "EBP: " << ebp << endl;
        // REG_DUMP(ebp);
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

// void Assembly::PUSH()
// void Assembly::POP()
// void Assembly::RET()

void Assembly::PRINT_INT(ERegister *register_name)
{
    cout << register_name->int_value;    
}

void Assembly::PRINT_STRING(ERegister *register_name)
{
    cout << register_name->str_value;    
}

void Assembly::REG_DUMP(ERegister *register_name)
{
    cout << "   int_value: " <<register_name->int_value << endl;
    cout << "   str_value: " << register_name->str_value << endl;
}

// void Assembly::REG_DUMP(StackPointer *stackpointer_name)
// {
//     cout << "   ptr_value: " << stackpointer_name->pointer << endl;
// }

void Assembly::PRINT_NL()
{
    cout << endl;
}