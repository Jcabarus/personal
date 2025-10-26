#include <iostream>

using std::string;
using std::cout;
using std::endl;

int main()
{

    string str_a = "Hello";
    string str_b = "World";

    str_b = str_b + str_a;

    cout << str_b << endl;

    return 0;
}

