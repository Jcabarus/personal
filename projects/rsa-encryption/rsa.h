#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

#define bit rand() % 143 // Most possible number without causing segmentation fault

using namespace std;

class RSA
{
    public:
        RSA();
        void Initialize();
        void Print();

    private:
        int Dcrypt(int d, int N, int C);
        int Ncrypt(int M, int e, int N);
        // int CRT(int M, int e, int N);
        // int ModExp(int e, int N, int M);
        int PrimeFind(int rnum);
        int EDef(int p, int q, int Φ);
        int EucAlg(int e, int Φ);
        int MultInv(int e, int Φ);

        int p, q, N, Φ, e, d;
};