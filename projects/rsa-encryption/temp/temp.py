import math

# #######################
# #
# # Problem 5
# #
# #######################

def decode_ascii_pairs(ascii_input):
    ascii_string = str(ascii_input)
    m_string = ''
    
    for i in range(0, len(ascii_string), 2):
        m_string += chr(int(ascii_string[i:i + 2]))

    return m_string

print('==============')
print('Problem 5')
print('==============')

N = 11567078666698476133
e = 65537
c = 4430111948052713731

# Once you find the message m (integer) compute decode_ascii_pairs(m) to see the corresponding string.
def brute_force(encrypted_int):
    array_int = []
    array_prime = []

    for i in range(1, encrypted_int, 2):
        calculated = encrypted_int / i # Find the factors of the [encrypted_int]

        if(calculated % 2 == 1): # Only odd numbers
            array_int.append(int(calculated))

    for i in range(0, len(array_int)):
        prime_number = prime_find(array_int[i])

        if(prime_number != -1):
            array_prime.append(prime_number)

    print(array_int)
    print(array_prime)
    print()

    if(len(array_prime) >= 2 and array_prime[0] * array_prime[1] == encrypted_int):
        return (array_prime[0], array_prime[1])
    else:
        return ("No", "pair")

def prime_find(int_value):
    counter = 0

    for i in range(1, int_value + 1):
        if(int_value % i == 0):
            counter += 1

    if(counter == 2):
        return int_value
    else:
        return -1

# print(brute_force(3233)) # 0m0.46.050s
print(brute_force(32737)) # 0m0.050s
# print(brute_force(345439)) # 0m0.090s
# print(brute_force(3454391)) # 0m0.452s
# print(brute_force(34543237)) # 0m4s.401s
# print(brute_force(345432317)) # 0m41s.927s

# N = 11567078666698476133
# E = 4430111948052713731
# p, q = brute_force(11567078666698476133)
# e = 65537
# phi = (p - 1) * (q - 1)
# d = pow(e, -1, phi)
# ascii_input = pow(E, d, N)

# print(decode_ascii_pa?irs(ascii_input))

def factorize_rsa(N):
    """Efficiently finds p and q such that N = p * q (for RSA modulus)."""
    if N % 2 == 0:  # Handle even N (unlikely in RSA)
        return 2, N // 2    
    
    max_factor = math.isqrt(N) + 1  # Only check up to √N
    
    for p in range(3, max_factor, 2):  # Skip even numbers
        if N % p == 0:
            q = N // p
            if is_prime(q):  # Check if q is also prime
                return p, q
    return None  # No factors found (N is prime or too large)

def is_prime(n):
    """Efficient primality test (up to √n)."""
    if n <= 1:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    
    max_divisor = math.isqrt(n) + 1
    for d in range(3, max_divisor, 2):  # Check odd divisors only
        if n % d == 0:
            return False
    return True

# Example Usage
# N = 11567078666698476133
# E = 4430111948052713731
# p, q = factorize_rsa(11567078666698476133)
# e = 65537
# phi = (p - 1) * (q - 1)
# d = pow(e, -1, phi)

# ascii_input = pow(E, d, N)

# print(ascii_input)
# print(decode_ascii_pairs(ascii_input))

"""
a)  Alice's private info:
        p = 8675309
        q = 1333333333337

b)  phi = (p - 1) * (q - 1)
    phi = 11567077333356467488

    d = inv_mod(e, phi)
    d = 10886681783970789441

c)  m = pow(E, d, N)
    m = 896589678289808479

d)  decoded_message = decode_ascii_pairs(m)
    message:
        YAYCRYPTO
"""