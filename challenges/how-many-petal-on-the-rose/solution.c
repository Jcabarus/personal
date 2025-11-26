#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* generate_num(int* calculate_num);
int return_sum(int* array);

int main()
{
    srand(time(NULL));

    int array[6];

    for(int i = 0; i < 6; i++)
    {
        generate_num(&array[i]);
    }
    
    for(int i = 0; i < 6; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("%d\n", return_sum(array));

    return 0;
}

int* generate_num(int* calculate_num)
{
    *calculate_num = rand() % 7;
    return calculate_num;
}

int return_sum(int* array)
{
    int sum_flag = 0;

    for(int i = 0; i < 6; i++)
    {
        if(array[i] == 3)
        {
            sum_flag += 2;        
        }
        else if(array[i] == 5)
        {
            sum_flag += 4;
        }
    }

    return sum_flag;
}