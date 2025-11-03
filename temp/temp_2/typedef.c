#include <stdio.h>

#define size 10

typedef int integer; // You can create an alias of an existing or any primitive data type
typedef int array[10]; // You can alias array 

typedef int integers;

typedef struct // Most usecase of typedef to eliminate the use of 'struct' when it's used
{
    char a, b, c;
} user_defined_struct;

int main()
{
    array array_a;
    integer int_a;
    user_defined_struct struct_a;
    
    
    for(int i = 0; i < size; i++)
    {
        array_a[i] = i;
    }
    
    int_a = 10;

    struct_a.a = 'a';
    struct_a.b = 'b';
    struct_a.c = 'c';

    printf("Array:");
    for(int j = 0; j < size; j++)
    {
        printf("%d ", array_a[j]);
    }
    printf("\n");

    printf("Integer: %d\n", int_a);

    printf("Struct: %c %c %c\n", struct_a.a, struct_a.b, struct_a.c);

    return 0;
}