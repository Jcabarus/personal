// Jump Game

#include <iostream>
#include <vector>

using namespace std;

bool canJump(vector<int>& nums) 
{
    int initial_index = 0;
    int optimum_jump = nums[initial_index];

    while(initial_index != nums[nums.size() - 1])
    {
        for(int i = initial_index + 1; i <= nums[i] + 1; i++)
        {
            if(optimum_jump < nums[i])
            {
                optimum_jump = nums[i];
            }
            
            if(nums[i] == 0 && &nums[i] != &nums[nums.size() - 1])
            {
                return false;
            }
            
            initial_index = i;
        }
    }

    return true;
}

int main()
{
    vector<int> nums_1 = {2, 3, 1, 1, 4};
    vector<int> nums_2 = {2, 1, 6, 1, 0};

    if(canJump(nums_1))
    {
        cout << "Can jump!" << endl;
    }
    else
    {
        cout << "Not possible" << endl;
    }

    return 0;
}