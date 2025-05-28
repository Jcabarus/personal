#include <iostream>
#include <fstream>

using namespace std;

void Information(string str_arg);
void FileGenCPP(string arg);
void FileGenTest(string arg);

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "leet help" << endl;
        cout << "leet info" << endl;
    }
    else
    {
        string arg_check = argv[1];

        if(arg_check == "help" || arg_check == "info")
        {
            Information(arg_check);
        }
        else
        {
            for(int i = 1; i < argc; i++)
            {
                FileGenCPP(argv[i]);
            }
        }
    }

    return 0;
}

void Information(string str_arg)
{
    if(str_arg == "info")
    {
        cout << "Leet Code template maker for cpp" << endl;
        cout << endl;
        cout << "Developed by Jerome Cabarus" << endl;
    }
    else if(str_arg == "help")
    {
        cout << "How to use:" << endl;
        cout << "   leet [arg_1] [arg_2] ... [arg_n]" << endl;
        cout << endl;
        cout << "Supported Template:" << endl;
        cout << "   cpp" << endl;
    }
    else
    {
        return;
    }
}

void FileGenCPP(string arg)
{
    ifstream file_test;
    
    file_test.open(arg);

    if(file_test.fail())
    {
        file_test.close();
    
        ofstream create_template;

        create_template.open(arg);
    
        create_template << "#include <iostream>" << endl;
        create_template << "#include <vector>" << endl;
        create_template << endl;
        create_template << "using namespace std;" << endl;
        create_template << endl;
        create_template << "class Solution" << endl;
        create_template << "{" << endl;
        create_template << "    public:" << endl;
        create_template << "        [function_type] [function_name](vector<int>& array)" << endl;
        create_template << "        {" << endl;
        create_template << "            " << endl;
        create_template << "        }" << endl;
        create_template << "};" << endl;

        create_template.close();
    }
    else
    {
        file_test.close();
        cout << arg << " exist" << endl;
    }
}

void FileGenTest(string arg)
{
    string file_arg = arg + "_test.cpp";
    ofstream create_test;

    create_test.open(file_arg);

    create_test <<  "#include " << "\""<< arg << "\"" << endl;
    create_test << endl;
    create_test <<  "void Test(int test_case);" << endl;
    create_test <<  "void Run(int test[], int size);" << endl;
    create_test << endl;
    create_test <<  "int main(int argc, char* argv[])" << endl;
    create_test <<  "{" << endl;
    create_test <<  "    if(argc != 2)" << endl;
    create_test <<  "    {" << endl;
    create_test <<  "        cout << \"No test case selected\" << endl;" << endl;
    create_test <<  "    }" << endl;
    create_test <<  "    else" << endl;
    create_test <<  "    {" << endl;
    create_test <<  "        int test_case = *argv[1] - '0';" << endl;
    create_test <<  "        Test(test_case);" << endl;
    create_test <<  "    }" << endl;
    create_test <<  "}" << endl;
}

























