// Remove Element

#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
    public:
        int removeElement(vector<int> &array_one, int remove_value) 
        {
            int index_tracker = 0;
            
            for(int i = 0; i < array_one.size(); i++) // Initalize index_tracker
            {
                if(array_one[i] == remove_value)
                {
                    index_tracker++;
                }
            }
            
            int* index_array = new int[index_tracker];

            index_tracker = 0;
            
            for(int i = array_one.size() - 1; i >= 0; i--) // Storing indexes to be removed
            {
                if(array_one[i] == remove_value)
                {
                    index_array[index_tracker++] = i;
                }
            }

            for(int i = 0; i < index_tracker; i++) // Remove array_one[index_array[i]]
            {
                array_one.erase(array_one.begin() + index_array[i]);
            }

            delete[] index_array;
            return array_one.size();
        }
};