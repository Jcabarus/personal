// Remove Duplicate from Sorted Array, solved

#include <iostream>
#include <vector>

using namespace std;

int removeDuplicates(vector<int> &nums) 
{
    for(int i = 0; i < nums.size() - 1; i++) // Vector traversal
    {
        if(nums[i] == nums[i + 1]) // Scope
        {
            nums.erase(nums.begin() + (i + 1));
            i--;
        }
    }

    return nums.size();
}