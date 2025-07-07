#include "header.h"

using namespace std;

void Menu(string &string_input, vector<Token*> &tokenized_expression_vector);
void Input(string &input);
void Lexer(string &string_input, vector<Token*> &tokenized_expression_vector);
void Parser(vector<Token*> &tokenized_expression_vector);
void Result(Pratt &pratt_parsing);

int main()
{
    vector<Token*> tokenized_expression;

    string input; // User's input
    Menu(input, tokenized_expression); 
}

void Menu(string &string_input,vector<Token*> &tokenized_expression_vector)
{
    // cout << "[+] [-] [*] [/]" << endl;
    // cout << endl;

    Input(string_input);
    Lexer(string_input, tokenized_expression_vector);
    Parser(tokenized_expression_vector);
}

void Input(string &string_input)
{
    // cout << "      : ";
    // getline(cin, string_input);
    
    string_input = "1 * 3 + 2 - 1 / 4 * 5 - 2"; // Debugging purposes, delete later
}

void Lexer(string &string_input, vector<Token*> &tokenized_expression_vector) // Classifies the operators and operands in their respective token classification
{
    for(int i = 0; i < string_input.size(); i++)
    {
        if(string_input[i] != ' ' && string_input[i] != '\n')
        {
            Token *initialize_token = new Token;

            initialize_token->token_attribute = "N/A"; // Initialized default value
            initialize_token->token_identificator = "N/A"; // Initialized default value

            if(string_input[i] == '+' || string_input[i] == '-' || string_input[i] == '*' || string_input[i] == '/')
            {
                initialize_token->token_identificator = string_input[i];
                initialize_token->token_attribute = "operator";
                tokenized_expression_vector.push_back(initialize_token);
            }
            else
            {
                initialize_token->token_identificator = string_input[i];
                initialize_token->token_attribute = "operand";
                tokenized_expression_vector.push_back(initialize_token);
            }
        }
    }
}

void Parser(vector<Token*> &tokenized_expression_vector)
{
    Pratt parsing(tokenized_expression_vector);

    // Result(parsing);
}

void Result(Pratt &pratt_parsing)
{
    // cout << "Result: " << pratt_parsing.Result() << endl;
}