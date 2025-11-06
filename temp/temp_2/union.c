#include <stdio.h>

typedef union
{
    int integer;
    char character;
    float decimal;
} Storage;

int main()
{
    Storage box;

    printf("          Sizeof(box): %ld\n\n", sizeof(box));


    box.integer = 10;
    printf("  sizeof(box.integer): %ld\n", sizeof(box.integer));
    printf("          box.integer: %d\n\n", box.integer);
    
    box.character = 'A';
    printf("sizeof(box.character): %ld\n", sizeof(box.character));
    printf("        box.character: %c\n\n", box.character);
    
    box.decimal = 10.5;
    printf("  sizeof(box.decimal): %ld\n", sizeof(box.decimal));
    printf("            box.float: %f\n\n", box.decimal);
    
    printf("  sizeof(box.integer): %ld\n", sizeof(box.integer));
    printf("          box.integer: %d\n", box.integer);

    return 0;
}
