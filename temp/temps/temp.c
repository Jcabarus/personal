#include <stdio.h>

void print_game(char pos_1, char pos_2, char pos_3, char pos_4, char pos_5, char pos_6, char pos_7, char pos_8, char pos_9);
int win_condition(char pos_1, char pos_2, char pos_3, char pos_4, char pos_5, char pos_6, char pos_7, char pos_8, char pos_9);

int main()
{
    char pos_1 = ' ';
    char pos_2 = ' ';
    char pos_3 = ' ';
    char pos_4 = ' '; 
    char pos_5 = ' '; 
    char pos_6 = ' '; 
    char pos_7 = ' '; 
    char pos_8 = ' '; 
    char pos_9 = ' ';

    char player = 'x';
    int win_cond = 2, position;

    
    while(win_cond == 2)
    {
        printf("It's %c's turn: ", player);
        scanf("%d", &position);
        printf("\n");

        if(position == 1 && pos_1 == ' ')
        {
            pos_1 = player;
        }
        else if(position == 2 && pos_2 == ' ')
        {
            pos_2 = player;
        }
        else if(position == 3 && pos_3 == ' ')
        {
            pos_3 = player;
        }
        else if(position == 4 && pos_4 == ' ')
        {
            pos_4 = player;
        }
        else if(position == 5 && pos_5 == ' ')
        {
            pos_5 = player;
        }
        else if(position == 6 && pos_6 == ' ')
        {
            pos_6 = player;
        }
        else if(position == 7 && pos_7 == ' ')
        {
            pos_7 = player;
        }
        else if(position == 8 && pos_8 == ' ')
        {
            pos_8 = player;
        }
        else if(position == 9 && pos_9 == ' ')
        {
            pos_9 = player;
        }
        else
        {
            printf("Position already placed\n");

            if(player == 'x')
            {
                player = 'o';
            }
            else
            {
                player = 'x';
            }
        }

        print_game(pos_1, pos_2, pos_3, pos_4, pos_5, pos_6, pos_7, pos_8, pos_9);
        
        if(player == 'x')
        {
            player = 'o';
        }
        else
        {
            player = 'x';
        }

        win_cond = win_condition(pos_1, pos_2, pos_3, pos_4, pos_5, pos_6, pos_7, pos_8, pos_9);
    }

    if(win_cond == 1)
    {
        printf("[x] won\n");
    }
    else if(win_cond == 0)
    {
        printf("[o] won\n");
    }
    else
    {
        printf("draw");
    }

    return 0;
}

void print_game(char pos_1, char pos_2, char pos_3, char pos_4, char pos_5, char pos_6, char pos_7, char pos_8, char pos_9)
{
    printf(" %c | %c | %c \n", pos_1, pos_2, pos_3);
    printf("--------------\n");
    printf(" %c | %c | %c \n", pos_4, pos_5, pos_6);
    printf("--------------\n");
    printf(" %c | %c | %c \n", pos_7, pos_8, pos_9);
}

int win_condition(char pos_1, char pos_2, char pos_3, char pos_4, char pos_5, char pos_6, char pos_7, char pos_8, char pos_9)
{
    if((pos_1 == 'x' && pos_2 == 'x' &&  pos_3 == 'x') || (pos_4 == 'x' && pos_5 == 'x' &&  pos_6 == 'x') || (pos_7 == 'x' && pos_8 == 'x' && pos_9 == 'x') || (pos_1 == 'x' && pos_4 == 'x' && pos_7 == 'x') || (pos_2 == 'x' && pos_5 == 'x' &&  pos_8 == 'x')|| (pos_3 == 'x' && pos_6 == 'x' && pos_9 == 'x') || (pos_1 == 'x' && pos_5 == 'x' && pos_9 == 'x') || (pos_3 == 'x' && pos_5 == 'x' && pos_7 == 'x'))
    {
        return 1;
    }
    else if((pos_1 == 'o' && pos_2 == 'o' &&  pos_3 == 'o') || (pos_4 == 'o' && pos_5 == 'o' &&  pos_6 == 'o') || (pos_7 == 'o' && pos_8 == 'o' && pos_9 == 'o') || (pos_1 == 'o' && pos_4 == 'o' && pos_7 == 'o') || (pos_2 == 'o' && pos_5 == 'o' &&  pos_8 == 'o')|| (pos_3 == 'o' && pos_6 == 'o' && pos_9 == 'o') || (pos_1 == 'o' && pos_5 == 'o' && pos_9 == 'o') || (pos_3 == 'o' && pos_5 == 'o' && pos_7 == 'o'))
    {
        return 0;
    }
    else if(pos_1 != ' ' && pos_2 != ' ' && pos_3 != ' ' && pos_4 != ' ' && pos_5 != ' ' && pos_6 != ' ' && pos_7 != ' ' && pos_8 != ' ' && pos_9 != ' ')
    {
        return -1;
    }
    else
    {
        return 2;
    }
}