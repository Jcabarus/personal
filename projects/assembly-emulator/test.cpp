#include <iostream>

int main()
{
    int* array_ptr[5];

    short array_int[] = {1, 2, 3, 4, 5};

    for(int i = 0; i < 5; i++)
    {
        array_ptr[i] = (int*)&array_int[i];
    }

    for(int i = 0; i < 5; i++)
    {
        std::cout << array_ptr[i] << " -> " << *array_ptr[i] << "\n";
    }

    return 0;
}