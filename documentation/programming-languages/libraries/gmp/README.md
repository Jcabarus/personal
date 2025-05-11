## GNU Multiple Precision Library
The purpose of this library is to handle the arbitray large integers, floating point numbers, and many more.
<br>

## Quick Reference
### Variable Initialization
1. You want to declare a variable i.e `int`, `float` as `mpz`, `mpf` in this case.
1. Use `mpz_init()` in this case to initialize the variable as `int` 
1. Use the `mpz_set_ui()` to set the variable's number, `int`.

**Example:**
```c
#include <stdio.h>
#include <gmp.h>

int main()
{
    mpz_t num; // This declares the variable which is a pointer, and is ready for initialization
    mpz_init(num); // We will use mpz_init in this case because it is an integer, and it takes in a parameter of an mpz_t pointer. By default, it is initialized to 0
    mpz_set_ui(num, 100); // This will set num's value as 100, 

    return 0;
}
```
<br>