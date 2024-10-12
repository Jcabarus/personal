/*
    User input a string
    Generate a key to decrypt said encrypted string
    Encrypt said string
    Output an encrypted string as well as key to decrypt to user.

    The end-user should be able to input the decryptor key as well the encrypted string
    Output a decrypted string to user.

    Implement File Stream
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GlobalSize 100
#define GlobalSum 1000000
#define GlobalTime time(NULL)

int main()
{
    char InitialStringArray[GlobalSize];
    char ModifiedStringArray[GlobalSize];

    //User input
    fgets(InitialStringArray, GlobalSize, stdin);

    //Generate key based on input


    //Output an encrypted string along with decryption key

    return 0;
}

