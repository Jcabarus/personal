```
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
    [/] Find a way to read in to the file without switching into a binary format
    [] Find a way to only read up to the end of file
        [] fgets()
    [] Find a way to combine one individual digit into one digit ([1] [1] => [11])
```