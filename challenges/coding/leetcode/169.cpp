// Majority Element, solved

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int majorityElement(vector<int>& nums) 
{
    vector<int> element_array;

    sort(nums.begin(), nums.end());

    return nums[nums.size() / 2];
}