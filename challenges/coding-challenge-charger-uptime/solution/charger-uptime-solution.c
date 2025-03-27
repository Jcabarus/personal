#include <stdio.h>
#include <stdlib.h>

void Input(FILE* filestream);
void Calculation();
void Output();

int main(int argc, char* argv[])
{
    if(argc != 2) // CML error handling
    {
        if(argc < 2)
        {
           printf("Error: too few argument (expected 2)\n");
           return -1;
        }
        else if(argc > 2)
        {
           printf("Error: too many argument (expected 2)\n");
           return -1;
        }
    }
    else
    {
        FILE* rstream = fopen(argv[1], "r");

        if(rstream == NULL) // File stream Error handing
        {
            printf("Error: unable to open file\n");
            return -1;
        }
        else
        {
            Input(rstream);
            return 0;
        }

        return 0;
    }
}

void Input(FILE* filestream)
{

}