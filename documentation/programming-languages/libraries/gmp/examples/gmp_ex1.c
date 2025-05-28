#include <stdio.h>
#include <gmp.h>

int main()
{
    mpz_t number;

    mpz_init(number);
    mpz_set_ui(number, 102341341234123234);

    gmp_printf("%Zd\n", number);

    return 0;
}