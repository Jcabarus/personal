// Jump Game

#include <iostream>
#include <vector>

using namespace std;

bool canJump(vector<int>& nums) 
{
    // {3, 0, 8, 2, 0, 0, 1}
    // {3, 2, 1, 0, 4}
    //  {3, 0, 8, 2, 0, 0, 1, 4, 3, 0, 2, 1, 0, 3, 0, 0, 0, 2}

    vector<int*> unjumped_indices;
    vector<int*> jumped_indices;
    int* jump_end_goal = nullptr;
    int* current_evaluate_jump_ptr = nullptr;
    int* previous_evaluate_jump_ptr = nullptr;
    int* jump_ahead_ptr = nullptr;
    int* evaluated_jump_ptr = nullptr;


    jump_end_goal = &nums[nums.size() - 1];
    current_evaluate_jump_ptr = &nums[0];
    unjumped_indices.push_back(current_evaluate_jump_ptr);
    jump_ahead_ptr = unjumped_indices[unjumped_indices.size() - 1];

    while(current_evaluate_jump_ptr != jump_end_goal)
    // for(int i = 0; i < 8; i++)
    {
        // cout << " current_evaluate_jump_ptr: " << *current_evaluate_jump_ptr << endl; // Debug, remove later
        
        if(*jump_ahead_ptr == 0)
        {
            // cout << "   | --> unjumped_ahead: " << *jump_ahead_ptr << endl; // Debug, remove later
            unjumped_indices.pop_back();
            current_evaluate_jump_ptr = &(*unjumped_indices.back());
            evaluated_jump_ptr = &(*unjumped_indices.back());
            jump_ahead_ptr = &(*unjumped_indices.back());


            // cout << "            jump_ahead_ptr: " << *jump_ahead_ptr << endl; // Debug, remove later
        }
        else if(previous_evaluate_jump_ptr != nullptr && jump_ahead_ptr == previous_evaluate_jump_ptr)
        {
            // cout << "   | --> unjumped_ahead: " << *jump_ahead_ptr << endl; // Debug, remove later
            unjumped_indices.pop_back();
            current_evaluate_jump_ptr = unjumped_indices.back();
            previous_evaluate_jump_ptr = nullptr;

            jump_ahead_ptr = &(*unjumped_indices.back());
            // cout << "            jump_ahead_ptr: " << *jump_ahead_ptr << endl; // Debug, remove later
        }
        else
        {
            for(int i = 0; i < *current_evaluate_jump_ptr && jump_ahead_ptr != jump_end_goal; i++)
            {
                unjumped_indices.push_back(++jump_ahead_ptr);        
                // cout << "   | <-- jumped_ahead: " << *jump_ahead_ptr << endl; // Debug, remove later
            }
            
            previous_evaluate_jump_ptr = &(*current_evaluate_jump_ptr);
            // cout << "previous_evaluate_jump_ptr: " << *previous_evaluate_jump_ptr << endl; // Debug, remove later
            
            current_evaluate_jump_ptr = &(*jump_ahead_ptr);
            
            jump_ahead_ptr = &(*unjumped_indices.back());
            // cout << "            jump_ahead_ptr: " << *jump_ahead_ptr << endl; // Debug, remove later
        }

        cout << endl;
    }
    
    return true;
}

void cases(vector<int> &num)
{
    if(canJump(num))
    {
        cout << "Can jump!" << endl;
    }
    else
    {
        cout << "Not possible" << endl;
    }
}

int main()
{
    vector<int> nums_1 = {2, 3, 1, 1, 4}; // true
    vector<int> nums_2 = {3, 2, 1, 0, 4}; // false
    vector<int> nums_3 = {3, 0, 8, 2, 0, 0, 1}; // 
    vector<int> final = {3, 0, 8, 2, 0, 0, 1, 4, 3, 0, 2, 1, 0, 3, 0, 0, 0, 2}; // 

    cases(nums_3);

    return 0;
}