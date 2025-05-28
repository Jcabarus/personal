#include "header.h"

using namespace std;

void Menu(string &input, vector<string> &parsed_expression);
void Input(string &input);
void Result(vector<string> &parsed_expression);
void Parse(string &input, vector<string> &parsed_expression);

int main()
{
    string input;
    vector<string> parsed_expression;

    Menu(input, parsed_expression);
}

void Menu(string &input, vector<string> &parsed_expression)
{
    cout << "[+] [-] [*] [/]" << endl;
    cout << endl;

    Input(input);
    Parse(input, parsed_expression);
    Result(parsed_expression);
}

void Input(string &input)
{
    cout << "      : ";
    getline(cin, input);
}

void Result(vector<string> &parsed_expression)
{
    cout << "Result: ";
    
    Pratt pratt_parsing(parsed_expression);

    cout << endl;
}

void Parse(string &input, vector<string> &parsed_expression)
{
    string parse_buffer;
    
    for(int i = 0; i < input.length(); i++) // Parses numbers and operands
    {
        if(input[i] != ' ')
        {
            parse_buffer.push_back(input[i]);
        }

        if((i == input.length() - 1 || input[i] == ' ') && !parse_buffer.empty())
        {
            parsed_expression.push_back(parse_buffer);
            parse_buffer.clear();
        }
    }
}