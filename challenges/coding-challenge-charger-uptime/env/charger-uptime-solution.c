/*
    Goal:
        Input:
            The program should accept a single argument, the path to the input file. The input file may not necessarily be co-located in the same folder as the program.
            
            Format:
                [] Station:
                    [] Station ID

                [] Charger Availability Report:
                    [] Charger ID
                    [] Start time nanos
                    [] End time nanos
                    [] up? T/F

        Calculation:
            Station uptime is the percentage of time any charger at the station was available out of the total time chargers reported at that station.

        Output:
            The output shall be written to `stdout`. If the input is invalid, please simply print `ERROR` and exit. 
            `stderr` may contain detailed error information but is not mandatory. If there is no error, please write 
            `stdout` as follows, and then exit gracefully.

    Issue:
        [] Find a way to read in to the file without switching into a binary format
        [] Review how file stream works

*/

#include <stdio.h>
#include <stdlib.h>

void Input(FILE* file);
void Calculation();
void Output();

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        if(argc < 2)
        {
           printf("Error: too few argument (expected 2)\n");
           return 0;
        }
        else if(argc > 2)
        {
           printf("Error: too many argument (expected 2)\n");
           return 0;
        }
    }
    else
    {
        FILE* finput = fopen(argv[1], "r");

        Input(finput);

        return 0;
    }
}