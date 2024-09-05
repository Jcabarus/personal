/*
    User input a string
    Generate a key to decrypt said encrypted string
    Encrypt said string
    Output an encrypted string as well as key to decrypt to user.

    The end-user should be able to input the decryptor key as well the encrypted string
    Output a decrypted string to user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define global_size 100
#define global_num 1000000

int Encrypt(int int_input);

int main(void)
{
    char char_user_input[global_size];
    int int_user_input[global_size];
    int int_counter = 0;

    printf("Limitation: 100 Character Limit\n");
    printf("Provide input to encrypt your message:\n");
    fgets(char_user_input, global_size, stdin);

    //Convert user input from char to int
    for(int i = 0; char_user_input[i] != '\0'; i++)
    {
        //Filters out '\n'
        if(char_user_input[i] != '\n')
        {
            int_user_input[i] = char_user_input[i]; //char -> int
            int_counter++;
        }   
    }

    //Add KeyGen to int_user_input
    for(int i = 0; i < int_counter; i++)
    {
        int_user_input[i] = Encrypt(int_user_input[i]);
    }

    //Print out int_mod_input
    for(int i = 0; i < int_counter; i++)
    {
        printf(" %d", int_user_input[i]);
    }

    printf("\n");

    return 0;
}

int Encrypt(int int_input)
{
    //input + unix time * rand with set seed
    srand((int_input % time(NULL)) * -10);
    int int_mod_input = int_input * rand() % global_num;

    return int_mod_input;
}


