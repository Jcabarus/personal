#include "rsa.h"

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        //Input

        // Calculation
        RSA rsa;
        rsa.Initialize();
        
        // Output
        rsa.Print();

        return 0;
    }
    else if(argc == 2)
    {

    }
    else
    {
        printf("Error: too many argument\n");
        return 0;
    }
}