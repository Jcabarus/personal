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

    Task:
*/

#include <stdio.h>
#include <stdlib.h>

void Input(FILE* input);
void Calculation(FILE* input);
void Output(FILE* input);

typedef struct Charger
{
    int ChargerID;
    int ChargerStart;
    int ChargerEnd;
    int uptime;
}Charger;

typedef struct Station
{
    int StationID;
    Charger* ChargerIDlinker;
}Station;

Station* StationInitialization(Station* head, int ID);

int main(int argc, char* argv[])
{

    

    // if(argc != 2) // Arguemnt error handling
    // {
    //     if(argc < 2)
    //     {
    //         printf("Error: too few argument\n");
    //     }
    //     else if(argc > 2)
    //     {
    //         printf("Error: too many argument\n");
    //     }

    //     return -1;
    // }
    // else
    // {
    //     FILE* read = fopen(argv[1], "r");

    //     InputFunction(read);

    //     fclose(read);

    //     return 0;
    // }
}

Station* StationInitialization(Station* head, int ID)
{
    head = malloc(sizeof(Station));
    head->StationID = ID;
    head->ChargerIDlinker = NULL;
}
