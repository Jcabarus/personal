#include "header.h"

void main_menu();
void main_menu_prompt();

int main()
{
    main_menu();
    return 0;
}

void main_menu()
{
    cout << "=====[ MENU ]=====" << endl;
    cout << "[1] Sign In" << endl;
    cout << "[2] Sign Up" << endl << endl;

    main_menu_prompt();
}

void main_menu_prompt()
{
    int buffer_input;

    cout << ">: ";
    cin >> buffer_input;

    switch(buffer_input)
    {
        case(1): sign_in_menu(); break;
        case(2): sign_up_menu(); break;
        default: cout << "Invalid option" << endl; main_menu_prompt();
    }
}
