#include <stdio.h>

void same_type();
void type_compatible_casted();
void void_ptr();

int main()
{
    // same_type();
    // type_compatible_casted();
    void_ptr();
    return 0;
}

void same_type()
{
    int var_a = 10;
    int var_b = 20;

    int* int_ptr_a = NULL;
    int* int_ptr_b = NULL;

    int_ptr_a = &var_a; // ptr_a now holds the memory address of var_a
    int_ptr_b = int_ptr_a; // ptr_b now holds the same memory address of ptr_a
    
    printf("ptr_a: %p\n", int_ptr_a);
    printf("     : %d\n", *int_ptr_a);

    printf("ptr_b: %p\n", int_ptr_b);
    printf("     : %d\n", *int_ptr_a);
}

void type_compatible_casted()
{
    char var_a = 'C';
    int var_b = 67;
    
    char* char_ptr_a = NULL;
    int* int_ptr_b = NULL;
    
    char_ptr_a = &var_a; // ptr_a now holds the memory address of var
    int_ptr_b = (int*) char_ptr_a; // ptr_b now holds the same memory address of ptr_a casted
    

    printf("ptr_a: %p\n", char_ptr_a);
    printf("     : %c\n", *char_ptr_a);

    printf("ptr_b: %p\n", int_ptr_b);
    printf("     : %c\n", *int_ptr_b);
}

void void_ptr()
{
    int var_a = 67;
    void* void_ptr = NULL;

    void_ptr = &var_a; // void_ptr holds the memory address of var_a

    printf("void_ptr: %p\n", void_ptr);
    printf("        : %d\n", *(int*)void_ptr); 
    printf("        : %c\n", *(char*)void_ptr);
}


