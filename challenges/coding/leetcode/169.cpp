// Majority Element

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution 
{
    public:
        int majorityElement(vector<int>& nums) 
        {
            vector<int> element_array;

            sort(nums.begin(), nums.end());

            return nums[nums.size() / 2];
        }
};