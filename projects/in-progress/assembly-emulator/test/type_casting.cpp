#include <iostream>

struct TypeCast
{
    int number;
};

int main()
{
    // Casting an unknown data type to a known data type
    // void* unknown_data_type;
    
    // int* number = reinterpret_cast<int*>(unknown_data_type);
    // *number = 100;
    
    // Casting an unknown data type to a known struct
    void* unknown_data_type;
    TypeCast* known_struct = reinterpret_cast<TypeCast*>(unknown_data_type);
    


    return 0;
}