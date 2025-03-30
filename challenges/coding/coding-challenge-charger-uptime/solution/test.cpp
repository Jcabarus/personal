#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    int var_one, var_two[2], var_three[3];

    ifstream read_file;

    read_file.open(argv[2]);
    
    int mode = *argv[1] - '0';
    
    switch(mode)
    {
        case(1):
        {
            while(read_file >> var_one)
            {
                cout << var_one << endl;
            }

            break;
        }
        case(2):
        {
            while(read_file >> var_two[0] >> var_two[1])
            {
                cout << var_two[0] << " " << var_two[1] << endl;
            }

            break;
        }
        case(3):
        {
            while(read_file >> var_three[0] >> var_three[1] >> var_three[2])
            {
                cout << var_three[0] << " " << var_three[1] << " " << var_three[2] << endl;
            }

            break;
        }
    }

    read_file.close();

    return 0;
}