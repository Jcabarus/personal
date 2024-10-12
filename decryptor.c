#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define global_size 100
#define global_num 1000000

int main(void)
{
    int int_encrypt_user_input;
    int int_user_snapshot;

    printf("Limitation: 100 Character Limit\n");
    printf("Provide input to decrypt message:\n");
   //printf("Add 'x' at the end of encrypted message to start decryption\n");

    scanf("%d", &int_encrypt_user_input);
    scanf("%d", &int_user_snapshot);

    srand(int_user_snapshot / int_encrypt_user_input);
    int int_decrypt_input = (int_encrypt_user_input / rand()) % global_num;

    printf("%d\n", int_decrypt_input);

    return 0;
}

int decrypt(int int_user_input, int int_user_snapshot)
{
    srand(int_user_snapshot * int_user_input);
    int int_decrypt_input = (int_user_input / rand());

    return int_decrypt_input;
}