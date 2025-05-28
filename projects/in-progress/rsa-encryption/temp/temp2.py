def xgcd(a, N):
    u = 1
    g = a
    x = 0
    y = N

    while y != 0:
        q = g // y
        t = g % y
        s = u - q * x
        u = x
        g = y
        x = s
        y = t
        v = (g - a * u) // N

    return (g, u, v)

# print(f"{a}({u}) + {b}({v}) = {a*u + b*v}")

##############
#Fill in xgcd
##############

def inverse_mod(a,N):
    d, u, v = xgcd(a,N)

    if d != 1:
        return False
    elif u < 0:
        u = u + N

    return u

# index = 2
# a = [424242, 13337, 8675309 ]
# N = [8675309, 12345678910987654321, 13333333333333333333333337]

# u_ret = inverse_mod(a[index], N[index])

# print(inverse_mod(a[index], N[index]))

# print((a[index] * u_ret) % N[index])

print('==============')
print('Problem 3')
print('==============')
index = 2
a = [424242, 13337, 8675309 ]
N = [8675309, 12345678910987654321, 13333333333333333333333337]
a_inv = inverse_mod(a[index], N[index])
print('a =', a[index])
print('N =', N[index])
print('a_inv =', a_inv)
print('(a*a_inv) % N = ',(a[index] * a_inv) % N[index])