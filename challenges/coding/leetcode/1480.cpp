// Running Sum Array, solved

#include <iostream>
#include <vector>

using namespace std;

vector<int> runningSum(vector<int>& array)
{
    vector<int> temp;

    for(int i = 0; i < array.size(); i++)
    {
        temp.push_back(0); // Initialization

        for(int j = 0; j <= i; j++)
        {
            temp[i] += array[j]; // Assignment
        }
    }

    return temp;
}
