#include <stdio.h>

void narrowing_explicit();
void narrowing_explicit();
void widening_implicit();
void widening_explicit();

int main()
{
    // narrowing_implicit();
    // narrowing_explicit();
    // widening_implicit();
    widening_explicit();
    return 0;
}

void narrowing_implicit()
{
    int x_int = 5;
    int y_int = 10;

    float x_float = 15.5;
    float y_float = 20.5;

    // Implicit, 
    x_int = x_int + x_float;
    printf("%d\n", x_int);
    
    return;
}

void narrowing_explicit()
{
    int x_int = 5;
    int y_int = 10;

    float x_float = 15.5;
    float y_float = 20.5;

    // Explicit
    y_int = y_int + (int) y_float;
    printf("%d\n", y_int);
    
    return;
}

void widening_implicit()
{
    int x_int = 5;
    int y_int = 10;

    float x_float = 15.5;
    float y_float = 20.5;

    // Implicit, 
    x_float = x_float + x_int;
    printf("%f\n", x_float);
}

void widening_explicit()
{
    int x_int = 5;
    int y_int = 10;

    float x_float = 15.5;
    float y_float = 20.5;

    // Explicity, 
    y_float = y_float + (float) y_int;
    printf("%f\n", y_float);
    return;
}