/*
    Goal:
        >[] Have user input a string
        >[] Generate a public which is shared and private key which is kept safe by the user
        >[] Output public and private key as well as the encrypted message             

    Note:
        >Left off:
            >Extended Euclidean Algorithm (e, Φ)
        >RSA:
            >Consist of: 
                >[p] - generated 
                >[q] - generated
                >[N = pd] - generated
                >[Φ = (p -1)(q - 1)]
                >[e] - generated
                >[d = multiplicative inverse (e, Φ)]
                >[public key - shared = e, N] 
                >[private - kept safe = d, N] 
                >[E = (m^e) % N] 
                >[D = (E^d) % N]
            >[p] and [q] are two different prime numbers with no correlation

    Task:
        >[/] Determine where a number is prime or not this will be use for [e], [p] and [q]
        >[/] p - generated 
            >[/] Issue: sometimes generates two the same p and q
        >[/] q - generated
        >[/] N = pd - generated
        >[/] Φ = (p -1)(q - 1)
        >[/] e - generated
        >[] d = Extended Euclidean Algorithm (e, Φ)
        >[] E = (m^e) % N -> Make as a separate function
        >[] D = (E^d) % N -> Make as a separate function
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define bit rand() % 46256//Most possible number without overflowing into negative 46256

int RSA(int p, int q);
int PrimeInt(int pnum);
int EuclExtAlg(int e, int Φ);

void Debugging(int input) //Testing Environment
{
    /*
        🦗🦗🦗
        
    */
}

int main()
{
    srand(time(NULL));

    //Input
    int pq[2]; //[p] and [q] respectively

    //Calculation
    for(int i = 0; i < 2; i++) //Inputs two consequtive prime numbers to pq[0] and pq[1]
    {
        pq[i] = PrimeInt(bit); 
    }

    //Output
    printf("Code executed successfully\n");

    return 0;
}

int PrimeInt(int pnum) //This function determines if [input] is prime
{
    int counter = 0;

    //Iterates when [input] % [i] = 0; if so, increment counter
    for(int i = 1; i <= pnum; i++)
    {
        if(pnum % (i) == 0)
        {
            counter++;
        }
    }

    //Returns [input] when counter is a value of 2; if not, recurses
    if(counter == 2)
    {
        return pnum;
    }
    else if(counter != 2 || pnum == 1)
    {
        return PrimeInt(bit);
    }
}

int RSA(int p, int q)
{
   int N = p * q;
   int Φ = (p - 1) * (q - 1);
   int e = PrimeInt(bit);
   int d = EuclExtAlg(e, Φ);

   return d; //return value should be [d]
}

int EuclExtAlg(int e, int Φ) //Finds gcd of [e] and [Φ]
{
    //Euclidean Algorithm
    if(e == 0)
    {
        return e - 1; //e is small, remove later
    }
    if(Φ == 0)
    {
        return Φ + 1; //Φ is small, remove later
    }
    else
    {
        if(e < Φ)
        {
            return EuclExtAlg(e, Φ % e);
        }
        if(e > Φ)
        {
            return EuclExtAlg(e % Φ, Φ);
        }
    }

    //Extended Euclidean Algorithm <-- Left off
}