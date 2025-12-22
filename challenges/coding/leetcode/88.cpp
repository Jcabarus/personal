// Merge Sorted Array, solved

#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) 
{
    int i = m, j = 0, sum_size = m + n;

    while(i < sum_size) // Merge nums1, nums2
    {
        nums1[i++] = nums2[j++];
    }

    for(i = 0; i < sum_size - 1; i++) // Bubble Sort
    {
        for(j = 0; j < sum_size - i - 1; j++)
        {
            if(nums1[j] > nums1[j + 1])
            {
                int temp = nums1[j];
                nums1[j] = nums1[j + 1];
                nums1[j + 1] = temp;
            }
        }
    }
}