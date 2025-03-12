#include <iostream>
#include <string>

using namespace std;

enum Type
{
    movt, subt, addt
};

class Assembly
{
    public:
        struct Lable
        {
            string lable_name;
            int int_value;
            string str_value;
        };

        struct Register
        {
            string register_name;
            int int_value;
            string str_value;
        };

        struct StackPointer
        {
            string stack_pointer_name;
            void* pointer;
        };
        
        Assembly(); // Constructor
        void mov(string arg_left, string arg_right);
        void add(string arg_left, string arg_right);
        void sub(string arg_left, string arg_right);
        // void mul();
        // void imul();
        // void div();
        // void idiv();
        // void idiv();
        // void push();
        // void pop();
        void call(string arg_left);

        
        private:
            void MOV(Register *register_name, string arg_left, string arg_right);
            void ADD(Register *register_name, string arg_left, string arg_right);
            void SUB(Register *register_name, string arg_left, string arg_right);
            void CALL(Register *register_name, string arg_left);

            void PRINT_INT(Register *register_name);
            void PRINT_STRING(Register *register_name);
            void PRINT_NL();
            void REG_DUMP();

            void error_handling(Type error_type);
};