#include <iostream>
#include <gmpxx.h>

using namespace std;

int main()
{
    mpz_t x_int;
    mpz_init(x_int);
    mpz_set(x_int, );
    gmp_printf("%Zd\n", x_int);
    mpz_clear(x_int);

    return 0;
}