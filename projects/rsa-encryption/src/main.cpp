#include "rsa.h"

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        //Input

        // Calculation
        
        // Output
        cout << "argc == 1" << endl;
        
        return 0;
    }
    else if(argc == 2)
    {
        RSA rsa;
        // rsa.Initialize();
        // rsa.Print();

        
        return 0;
    }
    else
    {
        cout << "Error: too many argument" << endl;
        return 0;
    }
}