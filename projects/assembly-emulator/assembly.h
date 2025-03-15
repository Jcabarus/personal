#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

enum Type
{
    eax, ebx, ecx, edx, esp, ebp, emov, emovsx, adde, sube, calle, einc, edec
};

class Assembly
{
    public:
        Assembly(); // Constructor
        void mov(string arg_left, string arg_right);
        void movsx(string arg_left, string arg_right);
        // void movzx(string arg_left, string arg_right);
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

        // struct Stack
        // {
        //     vector<void>* stack;
        //     int stack_size;
        // };

        ERegister* InitializeERegister(ERegister *register_lable);
        ARegister* InitializeARegister(ARegister *register_lable);
        LRegister* InitializeLRegister(LRegister *register_lable);
        // Stack* InitializeStack(vector<Stack> *stack);

        void MOV(ERegister *register_name, string arg_right);
        void MOV(ARegister *register_name, string arg_right);
        void MOV(LRegister *register_name, string arg_right);

        // void MOVZX(ERegister *register_name, string arg_right); // Unsigned
        // void MOVZX(ARegister *register_name, string arg_right);
        // void MOVZX(LRegister *register_name, string arg_right);

        void MOVSX(ERegister *register_to, string arg_right); // Signed
        void MOVSX(ARegister *register_to, string arg_right); // Signed

        void ADD(ERegister *register_name, string arg_right);
        void ADD(ARegister *register_name, string arg_right);
        void ADD(LRegister *register_name, string arg_right);
        
        void SUB(ERegister *register_name, string arg_right);
        void SUB(ARegister *register_name, string arg_right);
        void SUB(LRegister *register_name, string arg_right);

        void INC(ERegister *register_name);
        void DEC(ERegister *register_name);
        
        void CALL(ERegister *register_name, string arg_left);

        void PUSH(void* stack, string arg_right);
        void POP();
        void RET();

        void PRINT_INT(ERegister *register_name);
        void PRINT_STRING(ERegister *register_name);

        void REG_DUMP(ERegister *register_name);
        void REG_DUMP(ARegister *register_name);
        void REG_DUMP(LRegister *register_name);

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

        // void* stack[100];
        // vector<void>* stack;
        
        ARegister* eip;
        ARegister* esp;
        ARegister* ebp;
};