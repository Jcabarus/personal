#include <stdio.h>
 
int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

float div(float a, float b)
{
    return a / b;
}

void function_callback_demo(int (*function)(int a, int b), int arg_a, int arg_b)
{
    
    printf("In function_callback_demo()\n");
    printf("    operation: %d\n\n", function(arg_a, arg_b));
}

int main()
{
    int (*operation)(int a, int b);


    printf("In main()\n");

    operation = add;
    printf("    Add: %d\n", operation(3, 2));

    operation = sub;
    printf("    Sub: %d\n\n", operation(7, 2));

    operation = add;
    function_callback_demo(operation, 5, 4);

    operation = sub;
    function_callback_demo(operation, 7, 4);

    operation = div; // Will raise a compiler warning due to the mismatch of data type
    function_callback_demo(operation, 4, 4);

    return 0;
}

