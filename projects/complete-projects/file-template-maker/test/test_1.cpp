#include <iostream>
#include <cstdlib>

int main()
{
    char* path = getenv("HOME"); // getenv function is from a C-library and fetches the 

    std::cout << path << std::endl;
}