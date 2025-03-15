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