#include <iostream>
#include "matrix_mult.h"

using std::cout;
using std::endl;

int main()
{
    vector<vector<int>> matrix_a = {{ 1,  3,  5},
                                    { 7,  9, 11},
                                    {13, 15, 17}};

    vector<vector<int>> matrix_b = {{ 2,  4,  6},
                                    { 8, 10, 12},
                                    {14, 16, 18}};

    vector<vector<int>> matrix_c = {{ 2,  3},
                                    { 5,  7},
                                    {11, 13}};

    vector<vector<int>> matrix_d = {{ 1,  4,  9}, 
                                    {16, 25, 36}};

    vector<vector<int>> matrix_res_a = matrix_mult(matrix_a, matrix_b);
    for(int i = 0; i < matrix_res_a.size(); i++)
    {
        for(int j = 0; j < matrix_res_a[0].size(); j++)
        {
            cout << matrix_res_a[i][j] << " ";
        }
        
        cout << endl;
    }  
    cout << endl;
    
    vector<vector<int>> matrix_res_b = matrix_mult(matrix_a, matrix_c);
    for(int i = 0; i < matrix_res_b.size(); i++)
    {
        for(int j = 0; j < matrix_res_b[0].size(); j++)
        {
            cout << matrix_res_b[i][j] << " ";
        }
        
        cout << endl;
    }
    cout << endl;
    
    
    vector<vector<int>> matrix_res_c = matrix_mult(matrix_d, matrix_c);
    for(int i = 0; i < matrix_res_c.size(); i++)
    {
        for(int j = 0; j < matrix_res_c[0].size(); j++)
        {
            cout << matrix_res_c[i][j] << " ";
        }
        
        cout << endl;
    }
    cout << endl;
    
    vector<vector<int>> matrix_res_d = matrix_mult(matrix_c, matrix_d);
    for(int i = 0; i < matrix_res_d.size(); i++)
    {
        for(int j = 0; j < matrix_res_d[0].size(); j++)
        {
            cout << matrix_res_d[i][j] << " ";
        }
        
        cout << endl;
    }
    cout << endl;

    vector<vector<int>> matrix_res_e = matrix_mult(matrix_c, matrix_b);
    for(int i = 0; i < matrix_res_e.size(); i++)
    {
        for(int j = 0; j < matrix_res_e[0].size(); j++)
        {
            cout << matrix_res_e[i][j] << " ";
        }
        
        cout << endl;
    }
}