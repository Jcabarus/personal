/*
    Instruction: Write a function that generates the Fibonacci sequence up to the nth term.
    Status: Solved
    Solution: Code below
*/    

#include <iostream>

int Fibonacci(int sequence);

int main()
{
    int n;


    std::cin >> n;
    std::cout << Fibonacci(n) << "\n";

    return 0;
}

int Fibonacci(int sequence)
{
    if(sequence == 1)
    {
        return 0;
    }
    else if(sequence == 2)
    {
        return 1;
    }
    else
    {
        return Fibonacci(sequence - 1) + Fibonacci(sequence - 2);
    }
}