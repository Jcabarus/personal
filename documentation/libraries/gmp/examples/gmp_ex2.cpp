#include <iostream>
#include <gmpxx.h>

int main()
{
    mpz_class int_a;
    mpz_class int_b;
    mpz_class result;

    int_a = 12341234234121;
    int_b = 123432;

    std::cout <<int_a * int_b << std::endl;

    // mpz_mul(result.get_mpz_t(), int_a.get_mpz_t(), int_b.get_mpz_t());

    // std::cout << result << std::endl;

    return 0;
}