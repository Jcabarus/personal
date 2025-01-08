/*
    Intended Behavior:
        When traversing through the option and when attempting to exit the program, it should be on the first try.
        
    Status: Solved
    Solution:
        Error in Ln 86, 108, 130

*/

#include <stdio.h>

int MainMenu(int selection);
int ConfMenu(int selection);

int main()
{
    MainMenu(1);

    return 0;
}

int MainMenu(int selection)
{

    if(selection == 0 || selection == 1 || selection == 2 || selection == 3)
    {
        printf("\n[Menu/]\n");
        printf("-----\n");

        printf("1. Input new entry\n");
        printf("2. Read existing entry\n");
        printf("3. Edit existing entry\n");
        printf("0. Exit\n");

        printf("\n:");
        scanf("%d", &selection);

        switch(selection)
        {
            case 1: // Input entry
            {
                ConfMenu(selection); break;                
            }   
            case 2: // Read existing entry 
            {
                ConfMenu(selection); break;
            }
            case 3: // Edit existing entry
            {
                ConfMenu(selection); break;
            }
            case 0: return 0; break;
        }
    }
    else if(selection != 0 || selection != 1 || selection != 2 || selection != 3)
    {
        printf("Invalid selection\n");
        return 0;
    }
}

int ConfMenu(int selection)
{
    int mode;

    printf("\n[Menu/");

    switch(selection)
    {
        case 1: //Input new entry
        {
            printf("Input]\n");
            printf("-----\n");
            printf("1. Input Entry\n");
            printf("2. ..\n");

            printf("\n:");
            scanf("%d", &mode);

            if(mode == 1)
            {
                printf("Input Entry");
                ConfMenu(selection);
            }
            else if(mode == 2);
            {
                MainMenu(1);
            }

            break;
        }
        case 2: //Edit existing entry
        {
            printf("Edit]\n");
            printf("-----\n");
            printf("1. Edit Existing Entry\n");
            printf("2. ..\n");

            printf("\n:");
            scanf("%d", &mode);

            if(mode == 1)
            {
                printf("Edit Existing Entry");
                ConfMenu(selection);
            }
            else if(mode == 2);
            {
                MainMenu(1);
            }

            break;
        }
        case 3: // Read Existing Entry
        {
            printf("Read]\n");
            printf("-----\n");
            printf("1. Read Existing Entry\n");
            printf("2. ..\n");

            printf("\n:");
            scanf("%d", &mode);

            if(mode == 1)
            {
                printf("Read Existing Entry");
                ConfMenu(selection);
            }
            else if(mode == 2);
            {
                MainMenu(1);
            }

            break;
        }
    }
}