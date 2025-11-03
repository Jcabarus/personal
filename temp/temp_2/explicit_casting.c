#include <stdio.h>

void explicit_type_casting();

int main()
{

    explicit_type_casting();
    return 0;
}

void explicit_type_casting()
{
    int x_int = 10;
    float y_float = 40.57;

    // Narrowing
    x_int = (int)y_float;
    printf("%d\n", x_int);

    return;
}

