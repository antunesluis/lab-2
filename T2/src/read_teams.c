#include "read_teams.h"
#include "championship.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define BUFFER_SIZE 100

void press_enter_continue() {
    printf("\nPressione Enter para continuar...");
    consume_newline();
}

void clear_terminal() {
    printf("\033[H\033[J"); // Sequência de escape ANSI para limpar o terminal
}

void consume_newline() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void read_string(const char* prompt, char* buffer, size_t buffer_size) {
    printf("%s", prompt);
    fgets(buffer, buffer_size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

Team* read_team_data(Championship* c) {
    printf("------------- CRIAÇÃO DE TIMES -------------\n");

    char name_buffer[BUFFER_SIZE];
    char stadium_buffer[BUFFER_SIZE];
    char city_buffer[BUFFER_SIZE];
    char coach_buffer[BUFFER_SIZE];

    read_string("Digite o nome do time: ", name_buffer, sizeof(name_buffer));
    read_string("Digite o estádio do time: ", stadium_buffer, sizeof(stadium_buffer));
    read_string("Digite a cidade do time: ", city_buffer, sizeof(city_buffer));
    read_string("Digite o nome do treinador do time: ", coach_buffer, sizeof(coach_buffer));

    Team* team = create_team(c, name_buffer, stadium_buffer, city_buffer, coach_buffer);
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
    do {
        printf("Digite o número da posição: ");
        scanf("%d", &position);
    } while (position < 0 || position >= num_positions);

    return position;
}

Player* read_player_data(Team* team) {
    printf("\n------------- CRIAÇÃO DE JOGADOR -------------\n");

    char name_buffer[BUFFER_SIZE];
    read_string("Digite o nome do jogador: ", name_buffer, sizeof(name_buffer));

    int player_age;
    printf("Digite a idade do jogador: ");
    scanf("%d", &player_age);

    Position position = read_player_position();
    consume_newline();

    add_player(team, name_buffer, player_age, position);
    printf("\nTime adicionado!!");
}

void menu_options() {
    printf("------------- TORNEIO -------------\n");
    printf("Digite a ação desejada:\n");
    printf("\t0. Adicionar Time\n");
    printf("\t1. Apagar Time\n");
    printf("\t2. Mostrar Times\n");
    printf("\t3. Adicionar jogador a time existente\n");
    printf("\t4. Apagar jogador de um time\n");
    printf("\t5. Mostrar time relacionado a determinado jogador\n");
    printf("\t6. Sair\n");
    puts("");
}

void print_team(Championship* c) {
    clear_terminal();
    printf("------------- LIST OF TEAMS -------------\n");
    list_print(get_champ_teams(c));
    press_enter_continue();
}

void add_team(Championship* c) {
    Team* team = read_team_data(c);
    read_player_data(team);

}

void read_and_remove_team(Championship* c) {
    char name_buffer[BUFFER_SIZE];
    read_string("Digite o nome do time a ser removido: ", name_buffer, sizeof(name_buffer));
    remove_team_by_name(c, name_buffer);
}

void read_add_player(Championship* c) {
    char name_buffer[BUFFER_SIZE];
    read_string("Digite o nome do time: ", name_buffer, sizeof(name_buffer));
    Team* team = get_team(c, name_buffer);

    read_player_data(team);
}

bool menu(Championship* c) {
    unsigned int option;

    do {
        clear_terminal();
        menu_options();

        scanf("%u", &option);
        consume_newline();

        switch (option) {
        case AddTeam:
            add_team(c);
            break;
        case DeleteTeam:
            read_and_remove_team(c);
            break;

        case ShowTeams:
            print_team(c);
            break;

        case AddPlayer:
            read_add_player(c);
            break;

        case DeletePlayer:
            break;

        case ShowTeamByPlayer:
            break;

        default:
            break;
        }

        press_enter_continue();
    } while (option != Exit);
}


