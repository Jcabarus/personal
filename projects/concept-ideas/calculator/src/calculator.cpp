#include "header.h"

using namespace std;

void Menu(string &string_input, vector<Token*> &tokenized_expression_vector);
void Input(string &input);
void SyntaxCheck();
void Lexer(string &string_input, vector<Token*> &tokenized_expression_vector);
void Parser(vector<Token*> &tokenized_expression_vector);
void Result(Pratt &pratt_parsing, vector<Token*> &tokenized_expression_vector);

int main()
{
    string input; // User's input
    vector<Token*> tokenized_expression;

    Menu(input, tokenized_expression); 

    return 0;
}

void Menu(string &string_input,vector<Token*> &tokenized_expression_vector)
{
    cout << "=======[ Pratt Parsing Concept ]=======" << endl;
    cout << "[1] [2] [3] [4] [5] [6] [7] [8] [9] [0]" << endl;
    cout << "            [+] [-] [*] [/]" << endl;
    cout << endl;
    
    do
    {
        Input(string_input);

        if(string_input != "x")
        {
            Lexer(string_input, tokenized_expression_vector);
            Parser(tokenized_expression_vector);
            tokenized_expression_vector.clear();
        }
    }
    while(string_input != "x");
    return;
}

void Input(string &string_input)
{
    cout << "      : ";
    getline(cin, string_input);
}

void Lexer(string &string_input, vector<Token*> &tokenized_expression_vector) // C`ssifies the operators and operands in their respective token classification
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

    return;
}

void Parser(vector<Token*> &tokenized_expression_vector)
{
    Pratt parsing(tokenized_expression_vector);
    Result(parsing, tokenized_expression_vector);

    return;
}

void Result(Pratt &pratt_parsing, vector<Token*> &tokenized_expression_vector)
{
    cout << "Result: " << pratt_parsing.Result() << endl;

    for(int i = 0; i < tokenized_expression_vector.size(); i++)
    {
        delete tokenized_expression_vector[i];
    }
    
    return;
}