#include "169.cpp"

void Test(int test_case);
void Run(int test[], int size);

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "No test case selected" << endl;
    }
    else
    {
        int test_case = *argv[1] - '0';
        Test(test_case);
    }

    return 0;
}

void Test(int test_case)
{
    int test1[] = {3, 2, 3};
    int test2[] = {2, 2, 1, 1, 1, 2, 2};
    int test3[] = {4, 4, 3, 7, 6, 5, 4, 8, 2, 6, 7, 8, 5, 8, 3, 7, 9, 1, 0, 3, 6};
    int test4[] = {0, 1};
    int test5[] = {0, 0, 0};
    
    switch(test_case)
    {
        case(1): Run(test1, 3); break;
        case(2): Run(test2, 7); break;
        case(3): Run(test3, 21); break;
        // case(4): Run(test4, 2); break;
        // case(5): Run(test5, 3); break;
        default: return;
    }
}

void Run(int test[], int size)
{
    Solution solution;

    vector<int> test_array;

    for(int i = 0; i < size; i++)
    {
        test_array.push_back(test[i]);
    }
    
    for(int i = 0; i < test_array.size(); i++)
    {
        cout << test_array[i] << " ";
    }
    
    cout << endl;

    solution.majorityElement(test_array);
    
    // for(int i = 0; i < test_array.size(); i++)
    // {
    //     cout << test_array[i] << " ";
    // }
    
    // cout << endl;
}