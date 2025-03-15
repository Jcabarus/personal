#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

enum Type
{
    eax, ebx, ecx, edx, esp, ebp, emov, adde, sube, calle, einc, edec
};

class Assembly
{
    public:
        Assembly(); // Constructor
        void mov(string arg_left, string arg_right);
        void add(string arg_left, string arg_right);
        void sub(string arg_left, string arg_right);
        void inc(string arg_left);
        void dec(string arg_left);
        void call(string arg_left);
        void push();
        void pop();
        void ret();
        void error_handling(Type error_type);
        void end_program();
        
    private:
        struct Lable
        {
            string lable_name;

            int int_value;
            string str_value;
        };

        struct ERegister
        {
            int int_value;
            string str_value;
        };

        struct ARegister
        {
            short int int_value;
        };

        struct LRegister
        {
            int8_t int_value;
        };

        ERegister* InitializeERegister(ERegister *register_lable);
        ARegister* InitializeARegister(ARegister *register_lable);
        LRegister* InitializeLRegister(LRegister *register_lable);
        // StackPointer* InitializeStackPointer(StackPointer *stackpointer_lable);

        void MOV(ERegister *register_name, string arg_right);
        void MOV(ARegister *register_name, string arg_right);
        void MOV(LRegister *register_name, string arg_right);

        void ADD(ERegister *register_name, string arg_right);
        void ADD(ARegister *register_name, string arg_right);
        void ADD(LRegister *register_name, string arg_right);
        
        void SUB(ERegister *register_name, string arg_right);
        void SUB(ARegister *register_name, string arg_right);
        void SUB(LRegister *register_name, string arg_right);

        void INC(ERegister *register_name);
        void DEC(ERegister *register_name);
        
        void CALL(ERegister *register_name, string arg_left);

        void PUSH();
        void POP();
        void RET();

        void PRINT_INT(ERegister *register_name);
        void PRINT_STRING(ERegister *register_name);
        void REG_DUMP(ERegister *register_name);
        // void REG_DUMP(StackPointer *stackpointer_name);
        void PRINT_NL();

        ERegister* eax;
        ARegister* ax;
        LRegister* al;
        LRegister* ah;
        
        ERegister* ebx;
        ARegister* bx;
        LRegister* bl;
        LRegister* bh;
        
        ERegister* ecx;
        ARegister* cx;
        LRegister* cl;
        LRegister* ch;
        
        ERegister* edx;
        ARegister* dx;
        LRegister* dl;
        LRegister* dh;

        vector<void>* stack;

        // StackPointer* eip;
        // StackPointer* esp;
        // StackPointer* ebp;
};