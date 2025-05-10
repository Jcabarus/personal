#include <iostream>
#include <vector>

using namespace std;

class Calculator
{
    public:
        Calculator();
        void Menu();
        void Input();
        void Result();

    private:
        void PARSE();
        void CLEARSCREEN();

        string input;
        vector<string> expression;
};