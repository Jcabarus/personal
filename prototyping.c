#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define global_num 100000000

void setrand();
void charint();
void times();

int main()
{
    //setrand();
    //charint();
    times();
}

void setrand()
{
    int x = 101;
    int y = 50;
    
    srand(x);

   

    for(int i = 0; i < 10; i++)
    {
        for(int ii = 0; ii < 10; ii++)
        {
            printf("%d ", rand() % 10);
        }
        printf("\n");
    }
}

void charint()
{
    char a = 'a';
    int c = a;

    printf("%d\n", c);
}

void times()
{
    int initial = 100;
    int seed = time(NULL) * initial;
    srand(seed);
    int output = initial * rand() % global_num;

    scanf("%d", &initial);

    printf("Input: %d\n", initial);
    printf("Encrypted Output: %d\n", output);
    printf("Decrypted Output: %d\n", initial - (output / rand() % global_num));
}