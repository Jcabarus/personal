#include "header.h"

using namespace std;

void Menu(string &string_input, vector<Token*> &tokenized_expression_vector, float &pre_result);
void Input(string &input);
bool SyntaxChecker(string &string_input);
void Lexer(string &string_input, vector<Token*> &tokenized_expression_vector, float &pre_result);
void Parser(vector<Token*> &tokenized_expression_vector, float &prev_result);
void Result(Pratt &pratt_parsing, vector<Token*> &tokenized_expression_vector, float &prev_result);

int main()
{
    string input; // User's input
    float prev_result = 0; 

    vector<Token*> tokenized_expression;

    Menu(input, tokenized_expression, prev_result); 

    return 0;
}

void Menu(string &string_input,vector<Token*> &tokenized_expression_vector, float &prev_result)
{
    cout << "=======[ Pratt Parsing Concept ]=======" << endl;
    cout << "[1] [2] [3] [4] [5] [6] [7] [8] [9] [0]" << endl;
    cout << "   [+] [-] [*] [/] [pr = prev_result]" << endl; // Available operation
    cout << endl;
    
    do
    {
        Input(string_input);

        if(string_input != "x")
        {
            Lexer(string_input, tokenized_expression_vector, prev_result);
            Parser(tokenized_expression_vector, prev_result);
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

bool SyntaxChecker(string &string_input)
{
    return false;
}

void Lexer(string &string_input, vector<Token*> &tokenized_expression_vector, float &prev_result) // Classifies the operators and operands in their respective token classification
{
    for(int i = 0; i < string_input.size(); i++)
    {
        if(string_input[i] != ' ' && string_input[i] != '\n')
        {
            Token *initialize_token = new Token;

            initialize_token->token_attribute = "N/A"; // Initialized default value
            initialize_token->token_identity = "N/A"; // Initialized default value

            if(string_input[i] == '+' || string_input[i] == '-' || string_input[i] == '*' || string_input[i] == '/')
            {
                initialize_token->token_identity = string_input[i];
                initialize_token->token_attribute = "operator";
                tokenized_expression_vector.push_back(initialize_token);
            }
            else if(string_input[i] == 'pr' && prev_result != 0.0) // Need more progress
            {
                initialize_token->token_identity = prev_result;
                initialize_token->token_attribute = "operand";
                tokenized_expression_vector.push_back(initialize_token);
            }
            else
            {
                initialize_token->token_identity = string_input[i];
                initialize_token->token_attribute = "operand";
                tokenized_expression_vector.push_back(initialize_token);
            }
        }
    }

    return;
}

void Parser(vector<Token*> &tokenized_expression_vector, float &prev_result)
{
    Pratt parsing(tokenized_expression_vector);
    Result(parsing, tokenized_expression_vector, prev_result);

    return;
}

void Result(Pratt &pratt_parsing, vector<Token*> &tokenized_expression_vector, float &prev_result)
{
    cout << "Result: " << pratt_parsing.Result() << endl;

    prev_result = pratt_parsing.Result();

    for(int i = 0; i < tokenized_expression_vector.size(); i++)
    {
        delete tokenized_expression_vector[i];
        tokenized_expression_vector[i] = nullptr;
    }
    
    return;
}