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

    vector<vector<int>> matrix_e = {{ 1,  3,  5,  7,  9, 11},
                                    {13, 15, 17, 19, 21, 23},
                                    {25, 27, 29, 31, 33, 35},
                                    {37, 39, 41, 43, 45, 47},
                                    {49, 51, 53, 55, 57, 59},
                                    {61, 63, 65, 67, 69, 71}};

    vector<vector<int>> matrix_f = {{ 2,  4,  6,  8, 10, 12},
                                    {14, 16, 18, 20, 22, 24},
                                    {26, 28, 30, 32, 34, 36},
                                    {38, 40, 42, 44, 46, 48},
                                    {50, 52, 54, 56, 58, 60},
                                    {62, 64, 66, 68, 70, 72}};

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

    vector<vector<int>> matrix_res_f = matrix_mult(matrix_c, matrix_b);
    for(int i = 0; i < matrix_res_f.size(); i++)
    {
        for(int j = 0; j < matrix_res_f[0].size(); j++)
        {
            cout << matrix_res_f[i][j] << " ";
        }
        
        cout << endl;
    }

    cout << endl;
    vector<vector<int>> matrix_res_g = matrix_mult(matrix_e, matrix_f);
    for(int i = 0; i < matrix_res_g.size(); i++)
    {
        for(int j = 0; j < matrix_res_g[0].size(); j++)
        {
            cout << matrix_res_g[i][j] << " ";
        }
        
        cout << endl;
    }
}