#include <iostream>

using namespace std;

class Station
{
    public:
        Station(unsigned int station_id); // Construction
        ~Station(); // Deconstructor
        void Insert(int id_value);
        void Edit(int id_value);
        
    private:
        struct Charger
        {
            unsigned int charger_id;
            unsigned long int start_time;
            unsigned long int end_time;
            bool status_availability;
            Charger* station_pointer;
        };

        Charger* INSERT(Charger* pointer, int id_value);
        Charger* INITIALIZE(unsigned int id_value);
        Charger* EDIT(Charger* pointer, unsigned long int start_t_value, unsigned long int end_t_value, bool status);

        Charger* *pointer_station;
        int station_size, station_id;
    };

Station::Station(unsigned int input_value)
{
    station_id = input_value;
    station_size = 100; // Default value for now

    pointer_station = new Charger*[station_size]; 

    for(int i = 0; i < station_size; i++) // Poitner initilization
    {
        pointer_station[i] = NULL;
    }
}

Station::~Station()
{
    delete[] pointer_station;
}

void Station::Insert(int id_value)
{
    int index = 0;

    while(pointer_station[index] != NULL && index < station_size) // Index initialization for available pointer
    {
        index++;
    }

    pointer_station[index] = INSERT(pointer_station[index], id_value);
}

Station::Charger* Station::INSERT(Charger* pointer, int id_value)
{
    Charger* insert_charger = INITIALIZE(id_value);

    if(pointer == NULL)
    {
        pointer = insert_charger;
    }
    else // The same pointer cannot have more than one element
    {
        Charger* temp = pointer;
        pointer = insert_charger;

        delete temp;
    }

    return pointer;
}

Station::Charger* Station::INITIALIZE(unsigned int id_value)
{
    Charger* initialize_station = new Charger;

    initialize_station->charger_id = id_value;
    initialize_station->start_time = 0;
    initialize_station->end_time = 0;
    initialize_station->status_availability = false;
    initialize_station->station_pointer = NULL;

    return initialize_station;
}


Station::Charger* Station::EDIT(Charger* pointer, unsigned long int start_t_value, unsigned long int end_t_value, bool status)
{
    pointer->start_time = start_t_value;
    pointer->end_time = end_t_value;
    pointer->status_availability = status;

    return pointer;
}