#include "board.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    int l_play, c_play;
    srand(time(NULL));

    clock_t start_time = clock();
    Minefield minefield;

    instructions();
    question_size_table(&minefield);
    question_n_mine(&minefield);

    create_board(&minefield);
    init_board(&minefield);
    add_mines(&minefield);

    if (define_game_mode_AI(&minefield))
    {
        game_robot(&minefield, start_time);
    }

    do
    {
        if (check_win_game(&minefield))
        {
            break;
        }

        score(&minefield);
        print_minefield(&minefield);

        puts("Linha jogar: ");
        scanf("%d", &l_play);
        fflush(stdin);

        puts("Coluna jogar: ");
        scanf("%d", &c_play);

        system("cls");

    } while (play_in_board(&minefield, l_play, c_play));

    game_over(&minefield, start_time);
    destroy_board(&minefield);

    return 0;

    //dasdsdadsa

}