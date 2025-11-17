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

double* initialize_matrix(int x, int y)
{
    double* init_matrix = new double[x*y];

    for(int i = 0; i < x; i++)
    {

        for(int j = 0; j < y; j++)
        {
            init_matrix[(i * y) + j] = 0.0;
        }
    }

    return init_matrix;
}

void fill_matrix(double* matrix, int size)
{
    random_device ran_num;
    mt19937 eng(ran_num());
    uniform_int_distribution<> distr(1, 100);
    
    for(int k=0;k<size;k++)
    {
        for(int l=0;l<size;l++)
        {
            matrix[(k * size) + l]=distr(eng);
        }
    }
}

void print_matrix(double* matrix, int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            cout << matrix[(i * size) + j] << " ";
        }
        
        cout << endl;
    }
}

void delete_matrix(double* matrix)
{
    delete[] matrix;
    matrix = nullptr;
}

void MPI_THIS(double* Matrix_A, double* Matrix_B, double* matrix_c, double* seq_matrix_c, int size, int p, int id)
{
    int rows=size/p;
    double start, end;

    start = MPI_Wtime();

    if(size % p != 0)
    {
        cout<<"FUCK I'M NOT SUPPOSE TO BE HERE BUT HERE'S SOME INFO"<<endl;
        cout << "Row: " << rows << endl;
        cout << "  p: " << p << endl;
        return;
    }

    double* local_A=initialize_matrix(rows, size);
    double* local_C=initialize_matrix(rows, size);

    MPI_Scatter(Matrix_A, rows*size, MPI_DOUBLE, local_A, rows*size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(Matrix_B, size*size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for(int k=0;k<rows;k++)
    {
        for(int l=0;l<size;l++)
        {
            for(int m=0;m<size;m++)
            { 
                local_C[(k * size) + l]+=local_A[(k * size) + m]*Matrix_B[(m * size) + l];
            }
        }
    }

    MPI_Gather(local_C, rows*size, MPI_DOUBLE, matrix_c, rows*size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if(id==0)
    {
        for(int k=0;k<size;k++)
        {
            for(int l=0;l<size;l++)
            {
                for(int m=0;m<size;m++)
                {
                    if(matrix_c[(l * size) + m]!=seq_matrix_c[(l * size) + m])
                    {
                        cout<<"Matrics do not match"<<endl;
    
                        delete_matrix(local_A);
                        delete_matrix(local_C);
    
                        return;
                    }
                }
            }
        }

        end = MPI_Wtime();
        cout<<"Matrices Match"<<endl;
        cout << "Work on "<<size<< " matrix: " << end - start << " seconds" << endl;
    }
    
    delete_matrix(local_A);
    delete_matrix(local_C);

    return;
}

void MPI_RUN(int size, int p, int id)
{
    double* MatrixA=initialize_matrix(size, size);
    double* MatrixB=initialize_matrix(size, size);
    double* MatrixC=initialize_matrix(size, size);
    double* seq_MatrixC=initialize_matrix(size, size);
    
    //Fill Matrix A and B
    fill_matrix(MatrixA, size);
    fill_matrix(MatrixB, size);

    //Fill Seq C from Matrix A & B
    for(int k=0;k<size;k++)
    {
        for(int l=0;l<size;l++)
        {
            for(int m=0;m<size;m++)
            {
                seq_MatrixC[(k * size) + l]+=MatrixA[(k * size) + m]*MatrixB[(m * size) + l];
            }
        }
    }
    
    MPI_THIS(MatrixA,MatrixB,MatrixC,seq_MatrixC,size,p,id);

    delete_matrix(MatrixA);
    delete_matrix(MatrixB);
    delete_matrix(MatrixC);
    delete_matrix(seq_MatrixC);
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

    MPI_RUN(256,p, id);
    MPI_RUN(512,p, id);
    MPI_RUN(1024,p, id);
    
    MPI_Finalize();

    return 0;
}