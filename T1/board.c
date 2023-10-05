#include "board.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

const int MIN_NUMBERS_POSSIBLE_MINE = 3;

void create_board(Minefield *minefield)
{
    minefield->board = (Piece **)calloc(minefield->size, sizeof(Piece *));

    for (int i = 0; i < minefield->size; i++)
    {
        minefield->board[i] = (Piece *)calloc(minefield->size, sizeof(Piece));
    }
}

void destroy_board(Minefield *minefield)
{
    for (int i = 0; i < minefield->size; i++)
    {
        free(minefield->board[i]);
        minefield->board[i] = NULL;
    }
    free(minefield->board);
    minefield->board = NULL;
}

void init_board(Minefield *minefield)
{
    for (int i = 0; i < minefield->size; i++)
    {
        for (int j = 0; j < minefield->size; j++)
        {
            minefield->score = 0;
            minefield->board[i][j].value = 0;
            minefield->board[i][j].type = EMPTY;
            minefield->board[i][j].open_in_game = false;
            minefield->board[i][j].possible_mine = false;
        }
    }
}

void add_numbers(Minefield *minefield, int row, int col)
{
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int k = 0; k < 8; k++)
    {
        int ni = row + dx[k];
        int nj = col + dy[k];

        if (ni >= 0 && ni < minefield->size && nj >= 0 && nj < minefield->size &&
            minefield->board[ni][nj].type != MINE)
        {
            minefield->board[ni][nj].type = NUMBER;
            minefield->board[ni][nj].value++;
        }
    }
}

void add_mines(Minefield *minefield)
{
    for (int i = 0; i < minefield->n_mines; i++)
    {
        int c_rand = rand() % minefield->size;
        int l_rand = rand() % minefield->size;
        minefield->board[l_rand][c_rand].type = MINE;
        minefield->board[l_rand][c_rand].value = 9;

        add_numbers(minefield, l_rand, c_rand);
    }
}

void print_lines_terminal(Minefield *minefield)
{
    printf("\n   |");
    for (int i = 0; i < (minefield->size * 4) - 1; i++)
    {
        printf("-");
    }
    printf("|\n");
}

void print_minefield(Minefield *minefield)
{
    int i, j;

    printf("\n   ");
    for (i = 0; i < minefield->size; i++)
    {
        printf("%3d ", i);
    }
    print_lines_terminal(minefield);

    for (i = 0; i < minefield->size; i++)
    {
        printf("%2d |", i);
        for (j = 0; j < minefield->size; j++)
        {
            if (!minefield->board[i][j].open_in_game)
            {
                printf(" %c |", 219);
                continue;
            }

            if (minefield->board[i][j].type == EMPTY)
            {
                printf("   |");
                continue;
            }

            if (minefield->board[i][j].type == MINE)
            {
                printf(" %c |", 'X');
                continue;
            }

            printf(" %d |", minefield->board[i][j].value); // Espaços em branco para células vazias
        }
        print_lines_terminal(minefield);
    }
    puts("");
}

bool capacity(Minefield *minefield, int l, int c)
{
    if (l < 0 || l >= minefield->size || c < 0 || c >= minefield->size)
    {
        // printf("**** Coordenadas [%d][%d] fora dos limites do tabuleiro.\n", l, c);
        return false;
    }

    return true;
}

void open_board(Minefield *minefield, int l_play, int c_play)
{
    if (!capacity(minefield, l_play, c_play))
    {
        return; // Verificar limites do tabuleiro
    }

    Piece *current_cell = &minefield->board[l_play][c_play];

    if (current_cell->open_in_game || current_cell->type == MINE)
    {
        return; // Já foi aberta ou é uma mina
    }

    // Abre a célula atual, independentemente do tipo
    current_cell->open_in_game = true;

    if (current_cell->type != EMPTY)
    {
        return; // Se não for vazia, não precisa explorar as células vizinhas
    }

    // Verifica as células vizinhas recursivamente
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int k = 0; k < 8; k++)
    {
        int ni = l_play + dx[k];
        int nj = c_play + dy[k];
        open_board(minefield, ni, nj);
    }
}

bool play_in_board(Minefield *minefield, int l_play, int c_play)
{
    Piece *current_cell = &minefield->board[l_play][c_play];

    if (!capacity(minefield, l_play, c_play))
        return true;

    if (current_cell->open_in_game)
    {
        printf("\n**** Essa celula ja foi aberta.\n");
        return true;
    }

    if (current_cell->type == NUMBER)
    {
        current_cell->open_in_game = true;
        return true;
    }

    if (current_cell->type == MINE)
    {
        printf("\n#### MINA ENCONTRADA em [%d][%d], voce perdeu o jogo :(", l_play, c_play);
        return false;
    }

    open_board(minefield, l_play, c_play);
    return true;
}

void question_size_table(Minefield *minefield)
{
    printf("\n\tDigite o numero de linhas e de colunas da matriz: ");
    scanf("%d", &minefield->size);

    while (minefield->size <= 0)
    {
        printf("\n**** Valor inválido. O tamanho deve ser positivo. Tente novamente: ");
        scanf("%d", &minefield->size);
    }
}

void question_n_mine(Minefield *minefield)
{
    int max_n_mines = minefield->size * minefield->size;

    printf("\n\tQuantas minas voce deseja que o jogo possua? ");
    scanf("%d", &minefield->n_mines);

    while (minefield->n_mines >= max_n_mines)
    {
        printf("\n**** Numero de minas maior que o de posicoes, tente novamente:");
        scanf("%d", &minefield->n_mines);
    }
}

void score(Minefield *minefield)
{
    minefield->score = 0;

    for (int i = 0; i < minefield->size; i++)
    {
        for (int j = 0; j < minefield->size; j++)
        {
            if (minefield->board[i][j].type == EMPTY &&
                minefield->board[i][j].open_in_game)
                minefield->score++;
        }
    }

    printf("\n");
    printf("\tPONTUACAO ATUAL:  %15d pts\n", minefield->score);
}

void end_timer(int start_time)
{
    clock_t end_time = clock(); // Captura o tempo final
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\n\tTEMPO TOTAL DE JOGO: %15.2f segundos", elapsed_time);
}

void open_table_game_over(Minefield *minefield)
{
    for (int i = 0; i < minefield->size; i++)
    {
        for (int j = 0; j < minefield->size; j++)
        {
            minefield->board[i][j].open_in_game = true;
        }
    }
}

void game_over(Minefield *minefield, int start_time)
{
    printf("\n\n");
    printf("#### INFORMACOES FINAIS SOBRE O JOGO: ");

    end_timer(start_time);
    score(minefield);
    printf("\n");

    open_table_game_over(minefield);
    print_minefield(minefield);
}

bool check_win_game(Minefield *minefield)
{
    for (int i = 0; i < minefield->size; i++)
    {
        for (int j = 0; j < minefield->size; j++)
        {
            if (!minefield->board[i][j].open_in_game &&
                minefield->board[i][j].type != MINE)
            {
                return false;
            }
        }
    }

    printf("\n#### PARABENS, VOCE ACHOU TODAS AS MINAS E GANHOU O JOGO ####");
    return true;
}

bool define_game_mode_AI(Minefield *minefield)
{
    char choice;

    printf("\n#### DIGITE QUEM DEVE JOGAR");
    printf("\n[a] Player");
    printf("\n[b] Robo\n");

    while (true)
    {
        scanf(" %c", &choice);
        if (choice == 'a')
        {
            return false;
        }
        else if (choice == 'b')
        {
            return true;
        }
        printf("Opcao invalida. Escolha 'a' ou 'b'.\n");
    }
}

void instructions()
{
    printf("\n\n");
    printf("------------------ BEM VINDO AO CAMPO MINADO ------------------");
    printf("\n\n#### INSTRUCOES:\n");
    printf("\t1. Seu principal objetivo eh descobrir a localizacao de todas as minas.\n");
    printf("\t2. Se descobrir um quadrado vazio, o jogo continua.\n");
    printf("\t3. Se aparecer um numero, ele informara quantas minas estao escondidas nos oito quadrados que o cercam.\n");
    printf("\t4. Existem dois modos de jogo, sendo um onde o jogador realiza as ações e outro onde o robo tenta finalizar o jogo.\n\n");
    printf("\n#### AGORA VAMOS DEFINIR O TABULEIRO:");
}

void define_possible_mines_in2x2(Minefield *minefield, int row, int col)
{
    int cont_numbers = 1;
    int row_empty = -1, col_empty = -1;
    bool exist_empty = false;

    for (int i = 0; i <= 1; i++)
    {
        for (int j = 0; j <= 1; j++)
        {
            int ni = row + i;
            int nj = col + j;

            if (capacity(minefield, ni, nj))
            {
                if (minefield->board[ni][nj].type == NUMBER &&
                    minefield->board[ni][nj].open_in_game)
                {
                    cont_numbers++;
                }

                if (minefield->board[ni][nj].type == EMPTY &&
                    !minefield->board[ni][nj].open_in_game)
                {
                    exist_empty = true;
                    row_empty = ni;
                    col_empty = nj;
                }
            }
        }
    }

    if (cont_numbers == MIN_NUMBERS_POSSIBLE_MINE && exist_empty)
    {
        minefield->board[row_empty][col_empty].possible_mine = true;
    }
}

void found_number(Minefield *minefield)
{
    for (int i = 0; i < minefield->size; i++)
    {
        for (int j = 0; j < minefield->size; j++)
        {
            if (minefield->board[i][j].type == NUMBER && minefield->board[i][j].open_in_game)
            {
                define_possible_mines_in2x2(minefield, i, j);
            }
        }
    }
}

bool open_piece_empty(Minefield *minefield)
{
    int c_rand, l_rand;
    bool found = false;

    while (!found)
    {
        c_rand = rand() % minefield->size;
        l_rand = rand() % minefield->size;

        if (!minefield->board[l_rand][c_rand].open_in_game &&
            !minefield->board[l_rand][c_rand].possible_mine)
        {
            found = true;
        }
    }

    if (!play_in_board(minefield, l_rand, c_rand))
    {
        return false;
    }
    return true;
}

void game_robot(Minefield *minefield, int start_time)
{
    do
    {
        if (check_win_game(minefield))
        {
            break;
        }

        found_number(minefield);

    } while (open_piece_empty(minefield));

    system("cls");

    printf("\n#### Ultimo tabuleiro do robo antes de acabar:\n");
    print_minefield(minefield);

    game_over(minefield, start_time);
    destroy_board(minefield);
}