#include "calculator.h"

Calculator::Calculator()
{
    while(true)
    {
        Menu();
        Input();
        PARSE();
        Result();
        CLEARSCREEN();
    }
}

void Calculator::Menu()
{
    cout << "[sqrt()] [mod()] [pow()]" << endl;
    cout << "[+] [-] [*] [/]" << endl;
    // CLEARSCREEN();
}

void Calculator::Input()
{
    cout << "in: ";
    getline(cin, input);
}

void Calculator::Result()
{
    cout << "ou: ";
    
    if(expression.empty())
    {
        cout << "empty";

        return;
    }

    for(int i = 0; i < expression.size(); i++)
    {
        cout << "'" << expression[i] << "'" << " ";
    }

    cout << endl;

    expression.clear();
}


void Calculator::PARSE()
{
    string buffer_input;

    for(int i = 0; i < input.length(); i++)
    {
        if(input[i] != ' ')
        {
            buffer_input.push_back(input[i]);
        }
        else
        {
            expression.push_back(buffer_input);
            buffer_input.clear();
        }
    }
}

void Calculator::CLEARSCREEN()
{
    for(int i = 0; i < 10; i++)
    {
        cout << endl;
    }
}