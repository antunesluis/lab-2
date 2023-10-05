#ifndef FLOAT_BOARD_H
#define FLOAT_BOARD_H

#include <stdbool.h>

typedef enum
{
    EMPTY,
    NUMBER,
    MINE,
} PieceType;

typedef struct _piece
{
    PieceType type;
    int value;
    bool open_in_game;
    bool possible_mine;
} Piece;

typedef struct _minefield
{
    Piece **board;
    int size;
    int n_mines;
    int score;
} Minefield;

void create_board(Minefield *minefield);
void destroy_board(Minefield *minefield);
void init_board(Minefield *minefield);
void add_mines(Minefield *minefield);
void print_minefield(Minefield *minefield);

void question_n_mine(Minefield *minefield);
void question_size_table(Minefield *minefield);
void game_over(Minefield *minefield, int start_time);

bool check_win_game(Minefield *minefield);
bool define_game_mode_AI(Minefield *minefield);
bool play_in_board(Minefield *minefield, int l_play, int c_play);

void instructions();
void score(Minefield *minefield);
void game_robot(Minefield *minefield, int start_time);

#endif