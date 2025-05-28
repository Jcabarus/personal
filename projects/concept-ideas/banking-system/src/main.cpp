#include "header.h"

void Interface();

int main()
{
    Interface();
    return 0;
}

void Interface()
{
    short user_input;

    cout << "[Menu]" << endl;
    cout << "1. Sign In" << endl;
    cout << "2. Sign Up" << endl;
    cout << "0. Exit" << endl << endl;

    cout << ": ";
    cin >> user_input;

    switch(user_input)
    {
        case(1):
        {
            cout << "[Menu/sign-in]" << endl;
            
            SignIn signin;
            
            break;
        }
        case(2): 
        {
            cout << "[Menu/sign-up]" << endl;

            SignUp signup;

            break;
        }
        case(0): return;
        default: cout << endl; Interface();
    }
}