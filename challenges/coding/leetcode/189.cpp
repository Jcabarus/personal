// Rotate Array, solved
#include <iostream>
#include <vector>

using namespace std;

void rotate(vector<int>& nums, int num_rotate) 
{
    vector<int> temp; // Buffer vector

    num_rotate = num_rotate % nums.size();

    for(int i = 0; i < num_rotate; i++) // Copies the numbers that are desired to be kept
    {
        temp.push_back(nums[((nums.size()) - (num_rotate)) + i]);
    }
    
    for(int i = 0; i < nums.size() - num_rotate; i++) // Copies the remaining numbers 
    {
        temp.push_back(nums[i]);
    }
    
    nums = temp;
}

// void rotate(vector<int>& nums, int num_rotate) 
// {
//     num_rotate = num_rotate % nums.size();
    
//     while(num_rotate != 0)
//     {
//         for(int i = 0; i < nums.size(); i++)
//         {
//             int temp = nums[i];
//             nums[i] = nums[nums.size() - 1];
//             nums[nums.size() - 1] = temp;
//         }

//         num_rotate--;
//     }
// }
    
// void rotate(vector<int>& nums, int num_rotate) 
// {
//     if(num_rotate == 0)
//     {
//         return;
//     }
//     else
//     {
//         int buffer = nums.back();

//         for(int i = nums.size() - 1; i > 0; i--)
//         {
//             nums[i] = nums[i - 1];
//         }

//         nums[0] = buffer;

//         rotate(nums, num_rotate - 1);
//     }
// }