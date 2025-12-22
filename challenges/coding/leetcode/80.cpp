// Remove Duplicate from Sorted Array II, solved

#include <iostream>
#include <vector>

using namespace std;

int removeDuplicates(vector<int>& nums) 
{
    if(nums.size() > 2)
    {
        for(int i = 0; i < nums.size() - 2; i++) // Vector traversal
        {
            if(nums[i] == nums[i + 1] && nums[i] == nums[i + 2]) // Scope
            {
                nums.erase(nums.begin() + (i + 1));
                i--;
            }
        }
    }

    return nums.size();
}