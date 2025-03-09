#include "rsa.h"

RSA::RSA()
{
    p = 0, 
    q = 0, 
    N = 0, 
    Φ = 0, 
    e = 0, 
    d = 0;

    srand(time(NULL));
}

void RSA::Initialize()
{
    p = PrimeFind(bit);
    q = PrimeFind(bit); 
    N = p * q; // Public, shared 
    Φ = ((p - 1) * (q - 1)) / EucAlg(p - 1, q - 1); // Find the LCM
    e = EDef(p, q, Φ); // Pulic, shared 
    d = MultInv(e, Φ); // Private, kept

    if(p != q && e != d)
    {
        return;
    }
    else
    {
        Initialize(); 
    }
}   

void RSA::Print()
{
    cout << "[" << p << " " << q <<"]"<< endl;
    cout << "N: " << N << endl;
    cout << "Φ: " << Φ << endl;
    cout << "d: " << d << endl;
    cout << "e: " << e << endl;
}

int RSA::Dcrypt(int C, int d, int N)
{
    return 0; //Refer to task
}

int RSA::Ncrypt(int M, int e, int N)
{
    return 0; //Refer to task
}

/*int RSA::CRT(int M, int e, int N)
{
    int size = 0, index = 0, n[index];

    for(int i = 1; i <= N; i++) // Define the size for [n]
    {
        if(N % i == 0)
        {
            size++;
        }
    }

    for(int i = 1; i <= N; i++) // Finds the factors of [N]
    {
        if(N % i == 0)
        {
            n[index++] = i; // Refer to Notes
        }
    }

}*/

/*int RSA::ModExp(int M, int e, int N) // Modular Exponentiation, no use yet and need optimization consider interative or recursive methods, refer to task
{
    int ebase;

    for(int i = 2; i < e; i++)
    {
        //M^e % N = C
        if(fmod(pow(M, 1), N) == fmod(pow(M, i), N) || fmod(pow(M, 0), N) == fmod(pow(M, i), N)) // Compares until the [intial value] == [the target value]. If so, breaks.
        {
            ebase = i;
            break;
        }
    }

    ebase = fmod(e, ebase);

    return fmod(pow(M, ebase), N); //M^e % N - Encryption
}*/

int RSA::PrimeFind(int rnum) // This function determines if [rnum] is prime
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
    else /*if(counter != 2 || rnum == 1)*/
    {
        return PrimeFind(bit);
    }
}

int RSA::EDef(int p , int q, int Φ) //Defines [e] by satisfying conditions of 1 < e < Φ and gcd([number given], Φ) = 1
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

int RSA::EucAlg(int e, int Φ) // Finds gcd of [e] and [Φ], need optimization
{
    if((e % e) == 0 && (Φ % e) == 0) // GCD of [e] and [Φ]
    {
        return e;
    }
    else // Euclidean Algorithms
    {
        int modr = Φ % e;
        int modb =  (Φ - modr) / e;
        int mode = (modb * e) + modr;

        return EucAlg(modr, e);
    }
}

int RSA::MultInv(int e, int Φ) //Finds multiplicative inverse for [d]
{
    int d;

    for(d = 1; d < Φ; d++) //Iterates until condition is equal to 1
    {
        if((e * d) % Φ == 1) //EucAlg(e, d) == 1
        {
            break;
        }
    }

    return d;
}