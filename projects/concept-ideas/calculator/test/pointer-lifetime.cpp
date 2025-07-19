#include <iostream>
#include <vector>

struct Pointer
{
    int num32;
};

int main()
{
    std::vector<Pointer*> vector_test;  

    for(int _ = 0; _ < 10; _++)
    {
        Pointer* pointer_lifetime_test = new Pointer;
        pointer_lifetime_test->num32 = _;
        vector_test.push_back(pointer_lifetime_test);
    }

    for(int i = 0; i < vector_test.size(); i++)
    {
        vector_test[i]->num32 = 0;
        delete vector_test[i];
    }

    return 0;
}