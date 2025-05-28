#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

class File
{
    public:
        File(ifstream &source_file, string file_input, string file_extension);
        
    private:
        void HANDLER(ifstream &source_file, string file_input, string file_extension);
        void GENERATOR(ifstream &source_file, string file_input, string template_extension);
};

File::File(ifstream &source_file, string file_input, string file_extension)
{
    ifstream write_file_test; // Opens a file stream to the requested file
    write_file_test.open(file_input);

    if(write_file_test.fail()) // Requested file does not exist
    {
        write_file_test.close();
        HANDLER(source_file, file_input, file_extension); // Generates the requested file
    }
    else // Requested file exists
    {
        write_file_test.close();
        cout << "Error: [" << file_input << "] already exist" << endl;
    }
}

void File::HANDLER(ifstream &source_file, string file_input, string file_extension)
{
    string template_extension;

    if(file_extension == "c") // Template condition checks
    {
        template_extension = "[C]";
    }
    else if(file_extension == "cpp")
    {
        template_extension = "[CPP]";
    }
    else if(file_extension == "rs")
    {
        template_extension = "[RUST]";
    }
    else
    {
        cout << "Error: [" << file_extension << "] template not found in [source_file]" << endl;
    }

    GENERATOR(source_file, file_input, template_extension);

    return;
}

void File::GENERATOR(ifstream &source_file, string file_input, string template_extension)
{
    ofstream write_file; // Generates a file stream
    write_file.open(file_input); // Creates the file_input
    
    string read_buffer, write_buffer;
    
    while(read_buffer != template_extension) // read_buffer offset
    {
        getline(source_file, read_buffer, '\n');
    }

    while(write_buffer != "}") // write_buffer boundary
    {
        getline(source_file, write_buffer);
        write_file << write_buffer;
        write_file << endl;
    }

    write_file.close();
}