#include <iostream>

using namespace std;

void IterativeApproach(int iterative_step, string string_arg);
void RecursionApproach(int recursion_step, string string_arg);

int main()
{
    IterativeApproach(4, "Hello World");
    cout << endl;
    RecursionApproach(4, "Hello World");

    return 0;
}

void IterativeApproach(int iterative_step, string string_arg)
{
    for(int i = 0; i < iterative_step; i++)
    {
        cout << string_arg << endl;
    } 
}

void RecursionApproach(int recursion_step, string string_arg)
{
    if(recursion_step > 0)
    {
        cout << string_arg << endl;
        RecursionApproach(recursion_step - 1, string_arg);
    }
    else
    {
        return;
    }
}