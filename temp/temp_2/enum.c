#include <stdio.h>

void enumaration_usage();

enum week
{
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

int main()
{
    enumaration_usage();
    return 0;
}

void enumaration_usage()
{
    enum week week_day; 

    week_day = monday; // monday = 0
    week_day += 1; // no safety, this will modify the value

    switch(week_day)
    {
        case(monday): printf("It's monday\n"); break;
        case(tuesday): printf("It's tuesday\n"); break;
        case(wednesday): printf("It's wednesday\n"); break;
        case(thursday): printf("It's thursday\n"); break;
        case(friday): printf("It's friday\n"); break;
        case(saturday): printf("It's saturday\n"); break;
        case(sunday): printf("It's sunday\n"); break;
        default: break;
    }

    return;
}

