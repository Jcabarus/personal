/*
    Instruction: Write a function that takes a string as input and returns the string in reverse order.
    Status: Solved
    Solution: Code below
*/

#include <stdio.h>
#include <string.h>

void ReseverseString(char string[], int length);

int main()
{
    char string[20];

    scanf("%s", string);
    int length = strlen(string);
    ReseverseString(string, length);

    return 0;
}

void ReseverseString(char string[], int length)
{
    for(int i = length; i >= 0; i--)
    {
        printf("%c", string[i]);
    }
}
