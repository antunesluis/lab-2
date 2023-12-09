#include "read_teams.h"
#include "championship.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define BUFFER_SIZE 100

void menu_options() {
    printf("------------- TORNEIO -------------\n");
    printf("Digite a ação desejada:\n");
    printf("\t0. Adicionar Time\n");
    printf("\t1. Apagar Time\n");
    printf("\t2. Mostrar Times\n");
    printf("\t3. Adicionar jogador a time existente\n");
    printf("\t4. Apagar jogador de um time\n");
    printf("\t5. Adiconar status a um jogador\n");
    printf("\t6. Sair\n");
    puts("");
}

void clear_terminal() {
    printf("\033[H\033[J"); // Sequência de escape ANSI para limpar o terminal
}

void consume_newline() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void press_enter_continue() {
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n');
}

void read_string(const char* prompt, char* buffer, size_t buffer_size) {
    printf("%s", prompt);

    if (fgets(buffer, buffer_size, stdin) == NULL) {
        printf("Erro ao ler a entrada.\n");
    }
    else {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

Team* read_team_data(Championship* c) {
    printf("------------- CRIAÇÃO DE TIMES -------------\n");

    char* name_buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
    char* stadium_buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
    char* city_buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
    char* coach_buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));

    read_string("Digite o nome do time: ", name_buffer, BUFFER_SIZE);
    read_string("Digite o estádio do time: ", stadium_buffer, BUFFER_SIZE);
    read_string("Digite a cidade do time: ", city_buffer, BUFFER_SIZE);
    read_string("Digite o nome do treinador do time: ", coach_buffer, BUFFER_SIZE);

    Team* team = create_team(c, name_buffer, stadium_buffer, city_buffer, coach_buffer);

    free(name_buffer);
    free(stadium_buffer);
    free(city_buffer);
    free(coach_buffer);

    return team;
}

int read_player_position() {
    const char* positions[] = { "Goleiro", "Lateral Direito", "Lateral Esquerdo",
                                "Defensor", "Meio-campista", "Atacante" };
    const int num_positions = sizeof(positions) / sizeof(positions[0]);

    printf("Escolha a posição do jogador:\n");
    for (int i = 0; i < num_positions; i++) {
        printf("\t[%d] %s\n", i, positions[i]);
    }

    int position;
    int result;

    do {
        printf("Digite o número da posição: ");
        result = scanf("%d", &position);

        if (result == 0 || result == EOF) {
            printf("Entrada inválida. Por favor, digite um número.\n");
            while (getchar() != '\n');
        }
    } while (position < 0 || position >= num_positions);

    return position;
}

unsigned int read_player_age() {
    unsigned int player_age;

    while (1) {
        printf("Digite a idade do jogador: ");
        int result = scanf("%u", &player_age);

        if (result == 1) {
            break;
        }
        else {
            while (getchar() != '\n');
            printf("\nPor favor, insira uma idade válida.\n");
        }
    }

    return player_age;
}

void read_player_data(Team* team) {
    printf("\n------------- CRIAÇÃO DE JOGADOR -------------\n");

    char* name_buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
    read_string("Digite o nome do jogador: ", name_buffer, BUFFER_SIZE);

    unsigned int player_age = read_player_age();

    Position position = read_player_position();
    consume_newline();

    add_player(team, name_buffer, player_age, position);
    printf("\nJogador adicionado!\n");

    free(name_buffer);
}

void print_team(Championship* c) {
    clear_terminal();
    printf("------------- LIST OF TEAMS -------------\n");
    list_print(get_champ_teams(c));
}

void add_team(Championship* c) {
    Team* team = read_team_data(c);
    read_player_data(team);
}

void read_and_remove_team(Championship* c) {
    char* name_buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));

    read_string("Digite o nome do time a ser removido: ", name_buffer, BUFFER_SIZE);
    remove_team_by_name(c, name_buffer);

    free(name_buffer);
}

void read_add_player(Championship* c) {
    char* name_buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));

    read_string("Digite o nome do time: ", name_buffer, BUFFER_SIZE);
    Team* team = get_team(c, name_buffer);

    if (team != NULL) {
        read_player_data(team);
    }
    else {
        printf("\nTime inexistente!");
    }

    free(name_buffer);
}

Team* search_team_by_name(Championship* c) {
    char* team_buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));

    read_string("Digite o nome do time: ", team_buffer, BUFFER_SIZE);
    Team* team = get_team(c, team_buffer);

    if (team == NULL) {
        printf("\nTime Inexistente");
    }

    free(team_buffer);
    return team;
}

Player* search_player_by_names(Championship* c, Team* team) {
    char* player_buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));

    read_string("Digite o nome do jogador: ", player_buffer, BUFFER_SIZE);
    Player* player = get_player(team, player_buffer);

    if (player == NULL) {
        printf("\nJogador não existe no time selecionado");
    }

    free(player_buffer);
    return player;
}

Player* get_player_by_team(Championship* c) {
    Team* team = search_team_by_name(c);

    if (team != NULL) {
        Player* player = search_player_by_names(c, team);

        if (player != NULL) {
            return player;
        }
        printf("\nJogador não existe no time selecionado");


    }
    printf("\nTime não encontrado");
    return NULL;
}

int read_integer(const char* prompt) {
    int value;

    printf("\n%s", prompt);

    while (scanf("%d", &value) != 1) {
        while (getchar() != '\n');

        printf("Por favor, digite um número inteiro válido: ");
    }
    puts("");

    return value;
}

void read_stats_player(Player* Player) {
    unsigned int goals_scored = read_integer("Digite o numero de gols feitos: ");
    unsigned int yellow_cards = read_integer("Digite o numero de cartões amarelos: ");
    unsigned int red_cards = read_integer("Digite o numero de cartões vermelhos: ");
    unsigned int fouls = read_integer("Digite o numero de faltas");

    add_player_stats(Player, goals_scored, yellow_cards, red_cards, fouls);
    printf("\nInformações adicionadas\n");
}

void get_player_and_read_stats(Championship* c) {
    Player* player = get_player_by_team(c);

    printf("\n----------- Estatisticas -----------");
    if (player != NULL) {
        read_stats_player(player);
    }
}

void read_delete_player(Championship* c) {
    Team* team = search_team_by_name(c);

    if (team != NULL) {
        Player* player = search_player_by_names(c, team);

        if (player != NULL) {
            remove_player(team, player);
            printf("\nJogador removido!");
            return;
        }
        printf("\nJogador não existe no time selecionado");
    }

    printf("\nTime não encontrado");
}

void menu(Championship* C) {
    unsigned int option;
    int result;

    do {
        clear_terminal();
        menu_options();

        result = scanf("%u", &option);
        consume_newline();

        if (result == 0 || result == EOF) {
            printf("Entrada inválida. Por favor, digite um número.\n");
            while (getchar() != '\n');
        }
        else {
            switch (option) {
            case AddTeam:
                add_team(C);
                break;
            case DeleteTeam:
                read_and_remove_team(C);
                break;
            case ShowTeams:
                print_team(C);
                break;
            case AddPlayer:
                read_add_player(C);
                break;
            case DeletePlayer:
                read_delete_player(C);
                break;
            case AddStatsPlayer:
                get_player_and_read_stats(C);
                break;
            case Exit:
                break;
            default:
                printf("Opção inválida\n");
                break;
            }
        }

        press_enter_continue();
    } while (option != Exit);
}