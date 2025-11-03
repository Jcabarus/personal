#include <stdio.h>

struct struct_a
{
    int x;
    int y; 
    int z;
};

struct struct_b
{
    int x;
    int y; 
    int z;
};

void struct_application(struct struct_a this, struct struct_b that);

int main()
{
    struct struct_a coordinate;
    struct struct_b dimension;

    coordinate.x = 10;
    coordinate.y = 12;
    coordinate.z = -7;

    dimension.x = 20;
    dimension.y = 10;
    dimension.z = 30;

    struct_application(dimension, coordinate);

    return 0;
}

void struct_application(struct struct_a this, struct struct_b that)
{
    printf("This: %d %d %d\n", this.x, this.y, this.z);
    printf("That: %d %d %d", that.x, that.y, that.z);
}

