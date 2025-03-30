#include "charger-uptime-solution.h"
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "argc != 2" << endl;
        return -1;
    }
    else
    {
        ifstream read_file;

        read_file.open(argv[1]);

        if(read_file.fail())
        {
            read_file.close();
            cout << "Error: unable to " << argv[1] << endl;
            return -1;
        }
        else
        {
            unsigned int station_id, charger_id;

            read_file >> station_id;

            if(read_file >> charger_id)
            {
                read_file >> charger_id;
            }
        }
    }
}