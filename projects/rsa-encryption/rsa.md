README:
    Definition:
        Prime number - an integer  that only has 1 and itself as a factor, ex: 23 -> 1, 23.
        Plain text - a human readable form or text. 
        Encryption - converting plain text to a dedicated readable format.
        Decryption - converting a dedicated reable format back to plain text.
        RSA Encyption - an encryption method that commonly to transmit secure messages across parties.
        Number theory - a branch of pure mathematics primarily studying integers and arithmethic functions.
        Modular Arithmetic - a system of arithmetic for integers which considers the remainder.

    Application:
        I want to able to read in a file, and implement an encryption algorithm which in this case RSA encryption for this method. I would also be able to use this RSA to decrypt messages that are encrypted using RSA.

    Topics Explored:
        Number theory, modular arithmethic, RSA encryption.

Method:
    RSA:
        RSA encryption was developed in 1977 by Ron Rivest and Adi Shamir. This encryption method utilizes a private and public key for encryption and decryption. With that being said, we tackle the problem of implementing this algorithm by figuring out how private and public key is generated.

    Approach to generating variables:
        We first need to figure out what variable does and how it works. We first define the following variables: p, q, N, Φ(phi), e, d, E, and D. Keep in mind that p and q are two different prime numbers and must be unique to each other.

        p and q generation:
            p and q are prime numbers with no distinction to each other.

            p = PrimeFind(bit);
            q = PrimeFind(bit);

            PrimeFind(bit) function:
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

                This function passes an int to the function, and does a check if the number is a prime number or not. If not, it will recurse and generate another a random number. 'bit' is defined as rand() % 143. 143 being a random number selected in the macro definition.

        N is defined as multiplying p and q together.

        Φ(phi):
            Φ(phi) is defined as ((*p - 1) * (*q - 1)) / EucAlg(*p - 1, *q - 1);

            EucAlg function:
                int EucAlg(int e, int Φ) // Finds gcd of [e] and [Φ]
                {
                    if((e % e) == 0 && (Φ % e) == 0) // GCD of [e] and [Φ]
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

                This function passes in two integer arguments and applies a euclidean algorithm. 

        e:
            e is defined as EDef(*p, *q, *Φ);.

            EDef() function:
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

                This function passes three integer arguments and finds an appropriate number for 'e'

        d:
            d is defined as MultInv(*e, *Φ);.

            MultInv function:
                int MultInv(int e, int Φ) //Finds multiplicative inverse for [d]
                {
                    for(int d = 1; d < Φ; d++) //Iterates until condition is equal to 1
                    {
                        if((e * d) % Φ == 1) //EucAlg(e, d) == 1
                        {
                            return d;
                        }
                    }
                }

            This function pass in an integer and applies an alorigthm to find 'd'
                
Code Structure:
    Headers
    Macros
    Function prototypes

    void Testing()    
    int main(int argc, char* argv[])

    void RSA(int *p, int *q, int *N, int *Φ, int *e, int *d)
    int Dcrypt(int C, int d, int N)
    int Ncrypt(int M, int e, int N)
    int CRT(int M, int e, int N)
    int ModExp(int M, int e, int N)
    int PrimeFind(int rnum)
    int EDef(int p , int q, int Φ)
    int EucAlg(int e, int Φ)
    int MultInv(int e, int Φ)
    
    void DeprecatedFunc()

Issue:
    [/] bit causing segmentaion fault - fixed, decreased to 143
    [/] [d] function not accurately represented, has to be relative prime to Φ - fixed
    [/] Investigate:
        [/] why is [e] and [d] are not related, no issue found
        [/] [bit] limitations, decreased mitigate the floating error
        [/] how [e] is calculated, no issue found
        [/] how [d] is calculated, no issue found
    [] Find out a way to solve the integer limit
    [/] p and q are not distinctly unique
    [/] cannot recurse main due to standard practices

Goal:
    [] Have user input a string
    [] Generate a public which is shared to anyone,and private key which is kept safe by the user
    [] Output the public and private key as well as the encrypted message 
    [] Implement
        [/] Pointers - is it necessary?
        [] File Stream   
        [/] Command Line Argument  
    [/] Migrate codebase to C++
        [/] Classes
        [/] Abstraction
    [] Update/Improve documentation

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
    [] E = (m^e) % N
        [] Find a way to make large number calculation easy
    [] D = (E^d) % N
        [] Find a way to make large number calculation easy
    [] Explore:
        [] Chinese Remainder Theorem
            [] Learn more about CRT
        [] Euler's Theorem
        [] Fermat's little theorem

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