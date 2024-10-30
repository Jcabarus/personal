/*
    Issue:
        [/] bit causing segmentaion fault - fixed, decreased to 143
        [/] [d] function not accurately represented, has to be relative prime to Φ - fixed
        [/] Investigate:
            [/] why is [e] and [d] are not related, no issue found
            [/] [bit] limitations, decreased mitigate the floating error
            [/] how [e] is calculated, no issue found
            [/] how [d] is calculated, no issue found
        [] Find out a way to solve the integer limit
            [/] ModExp()
                >[] still faces the limit of the type
        [] p and q are not distinctly unique

    Goal:
        >[] Have user input a string
        >[] Generate a public which is shared to anyone,and private key which is kept safe by the user
        >[] Output the public and private key as well as the encrypted message 
        >[] Implement
            >[] Pointers
            >[] File Streaming          

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
        [] D = (E^d) % N
            [] Find a way to make large number calculation easy
        [] Explore:
            [] Chinese Remainder Theorem
            [] Euler's Theorem
    
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

#define bit rand() % 143 // Most possible number without causing segmentation fault

int RSA(int rtype);
int PrimeFind(int rnum);
int EDef(int p, int q, int Φ);
int EucAlg(int e, int Φ);
int MultInv(int e, int Φ);
int ModExp(int e, int N, int M);
int DRSA(int d, int N, int C);

void Testing() // Testing Environment
{
    //DO NOT REMOVE//
    printf("[TEST MODE: ACTIVE]\n");
    //DO NOT REMOVE//

    // Chinese Remainder Theorem
}

int main()
{
    // //Input
    // int M = NULL; // User input

    // // Calculation
    // srand(time(NULL));

    // int p = PrimeFind(bit);
    // int q = PrimeFind(bit); 
    // int N = p * p; // Public, shared 
    // int Φ = (p - 1) * (q - 1); 
    // int e = EDef(p, q, Φ); // Pulic, shared 
    // int d = MultInv(e, Φ); // Private, kept 


    // // Output
    // printf("[%d %d]\n", p, q);
    // printf("N: %d\n", N);
    // printf("Φ: %d\n", Φ);
    // printf("d: %d\n", d);
    // printf("e: %d\n\n", e);

    Testing();

    return 0;
}

int ModExp(int M, int e, int N) //Mitigates the limit of integers by using Modular Exponentiation
{
    int ebase;

    for(int i = 2; i < e; i++)
    {
        //M^e % N = C
        if(fmod(pow(M, 1), N) == fmod(pow(M, i), N) || fmod(pow(M, 0), N) == fmod(pow(M, i), N)) // Compares until the [intial value] == [the target value]. If so, breaks
        {
            ebase = i;
            break;
        }
    }

    ebase = fmod(e, ebase);

    return fmod(pow(M, ebase), N); //M^e % N - Encryption
}

int DRSA(int C, int d, int N)
{
    return 0; //Refer to task
}

int PrimeFind(int rnum) // This function determines if [rnum] is prime
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
        return PrimeFind(bit);
    }
}

int EDef(int p , int q, int Φ) //Defines [e] by satisfying conditions of 1 < e < Φ and gcd([number given], Φ) = 1
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
            return d;
        }
    }
}

void DeprecatedFunc() // Archived codes 
{
    // int RSA(int rtype) // Where magic happens
    // {
    //     srand(time(NULL));
        
    //     int pq[0] = 0, pq[1] = 0, N = 0, Φ = 0, d = 0, e = 0;

    //     // for(int i = 0; i < 2; i++)
    //     // {
    //     //     pq[i] = PrimeFind(bit); //Inputs two consequtive prime numbers to pq[0] and pq[1]  
    //     //     // pq[0] = 5, pq[1] = 11;
    //     // }
    //     if(N == 0 && Φ == 0 && d == 0 && e == 0)
    //     {
    //         pq[0] = 
    //         pq[1] =
    //         N = 
    //         Φ = 
    //         d = 
    //         e = 
    //     }
    //     else
    //     {
    //         if(e != d) // Ensures [e] != [d], if so, re-runs RSA function again
    //         {
    //             switch(rtype)
    //             {
    //                 case (0): return pq[0];
    //                 case (1): return pq[1];
    //                 case (2): return N;
    //                 case (3): return Φ;
    //                 case (4): return d;
    //                 case (5): return e;
    //             }
    //         }
    //         else 
    //         {
    //             RSA(rtype);
    //         }
    //     }

    // }

    // // [From Testing Function] 
    // int ebase, M, e, N;
    // scanf("%d %d %d", &M, &e, &N);

    // printf("%d^%d mod %d\n\n", M, e, N); // Prints input, remove later
    // printf("%d^%d mod %d = %.0f\n", M, 0, N, fmod(pow(M, 0), N)); // Prints the first iteration, remove later

    // for(int i = 2; i <= e; i++)
    // {
    //     printf("%d^%d mod %d = %.0f\n", M, i, N, fmod(pow(M, i), N)); // Prints every iterationl, remove later

    //     //M^e % N = C
    //     if(fmod(pow(M, 1), N) == fmod(pow(M, i), N) || fmod(pow(M, 0), N) == fmod(pow(M, i), N)) // Compares until the [intial value] == [the target value]. If so, breaks
    //     {
    //         ebase = i;
    //         break;
    //     }
    // }

    // printf("\nBase: %d\n", ebase); // Prints base , remove later
    // ebase = fmod(e, ebase);
    // printf("%d^%d mod %d = %0.f\n", M, ebase, N, fmod(pow(M, ebase), N)); //M^e % N - Encryption, prints return value

    // // [From Testing Function]
    // // ModExp
    // int M = 3, e = 47, N = 50;
    // printf("GCD: %d\n", EucAlg(M, N));
    // printf("C: %d\n", ModExp(M, e, N));
}