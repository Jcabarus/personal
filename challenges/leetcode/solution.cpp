#include "27.cpp"

int main()
{
    Solution solution;

    vector<int> array_one;
    
    int remove_value = 2, array[] = {0, 1, 2, 2, 3, 0, 4, 2};

    for(int i = 0; i < 8; i++)
    {
        array_one.push_back(array[i]);
    }

    cout << "remove_value: " << remove_value << endl;
    cout << "array_one size: " << array_one.size() << endl;

    for(int i = 0; i < 8; i++)
    {
        cout << array_one[i] << " ";
    }
    
    cout << endl;
    
    int size_k = solution.removeElement(array_one, remove_value);

    for(int i = 0; i < array_one.size(); i++)
    {
        cout << array_one[i] << " ";
    }

    cout << endl;

    cout << "size_k: " << size_k << endl;
}