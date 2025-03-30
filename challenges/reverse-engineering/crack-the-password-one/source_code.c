#include <stdio.h>
#include <string.h>

void checkCode(char input[])
{
    char secret[5] = "****"; // Replace with your secret 4-digit code

    if (strcmp(input, secret) == 0)
    {
        printf("Congratulations! You've unlocked the secret.\n");
    }
    else
    {
        printf("Wrong code! Try again.\n");
    }
}

int main()
{
    char guess[5];

    printf("Enter the 4-digit secret code: ");
    scanf("%4s", guess);

    checkCode(guess);

    return 0;
}
