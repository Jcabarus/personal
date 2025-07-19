// Jump Game

#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
    public:
        bool canJump(vector<int>& nums) 
        {
            int destination = nums.size() - 1;

            int starting_index = nums[0], temp_index = 0;

            if(nums.size() <= 1)
            {
                return true;
            }
            else
            {
                for(int i = 0; i < nums.size() - 1; i++)
                {
                    if(nums[i] + i >= nums[nums.size() - 1])
                    {
                        return true;
                    }
                }
            }

            return false;
        }
};