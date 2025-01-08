/*
    Instruction: Write a function that takes a string as input and returns the string in reverse order.
    Status: Solved
    Solution: Code below
*/

#include <stdio.h>

void ReseverseString(char string[]);

int main()
{
    char string[20];

    fgets(string, 20, stdin);
    ReseverseString(string);

    return 0;
}

void ReseverseString(char string[])
{
    for(int i = 19; i >= 0; i--)
    {
        printf("%c", string[i]);
    }
}