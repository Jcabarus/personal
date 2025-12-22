// 1. Two Sum, solved

#include <vector>
#include <iostream>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

vector<int> twoSum(vector<int>& nums, int target) 
{
    vector<int> two_sum;

    for(int i = 0; i < nums.size() - 1; i++)
    {
        for(int j = 1 + i; j < nums.size(); j++)
        {
            if(nums[i] + nums[j] == target)
            {
                two_sum.push_back(i);
                two_sum.push_back(j);
                return two_sum;
            }
        }
    }
    
    return two_sum;
}

int main(int argc, char* argv[])
{
    vector<int> nums = {2, 5, 5, 11};
    vector<int> targe_index;
    int target = atoi(argv[1]);

    cout << target << endl;

    targe_index = twoSum(nums, target);

    for(int i = 0; i < targe_index.size(); i++)
    {
        cout << targe_index[i] << " ";
    }

    cout << endl;

    return 0;
}