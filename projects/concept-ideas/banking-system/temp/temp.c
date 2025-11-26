#include <stdio.h>

int main()
{

    char str_a[] = "Hello\0";
    char str_b[] = "World\0";

    str_b = str_b + str_a;

    prinf("%s", str_b);

    return 0;
}

