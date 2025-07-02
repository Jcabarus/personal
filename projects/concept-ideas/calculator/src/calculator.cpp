#include "header.h"

using namespace std;

void Menu(string &string_input);
void Input(string &input);
void Lexer(string &string_input, Token &token);
void Parser(Token &token);
void Result(Pratt &pratt_parsing);

int main()
{
    string input; // User's input
    Menu(input); 
}

void Menu(string &string_input)
{
    Token token; // For operator and operands classification

    cout << "[+] [-] [*] [/]" << endl;
    cout << endl;
    
    Input(string_input);
    Lexer(string_input, token);
    Parser(token);
}

void Input(string &string_input)
{
    cout << "      : ";
    getline(cin, string_input);
}

void Lexer(string &string_input, Token &token)
{
    for(int i = 0; i < string_input.size(); i++) // Classifies the operators and operands in their respective token classification
    {
        if(string_input[i] != ' ' && string_input[i] != '\n')
        {
            if(string_input[i] != '+' && string_input[i] != '-' && string_input[i] != '*' && string_input[i] != '/')
            {
                token.operands.push_back(string_input[i]);
            }
            else
            {
                token.operators.push_back(string_input[i]);
            }
        }
    }
}

void Parser(Token &token)
{
    // Pratt parsing(token);
}

void Result(Pratt &pratt_parsing)
{
    // cout << "Result: " << pratt_parsing.Result() << endl;
}