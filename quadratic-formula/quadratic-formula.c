/*
    Goal:
        >[/] Have user input variable: [a], [b], [c]
        >[/] Calculate to get x = 0
        >[/] Output user the factors right factors
*/

#include <stdio.h>
#include <math.h>

float quadratic(int a, int b, int c, int par1);

int main()
{
    int coef[3];

    //Input
    printf("Does not work with imaginary system because they are imaginary:\n");

    for(int i = 0; i < 3; i++)
    {
        printf("%d: ", i + 1);
        scanf("%d", &coef[i]);
    }
    
    //Output
    printf("---\n");
    printf("(%d)x^2 + (%d)x + (%d)\n", coef[0], coef[1], coef[2]);

    for(int i = 0; i < 2; i++)
    {
        printf("x = %.4f\n", quadratic(coef[0], coef[1], coef[2], i));
    }

    return 0;
}

float quadratic(int a, int b, int c, int par1) //Formula (-[b] +||- sqrt([b]^2 - 4[a][c]))/2[a]
{
    float sqb = powf(b, 2);
    float sqrtbac = sqrtf(sqb - (4 * (a * c)));

    switch(par1)
    {
        case (0): return ((-b) - (sqrt((pow(b, 2)) - (4 * (a * c))))) / (2 * a); //return ((-sqb - sqrtbac) / (2 * a)); break;
        case (1): return ((-b) + (sqrt((pow(b, 2)) - (4 * (a * c))))) / (2 * a); //return ((-sqb + sqrtbac) / (2 * a)); break;
        default: return -1;
    }
}