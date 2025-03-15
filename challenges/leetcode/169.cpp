// Majority Element

#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
    public:
        int majorityElement(vector<int>& nums) 
        {
            
            if(nums.size() > 0)
            {
                int counter = 0, erase_value = nums[0];

                for(int i = i; i < nums.size(); i++) // Linear search and erase
                {
                    if(erase_value == nums[i])
                    {
                        counter++;
                        nums.erase(nums.begin() + i);
                        i--;
                    }
                }
            }
            else
            {

                return nums.size();
            }
        }
};