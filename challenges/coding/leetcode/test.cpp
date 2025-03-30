#include "1672.cpp"

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
    int test1[] = {1, 2, 3, 4};
    int test2[] = {1, 1, 1, 1, 1}; 
    int test3[] = {3, 1, 2, 10, 1}; 
    int test4[] = {1, 2}; 
    int test5[] = {3, 2, 6, 5, 0, 3}; 
    int test6[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 34}; 
    int test7[] = {34, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; 
    int test8[] = {2, 4, 1};
    
    switch(test_case)
    {
        case(1): Run(test1, 4); break;
        case(2): Run(test2, 5); break;
        case(3): Run(test3, 5); break;
        // case(4): Run(test4, 2); break;
        // case(5): Run(test5, 6); break;
        // case(6): Run(test6, 21); break;
        // case(7): Run(test7, 21); break;
        // case(8): Run(test8, 3); break;
        default: cout << "Invalid test case" << endl; return;
    }
}

void Run(int test[], int size)
{
    Solution solution;

    vector<vector<int>> test_array;

    for(int i = 0; i < size; i++)
    {
        // test_array.push_back(test[][i]);
    }
    
    cout << solution.maximumWealth(test_array) << endl;;

    cout << endl;
}