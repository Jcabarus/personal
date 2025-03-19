#include "121.cpp"

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
    int test1[] = {1, 3, 4, 5, 2, 9, 8}; // 1, 9, 8
    int test2[] = {2, 4, 5, 1, 6, 8, 9}; // 1, 9, 8
    int test3[] = {7, 2, 5, 3, 1, 4}; // 1, 4, 3
    int test4[] = {1, 2}; // 1, 1, 0
    int test5[] = {3, 2, 6, 5, 0, 3}; // 2, 6, 4
    int test6[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 34}; // 1, 34, 33
    int test7[] = {34, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // 34, 34, 0
    int test8[] = {2, 4, 1}; // 2, 4, 2
    
    switch(test_case)
    {
        case(1): Run(test1, 7); break;
        case(2): Run(test2, 7); break;
        case(3): Run(test3, 6); break;
        case(4): Run(test4, 2); break;
        case(5): Run(test5, 6); break;
        case(6): Run(test6, 21); break;
        case(7): Run(test7, 21); break;
        case(8): Run(test8, 3); break;
        default: cout << "Invalid test case" << endl; return;
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
    
    cout << solution.maxProfit(test_array) << endl;
}