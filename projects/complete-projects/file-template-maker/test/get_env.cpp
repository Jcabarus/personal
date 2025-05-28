#include <iostream>
#include <cstdlib>

int main()
{
    char* path = getenv("HOME"); // getenv() is from the C-libary outputs the environment whether is a PATH or in this case it's HOME
                                 // For use, you must declare your variable as a char* array. Either you can inialize it here like this
                                 // or declare it first and initialize it somewhere in your code.  

    std::cout << path << std::endl;
}