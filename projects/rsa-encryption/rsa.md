
Issue:
    [/] bit causing segmentaion fault - fixed, decreased to 143
    [/] [d] function not accurately represented, has to be relative prime to Φ - fixed
    [/] Investigate:
        [/] why is [e] and [d] are not related, no issue found
        [/] [bit] limitations, decreased mitigate the floating error
        [/] how [e] is calculated, no issue found
        [/] how [d] is calculated, no issue found
    [] Find out a way to solve the integer limit
    [] p and q are not distinctly unique
    [/] cannot recurse main due to standard practices

Goal:
    [] Have user input a string
    [] Generate a public which is shared to anyone,and private key which is kept safe by the user
    [] Output the public and private key as well as the encrypted message 
    [] Implement
        [] Pointers - is it necessary?
        [] File Streaming      
        [/] Command Line Argument    

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
        >[] Chinese Remainder Theorem
            Learn more about CRT
        [] Euler's Theorem
        [] Fermat's little theorem

Note:
    Left off:   
        Refer to RSA Notes

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