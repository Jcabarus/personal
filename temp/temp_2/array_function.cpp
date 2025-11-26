#include <stdio.h>

void array_behavior_demo(void* array, short type)
{
    if(type == 1)
    {
        int* ptr = (int*)array;

        for(int i = 0; i < 10; i++)
        {
            printf("%d ", (int)ptr[i]);
        }

        printf("\n");
    }
    else if(type == 2)
    {
        char* ptr = (char*)array;

        for(int i = 0; i < 10; i++)
        {
            printf("%c ", (char)ptr[i]);
        }
    
        printf("\n");
    }
    else if(type == 3)
    {
        float* ptr = (float*)array;

        for(int i = 0; i < 10; i++)
        {
            printf("%f ", (float)ptr[i]);
        }
    
        printf("\n");
    }
}

int main()
{
    int array_int[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    char array_char[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    float array_float[10] = {1.0, 2.10, 3.21, 4.32, 5.43, 6.54, 7.65, 8.76, 9.87, 10.98};

    array_behavior_demo(array_int, 1);
    array_behavior_demo(array_char, 2);
    array_behavior_demo(array_float, 3);

    return 0;
}