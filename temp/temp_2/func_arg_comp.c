#include <stdio.h>

int add_operation(int a, int b)
{
    return a + b;
}

int sub_operation(int a, int b)
{
    return a + b;
}

float div_operation(float a, float b)
{
    return a / b;
}

int main()
{   
    int a, b;

    a = 1, b = 2;
    printf("Addition: %d\n", add_operation(a, b));
    
    a = 7, b = 3;
    printf("Subtraction: %d\n", sub_operation(a, b));
    
    a = 10, b = 5;
    printf("Division: %f\n", div_operation(a, b)); // Will raise a compiler warning due to the data type mismatch
    
    a = 15, b = 5;
    printf("Division: %f\n", div_operation((float)a, (float)b)); 
    
    a = 15, b = 5;
    printf("Division: %f\n", div_operation((float)a));  // Will cause a compiler error due to function parameter having too few arguements


    return 0;
}