/*
    Issue:
        [/] bit causing segmentaion fault - fixed, decreased to 143
        [/] [d] function not accurately represented, has to be relative prime to Φ - fixed
        >[] Investigate
            >[] why is [e] and [d] are not related
            >[] [bit] limitations
            >[] how [e] is calculated
            >[] how [d] is calculated

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
        >[] E = (m^e) % N -> Make as a separate function
        >[] D = (E^d) % N -> Make as a separate function
    
    Note:
        Left off:
            MultInv() works finding mult. inv. of p and q, but finding e and Φ does not seem to work. Need further investigation.

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

#define bit rand() % 101 // Most possible number without overstacking, causing segmentation fault

int RSA(int p, int q, int rtype);
int PrimeInt(int pnum);
int EPrime(int p , int q, int Φ);
int EucAlg(int e, int Φ);
int MultInv(int e, int Φ);

void Debugging() //Testing Environment
{
    // From int main() output
}

int main()
{
    srand(time(NULL));

    // Input
    int pq[8]; //[p] and [q], [N], [Φ], [e], [d], [E], [D] respectively

    // Calculation
    for(int i = 0; i < 8; i++) //Inputs two consequtive prime numbers to pq[0] and pq[1]
    {
        if(i >= 0 && i <= 1) // 0 - 1 p and q
        {
            // pq[i] = PrimeInt(bit); 
            pq[0] = 13; 
            pq[1] = 17; 
        }
        if(i >= 2 && i <= 5) // 2 - 5 RSA variables
        {
            pq[i] = RSA(pq[0], pq[1], i - 1);
        }
        if(i >= 6 && i <= 7) //6 - 7 E and D
        {
            pq[i] = 0;
        }
    }
    // Output
    printf("q[%d] q[%d]\nN[%d] e[%d] d[%d]\n", pq[0], pq[1], pq[2], pq[4], pq[5]);
    printf("e[%d]", EPrime(pq[0], pq[1], pq[2]));
    printf("\n---\n");

    return 0;
}

int RSA(int p, int q, int rtype) // Where magic happens
{
   int N = p * q;
   int Φ = (p - 1) * (q - 1);
   int e = EPrime(p, q, Φ);
   int d = MultInv(e, Φ);

   switch(rtype)
   {
        case (1): return N;
        case (2): return Φ;
        case (3): return e;
        case (4): return d;      
   }
}

int PrimeInt(int pnum) // This function determines if [pnum] is prime
{
    int counter = 0;

    for(int i = 1; i <= pnum; i++) // Iterates when [pnum] % [i] = 0; if so, increment counter
    {
        if(pnum % i == 0)
        {
            counter++;
        }
    }

    if(counter == 2) // Returns [pnum] when counter is a value of 2; if not, recurses
    {
        return pnum;
    }
    else if(counter != 2 || pnum == 1)
    {
        return PrimeInt(bit);
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

    return modarr[2]; //Picks in values in modarr[] for [e]
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
    for(int d = 1; d < Φ; d++) //Iterates until condition is equal to 1
    {
        if((e * d) % Φ == 1)
        {
            return d; //Output seems inaccurate, refer to task
        }
    }
}