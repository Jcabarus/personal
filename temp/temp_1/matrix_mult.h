/*
    2D array behaviour

    array[y][x]
    y - axis, up/down - column
    x - axix, left/right - row

    Functionality:
        Multiplies two matrices together
        Conditional checks if the matrices are valid before multiplying
        If matrices multiplication operation is invalid, it returns -999
*/

#ifndef MATRIX_MULT
#define MATRIX_MULT

#include <vector>

using std::vector;

vector<vector<int>> matrix_mult(vector<vector<int>>& matrix_a, vector<vector<int>> &matrix_b);

#endif