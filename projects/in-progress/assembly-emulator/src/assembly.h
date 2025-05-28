#include <iostream>

using namespace std;

class CPU
{
    public:
        struct Register
        {
            bool reg_data[32]; // true = 1, false = 0
            bool reg_address[32];
        };

        struct Instruction
        {
            bool reg_address[32];
        }; 

        CPU();

        void mov(void* arg_a, void* arg_b);
        void movsx(void* arg_a, void* arg_b);
        void movzx(void* arg_a, void* arg_b);

        void add(void* arg_a, void* arg_b);
        void sub(void* arg_a, void* arg_b);
        void mul(void* arg_a, void* arg_b);
        void imul(void* arg_a, void* arg_b);
        void div(void* arg_a, void* arg_b);
        void idiv(void* arg_a, void* arg_b);

        void inc(void* arg_a, void* arg_b);
        void dec(void* arg_a, void* arg_b);

        // void cmp(void* arg_a);

        // void jmp();
        // void je();
        // void jne();
        // void jg();
        // void jge();
        // void jl();
        // void jle();
        // void jz();
        // void jnz();

        // void call();

        void e(Register* reg); // 32-bit
        void x(Register* reg); // 16-bit
        void l(Register* reg); // 8-bit lower
        void h(Register* reg); // 8-bit higher

        Register* a;
        Register* b;
        Register* c;
        Register* d;

        Instruction* eip;
        Instruction* esp;
        Instruction* ebp;
    
    private:
        void PARSE();
};

class Stack
{
    public:
        struct SNode
        {
            bool stack_address[32];
            SNode* snode_link;
        };

        Stack();

        void push();
        void enter();
        void pop();
        void pusha();
        void ret();
        void leave();
};

class Decoder
{
    Decoder();

    void hexadecimal(bool arr[32]);
    void ascii(bool arr[32]);
    void octal(bool arr[32]);
    void binary(bool arr[32]);
};