#include "matrix_mult.h"

vector<vector<int>> matrix_mult(vector<vector<int>>& matrix_a, vector<vector<int>> &matrix_b)
{
    vector<vector<int>> matrix_c; // Resulting matrix

    vector<int> multiplication_operation; // Buffer operation
    int addition_accumulator; // Buffer operation

    // Dimension in their respective matrices
    int matrix_a_y = matrix_a.size();
    int matrix_a_x = matrix_a[0].size();
    int matrix_b_y = matrix_b.size();
    int matrix_b_x = matrix_b[0].size();

    // matrix_c dimension initialization a_y, b_x as its dimension
    for(int i = 0; i < matrix_a_y; i++)
    {
        matrix_c.push_back(vector<int>());

        for(int j = 0; j < matrix_b_x; j++)
        {
            matrix_c[i].push_back(-999);
        }
    }
    
    if(matrix_a_x == matrix_b_y) // Dimension validation, is the [a_y x a_?] == [? x a_x]
    {
        for(int i = 0; i < matrix_a_y; i++)
        {
            for(int j = 0; j < matrix_b_x; j++)
            {
                for(int k = 0; k < matrix_a_x; k++)
                {
                    multiplication_operation.push_back(matrix_a[i][k] * matrix_b[k][j]);
                }

                addition_accumulator = 0; // Reset accumulator

                for(int l = 0; l < multiplication_operation.size(); l++)
                {
                    addition_accumulator += multiplication_operation[l];
                }

                multiplication_operation.clear(); // Resets buffer
                matrix_c[i][j] = addition_accumulator; // Assigns the accumulated addition the respective index
            }
        }
    }

    return matrix_c;
}

vector<vector<double>> matrix_mult(vector<vector<double>>& matrix_a, vector<vector<double>> &matrix_b)
{
    vector<vector<double>> matrix_c; // Resulting matrix

    vector<double> multiplication_operation; // Buffer operation
    double addition_accumulator; // Buffer operation

    // Dimension in their respective matrices
    int matrix_a_y = matrix_a.size();
    int matrix_a_x = matrix_a[0].size();
    int matrix_b_y = matrix_b.size();
    int matrix_b_x = matrix_b[0].size();

    // matrix_c dimension initialization a_y, b_x as its dimension
    for(int i = 0; i < matrix_a_y; i++)
    {
        matrix_c.push_back(vector<double>());

        for(int j = 0; j < matrix_b_x; j++)
        {
            matrix_c[i].push_back(-999);
        }
    }
    
    if(matrix_a_x == matrix_b_y) // Dimension validation, is the [a_y x a_?] == [? x a_x]
    {
        for(int i = 0; i < matrix_a_y; i++)
        {
            for(int j = 0; j < matrix_b_x; j++)
            {
                for(int k = 0; k < matrix_a_x; k++)
                {
                    multiplication_operation.push_back(matrix_a[i][k] * matrix_b[k][j]);
                }

                addition_accumulator = 0; // Reset accumulator

                for(int l = 0; l < multiplication_operation.size(); l++)
                {
                    addition_accumulator += multiplication_operation[l];
                }

                multiplication_operation.clear(); // Resets buffer
                matrix_c[i][j] = addition_accumulator; // Assigns the accumulated addition the respective index
            }
        }
    }

    return matrix_c;
}