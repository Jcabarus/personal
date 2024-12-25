Instruction:
    You must write a program that calculates uptime for stations in a charging network. It will take in a formatted input file that indicates individual charger uptime status for a given time period and write output to standard-output (`stdout`).

    **Station Uptime** is defined as the percentage of time that any charger at a station was available, out of the entire time period that any charger *at that station* was reporting in.

    The input file will be a simple ASCII text file. The first section will be a list of station IDs that indicate the Charger IDs present at each station. The second section will be a report of each Charger ID's availability reports. An availability report will contain the Charger ID, the start time, the end time, and if the charger was "up" (i.e. available) or not.

    The following preconditons will apply:
        * Station ID will be guaranteed to be a **unsigned 32-bit integer** and guaranteed to be unique to any other Station ID.
        * Charger ID will be guaranteed to be a **unsigned 32-bit integer** and guaranteed to be unique across all Station IDs.
        * `start time nanos` and `end time nanos` are guaranteed to fit within a **unsigned 64-bit integer**.
        * `up` will always be `true` or `false`
        * Each Charger ID may have multiple availability report entries.
        * Report entries need not be contiguous in time for a given Charger ID. A gap in time in a given Charger ID's availability report should count as downtime.

    Your program will be executed in a Linux environment running on an `amd64` architecture. If your chosen language of submission is compiled, ensure it compiles in that environment. Please avoid use of non-standard dependencies. 

    The program should accept a single argument, the path to the input file. The input file may not necessarily be co-located in the same folder as the program.

    The output shall be written to `stdout`. If the input is invalid, please simply print `ERROR` and exit. `stderr` may contain detailed error information but is not mandatory. If there is no error, please write `stdout` as follows, and then exit gracefully.

    `Station ID n uptime` should be an integer in the range [0-100] representing the given station's uptime percentage. The value should be rounded down to the nearest percent.

    Please output Station IDs in *ascending order*.

    Example CLI execution:
        ./your_submission relative/path/to/input/file

    Input Format:
        [Stations]
        <Station ID 1> <Charger ID 1> <Charger ID 2> ... <Charger ID n>
        ...
        <Station ID n> ...

        [Charger Availability Reports]
        <Charger ID 1> <start time nanos> <end time nanos> <up (true/false)>
        <Charger ID 1> <start time nanos> <end time nanos> <up (true/false)>
        ...
        <Charger ID 2> <start time nanos> <end time nanos> <up (true/false)>
        <Charger ID 2> <start time nanos> <end time nanos> <up (true/false)>
        ...
        <Charger ID n> <start time nanos> <end time nanos> <up (true/false)>

    Output Format:
        <Station ID 1> <Station ID 1 uptime>
        <Station ID 2> <Station ID 2 uptime>
        ...
        <Station ID n> <Station ID n uptime>
