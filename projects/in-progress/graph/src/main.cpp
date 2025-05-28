#include "header.h"

int main(int argc, char* argv[])
{
    if(argc == 2) // argc error checking
    {   
        ifstream read_test; // File error checking

        read_test.open(argv[1]);

        if(read_test.fail())
        {
            read_test.close();
            cout << "Error: argv[1]: " << argv[1] << endl;

            return -1;
        }
        else
        {
            read_test.close();
            ifstream read_file;
            read_file.open(argv[1]);

            Graph graph(read_file); // Graph initialization
            graph.Traversals();
        }  
    }
    else
    {
        cout << "Error: argc: " << argc << endl;
    }

    return 0;
}