#include <cstddef>
#include <cstring>
#include <mpi.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <unistd.h>
#include <string>
#include <random>
#include <vector>

using namespace std;

double* DD_D(double** matrix_a, int size)
{
    int d = size * size;
    double* d_array = new double[d];
    int d_index = 0;

    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j++; j++)
        {
            d_array[d_index] = matrix_a[i][j];
            d_index++;
        }
    }

    return d_array;
}

void D_DD(double* matrix_d, double** matrix_dd, int size_d)
{
    for(int i = 0; i < size_d; i++)
    {
        for(int j = 0; j < size_d; j++)
        {
            matrix_dd[i][j] = matrix_d[i + j];
        }
    }

    return;
}

void delete_DD_D(double* matrix, int size)
{
    delete[] matrix;
}

double** initialize_matrix(int size)
{
    double** matrix;

    for(int k=0;k<size;k++)
    {
        matrix=new double*[size];
        for(int l=0;l<size;l++)
        {
            matrix[l]=new double[size];
        }
    }
    for(int k=0;k<size;k++)
    {

        for(int l=0;l<size;l++)
        {
            matrix[k][l]=0;
        }
    }

    return matrix;
}

void fill_matrix(int size, double** matrix)
{
    random_device ran_num;
    mt19937 eng(ran_num());
    uniform_int_distribution<> distr(1, 100);

    for(int k=0;k<size;k++)
    {
        for(int l=0;l<size;l++)
        {
            matrix[k][l]=distr(eng);
        }
    }
}

void delete_matrix(int size, double** matrix)
{
    for(int k=0;k<size;k++)
    {
        delete[](matrix[k]);
    }
    delete[](matrix);
}

void MPI_THIS(double** Matrix_A, double** Matrix_B, double** matrix_c, double** seq_matrix_c, int size, int p, int id)
{
    int rows=size/p;
    double start, end;
    start = MPI_Wtime();

    if(rows % p)
    {
        cout<<"FUCK I'M NOT SUPPOSE TO BE HERE BUT HERE'S SOME INFO"<<endl;
        cout << "Row: " << rows << endl;
        cout << "  p: " << p << endl;
        return;
    }


    double** local_A=initialize_matrix(rows);
    double** local_C=initialize_matrix(rows);

    double* d_Matrix_A = DD_D(Matrix_A, size);
    double* d_Matrix_B = DD_D(Matrix_B, size);
    double* d_matrix_c = DD_D(matrix_c, size);
    double* d_seq_matrix_c = DD_D(seq_matrix_c, size);

    double* d_local_A = DD_D(local_A, size);
    double* d_local_C = DD_D(local_C, size);


     MPI_Scatter(d_Matrix_A, rows, MPI_DOUBLE, d_local_A, rows, MPI_DOUBLE, 0, MPI_COMM_WORLD);
     MPI_Bcast(d_Matrix_B, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

     for(int k=0;k<rows;k++)
     {
         for(int l=0;l<size * size;l++)
         {
            d_local_C[l]+=d_local_A[l]*d_Matrix_B[l];
         }
     }

    D_DD(d_local_A, local_A, size);

    D_DD(d_Matrix_A, Matrix_A, size);
    D_DD(d_Matrix_B, Matrix_B, size);

     MPI_Gather(d_local_C, rows, MPI_DOUBLE, d_matrix_c, rows, MPI_DOUBLE, 0, MPI_COMM_WORLD);

     for(int k=0;k<size;k++)
     {
        for(int l=0;l<size * size;l++)
        {
            if(d_matrix_c[l]!=d_seq_matrix_c[l])
            {
                cout<<"Matrixes do not match"<<endl;
                return;
            }
        }
     }

     if(id==0)
    {
        end = MPI_Wtime();
        cout<<"Matrixes Match"<<endl;
        cout << "Work on "<<size<< " matrix: " << end - start << " seconds" << endl;

    }

     D_DD(d_local_C, local_C, size);
     D_DD(d_matrix_c, matrix_c, size);
     cout<<"After D_DD"<<endl;

     delete_matrix(size, local_A);
     delete_matrix(size, local_C);

     delete_DD_D(d_local_A, size);
     delete_DD_D(d_local_C, size);
     delete_DD_D(d_Matrix_A, size);
     delete_DD_D(d_Matrix_B, size);

     delete_DD_D(d_matrix_c, size);
     delete_DD_D(d_seq_matrix_c, size);

     return;
}


int main(int argc, char * argv[])
{
    //id used for rank id for our processes
    int id;
    //used for the process size of our processes
    int p;
    //used for holding the hostname of the process running
    char hostname[50];
    //init our processes that we specified in the command line
    MPI_Init(&argc, &argv);
    //grabs the ranks of our processes
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    //grabs the total number of processes we are using
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    //gets the hostname of all our processes
    gethostname(hostname, sizeof(hostname));
    cout<<"Rank:"<<id<<" Size:"<<p<<" Hostname:"<<hostname<<endl;
    fflush(stdout);
    //Fill Matrix A and B

    double**  MatrixA=initialize_matrix(256);
    double**  MatrixB=initialize_matrix(256);
    double**  MatrixC=initialize_matrix(256);
    double** seq_MatrixC=initialize_matrix(256);
    fill_matrix(256, MatrixA);
    fill_matrix(256, MatrixB);
    //Fill Seq C from Matrix A & B
    for(int k=0;k<256;k++)
    {
        for(int l=0;l<256;l++)
        {
            for(int m=0;m<256;m++)
            {
                seq_MatrixC[k][l]+=MatrixA[k][m]*MatrixB[m][l];
            }
        }
    }
    MPI_THIS(MatrixA,MatrixB,MatrixC,seq_MatrixC,256,p,id);

    delete_matrix(256, MatrixA);
    delete_matrix(256, MatrixB);
    delete_matrix(256, MatrixC);
    delete_matrix(256, seq_MatrixC);

    // Scatter BCAST
    // Gather

    // Then check Matrix C to see if matches SeqC

    MPI_Finalize();
    return 0;
}