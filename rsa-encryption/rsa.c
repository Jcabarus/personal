/*
    Issue:
        [/] bit causing segmentaion fault - fixed, decreased to 143
        [/] [d] function not accurately represented, has to be relative prime to Φ - fixed
        [/] Investigate
            [/] why is [e] and [d] are not related, no issue found
            [/] [bit] limitations, decreased mitigate the floating error
            [/] how [e] is calculated, no issue found
            [/] how [d] is calculated, no issue found

    Goal:
        >[] Have user input a string
        >[] Generate a public which is shared to anyone,and private key which is kept safe by the user
        >[] Output the public and private key as well as the encrypted message             

    Task:
        [/] Determine where a number is prime or not this will be use for [e], [p] and [q]
        [/] p - generated 
            [/] Issue: sometimes generates two the same p and q
        [/] q - generated
        [/] N = pd - generated
        [/] Φ = (p -1)(q - 1)
        [/] e - generated
                [/] Must satify these condition: 1 < e < Φ && gcf(1, Φ) = 1
        [/] d = (e, Φ)
                [/] Implement Multiplicative Inverse
                [/] Implement GCD
        >[] E = (m^e) % N
            [] Find a way to make large number calculation easy
        >[] D = (E^d) % N
            [] Find a way to make large number calculation easy
    
    Note:
        Left off:

        Ideas:
            Implement a function to return a value when certain parameters are met
             
        RSA:
            Consist of: 
                [p] - generated 
                [q] - generated
                [N = pd] - generated
                [Φ = (p -1)(q - 1)]
                [e] - generated
                [d = multiplicative inverse (e, Φ)]
                [public key - shared = e, N] 
                [private - kept safe = d, N] 
                [E = (m^e) % N] 
                [D = (E^d) % N]
                [p] and [q] are two different prime numbers with no correlation
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define bit rand() % 143 // Most possible number without overstacking, causing segmentation fault

int RSA(int rtype);
int PrimeGen(int rnum);
int EPrime(int p, int q, int Φ);
int EucAlg(int e, int Φ);
int MultInv(int e, int Φ);
int NRSA(int e, int N, int M);
int DRSA(int d, int N, int C);

void Debugging() //Testing Environment
{
    /*
    printf("M = %d\n", M);
    printf("C = [%d]\n", C);
    printf("D = [%d]\n", D);
    */
}

int main()
{
    //Input
    int p = RSA(0), q = RSA(1), N = RSA(2), Φ = RSA(3), d = RSA(4), e = RSA(5), M = 2;

    // Calculation
    int C = NRSA(M, e, N), D = DRSA(C, d, N);

    // Output
    printf("[%d %d]\n", p, q);
    printf("N: %d\n", N);
    printf("Φ: %d\n", Φ);
    printf("d: %d\n", d);
    printf("e: %d\n\n", e);

    return 0;
}

int RSA(int rtype) // Where magic happens
{
    srand(time(NULL));
    
    int pq[2];

    for(int i = 0; i < 2; i++)
    {
        pq[i] = PrimeGen(bit); //Inputs two consequtive prime numbers to pq[0] and pq[1]
        // pq[0] = 5, pq[1] = 11;
    }

    int N = (pq[0]) * (pq[1]); // Public, shared
    int Φ = ((pq[0] - 1)) * ((pq[1] - 1));
    int e = EPrime(pq[0], pq[1], Φ); // Pulic, shared
    int d = MultInv(e, Φ); // Private, kept

    if(e != d)
    {
        switch(rtype)
        {
            case (0): return pq[0]; 
            case (1): return pq[1]; 
            case (2): return N;
            case (3): return Φ; 
            case (4): return d; 
            case (5): return e; 
        }
    }
    else
    {
        RSA(rtype);
    }
}

int NRSA(int M, int e, int N)
{
    return 0; //Refer to task
}

int DRSA(int C, int d, int N)
{
    return 0; //Refer to task
}

int PrimeGen(int rnum) // This function determines if [rnum] is prime
{
    int counter = 0;

    for(int i = 1; i <= rnum; i++) // Iterates when [rnum] % [i] = 0; if so, increment counter
    {
        if(rnum % i == 0)
        {
            counter++;
        }
    }

    if(counter == 2) // Returns [rnum] when counter is a value of 2; if not, recurses
    {
        return rnum;
    }
    else if(counter != 2 || rnum == 1)
    {
        return PrimeGen(bit);
    }
}

int EPrime(int p , int q, int Φ) //Defines [e] by satisfying conditions of 1 < e < Φ and gcd([number given], Φ) = 1
{
    int range = 0;
    int arr[Φ], modarr[range];

    for(int i = 0; i < Φ; i++) //Initialize arr[] to 0
    {
        arr[i] = 0;
    }

    for(int i = 2; i < Φ; i++) //Stores values for [e] to arr[]
    {
        if(EucAlg(i, Φ) == 1)
        {
            arr[range] = i;
            range++;
        }
    }

    for(int i = 0; i != 0; i++) //Filters out values for [e] and negates 0
    {
        modarr[i] = arr[i];
    }

    return modarr[bit % range]; //Picks in values in modarr[] for [e]
}

int EucAlg(int e, int Φ) // Finds gcd of [e] and [Φ]
{
    if((e % e) == 0 && (Φ % e) == 0) // GCD of e and Φ
    {
        return e; 
    }
    else // Euclidean Algorithm
    {
        int modr = Φ % e;
        int modb =  (Φ - modr) / e;
        int mode = (modb * e) + modr;

        return EucAlg(modr, e);
    }
}

int MultInv(int e, int Φ) //Finds multiplicative inverse for [d]
{
    for(int d = 2; d < Φ; d++) //Iterates until condition is equal to 1
    {
        
        if((e * d) % Φ == 1) //EucAlg(e, d) == 1
        {
            return d;//Output seems inaccurate, refer to task
        }
    }
}