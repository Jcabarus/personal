/*
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
            [/] Issue: not accurately represented, has to be relative prime to Φ
                [/] Must satify these condition: 1 < e < Φ && gcf(1, Φ) = 1
        >[] d = Extended Euclidean Algorithm (e, Φ)
                >[] Find out a way to traverse throught the recursion and extract each remainders
                >[] Implement Multiplicative Inverse
                [/] Implement GCD
        >[] E = (m^e) % N -> Make as a separate function
        >[] D = (E^d) % N -> Make as a separate function

    Issue:
        [/] bit causing segmentaion fault - fixed changed to 1447
        
    Note:
        Left off:
            Extended Euclidean Algorithm (e, Φ)

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

#define bit rand() % 1447 // Most possible number without overstacking, causing segmentation fault

int RSA(int p, int q);
int GCD(int e, int Φ);
int EPrime(int p , int q);
int PrimeInt(int pnum);

void Debugging() //Testing Environment
{
    // Purpose:
}

int main()
{
    srand(time(NULL));

    // Input
    int pq[2]; //[p] and [q] respectively

    // Calculation
    for(int i = 0; i < 2; i++) //Inputs two consequtive prime numbers to pq[0] and pq[1]
    {
        pq[i] = PrimeInt(bit); 
    }

    // Output

    return 0;
}

int RSA(int p, int q) // Where magic happens
{
   int N = p * q;
   int Φ = (p - 1) * (q - 1);
   int e = EPrime(p, q);
   int d = GCD(e, Φ); //Refer to task

   return 0; //Refer to task
}

int GCD(int e, int Φ) // Finds gcd of [e] and [Φ]
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

        return GCD(modr, e);
    }
}

int EPrime(int p , int q) //Defines [e] by satisfying conditions of 1 < e < Φ and gcd([number given], Φ) = 1
{
    int Φ = (p - 1) * (q - 1), range = 0;
    int arr[Φ], modarr[range];

    for(int i = 0; i < Φ; i++) //Initialize arr[] to 0
    {
        arr[i] = 0;
    }

    for(int i = 2; i < Φ; i++) //Stores values for [e] to arr[]
    {
        if(GCD(i, Φ) == 1)
        {
            arr[range] = i;
            range++;
        }
    }

    for(int i = 0; i != 0; i++) //Filters out values for [e] and negates 0
    {
        modarr[i] = arr[i];
    }

    return modarr[bit % range]; //Randomly pick in values in modarr[] for [e]
}

int PrimeInt(int pnum) // This function determines if [input] is prime
{
    int counter = 0;

    for(int i = 1; i <= pnum; i++) // Iterates when [input] % [i] = 0; if so, increment counter
    {
        if(pnum % (i) == 0)
        {
            counter++;
        }
    }

    if(counter == 2) // Returns [input] when counter is a value of 2; if not, recurses
    {
        return pnum;
    }
    else if(counter != 2 || pnum == 1)
    {
        return PrimeInt(bit);
    }
}