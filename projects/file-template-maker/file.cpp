#include "file.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "./ help || info || file_1, file_2, ..., file_n" << endl;
    }
    else
    {
        string arg_temp = argv[1];
        
        if(argc == 2 && (arg_temp == "info" || arg_temp == "help")) // argv infomation check
        {
            cout << "Template maker" << endl;
            cout << endl;
            cout << "Supported template" << endl;
            cout << "   c, cpp" << endl;
            return 0;
        }
        
        ifstream source_file_test; 
        source_file_test.open("source_file");
    
        if(source_file_test.fail()) // source_file check, if it's in the same directory as the program
        {
            source_file_test.close();
            cout << "Error: [source_file] is inaccessible" << endl;
            
            return -1;
        }
        else
        {
            source_file_test.close();
    
            for(int i = 1; i < argc; i++) // Determines what is the file's extension
            {
                string file = argv[i], file_extension;
                int extension_position = 0;
    
                while(file[extension_position] != '.' && extension_position < file.length()) // Finds the '.' position
                {
                    extension_position++;
                }
    
                if(extension_position == file.length()) // The file's '.' position is not found
                {
                    cout << "[" << argv[i] << "] does not have an extension" << endl;
                }
                else // The file's '.' position is found
                {
                    for(int i = extension_position + 1; i < file.length(); i++) // file_extension = file[extension_position]
                    {
                        file_extension.push_back(file[i]);
                    }
                    
                    ifstream read_source;
                    read_source.open("source_file");
    
                    File generate_file(read_source, argv[i], file_extension); 
    
                    read_source.close();
                }
            }
        }
    }

    return 0;
}