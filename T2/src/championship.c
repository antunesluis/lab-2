#include "championship.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

typedef struct _statistics {
    unsigned int goals_scored;
    unsigned int goals_conceded;
    unsigned int yellow_cards;
    unsigned int red_cards;
    unsigned int fouls;
} Statistics;


typedef struct _player {
    Position position;
    Statistics stats;
    char* name;
    unsigned int age;
} Player;


typedef struct _team {
    Statistics stats;
    Player** players;
    unsigned int n_players;
    char* coach;
    char* name;
    char* stadium;
    char* city;
} Team;


typedef struct _championship {
    List* list_teams;
    unsigned int rounds;
    unsigned int matches;
} Championship;


typedef struct _doubly_node {
    Team* val;
    struct _doubly_node* prev;
    struct _doubly_node* next;
} DoublyNode, Node;


typedef struct _doubly_linked_list {
    Node* begin;
    Node* end;
    size_t size;
} DoublyLinkedList, List;


Node* node_crete(Team* val) {
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->prev = NULL;
    node->next = NULL;
    node->val = val;

    return node;
}

List* list_create() {
    List* L = (List*)calloc(1, sizeof(List));
    L->begin = NULL;
    L->end = NULL;
    L->size = 0;

    return L;
}

void list_destroy(List** L_ref) {
    List* L = *L_ref;

    Node* p = L->begin;
    Node* aux = NULL;

    while (p != NULL) {
        aux = p;
        p = p->next;
        free(aux);
    }
    free(L);

    *L_ref = NULL;
}

bool list_is_empty(const List* L) {
    return L->size == 0;
}

void list_add_first(List* L, Team* val) {
    Node* p = node_crete(val);
    p->next = L->begin;

    if (list_is_empty(L)) {
        L->end = p;
    }
    else {
        L->begin->prev = p;
    }

    // list_is_empty(L) ? (L->end = p) : (L->begin->prev = p); 
    L->begin = p;
    L->size++;

}

void list_add_last(List* L, Team* val) {
    Node* p = node_crete(val);
    p->prev = L->end;

    if (list_is_empty(L)) {
        L->begin = p;
    }
    else {
        L->end->next = p;
    }

    // list_is_empty(L) ? (L->begin = p) : (L->end->prev = p);
    L->end = p;
    L->size++;
}

void list_print(const List* L) {
    Node* p = L->begin;

    printf("Numero de times: %lu\n", L->size);

    while (p != NULL) {
        Team* team = p->val;
        printf("  Team Name: %s\n", team->name);
        printf("  Stadium: %s\n", team->stadium);
        printf("  City: %s\n", team->city);

        if (team->n_players > 0) {
            printf("  Players:\n");
            for (unsigned int i = 0; i < team->n_players; i++) {
                Player* player = team->players[i];
                printf("    Player Name: %s\n", player->name);
                printf("    Position: %d\n", player->position);
                printf("    Age: %u\n", player->age);
                puts("");
            }
        }

        p = p->next;
        puts("");
        printf("|\nV\n\n");
    }

    if (L->end == NULL) {
        printf("List is empty\n");
    }
    else {
        printf("L->end = %s\n", L->end->val->name);
    }
    puts("");
}


void list_inverted_print(const List* L) {
    Node* p = L->end;

    printf("\nSize: %lu\n", L->size);
    printf("List of Teams (Inverted Order):\n");

    while (p != NULL) {
        Team* team = p->val;
        printf("Team Name: %s\n", team->name);
        printf("Stadium: %s\n", team->stadium);
        printf("City: %s\n", team->city);

        p = p->prev;
        puts("");
    }

    if (L->end == NULL) {
        printf("List is empty\n");
    }
    else {
        printf("L->begin = %s\n", L->begin->val->name);
    }
    puts("");
}

void List_remove(List* L, Team* val) {
    if (list_is_empty(L)) {
        return;
    }

    Node* p = L->begin;

    // caso 1: o elemento está na cabeça da lista
    if (L->begin->val == val) {
        L->begin = p->next;

        // a lista possui apenas um único elemento
        if (L->end == p) {
            L->end = NULL;
        }
        // a lista possui mais de um elemento
        else {
            L->begin->prev = NULL;
        }

        free(p);
        L->size--;
    }
    else {
        p = p->next;

        while (p != NULL) {
            if (p->val == val) {
                p->prev->next = p->next;
                // caso 3: o elemento está no final da lista
                if (L->end == p) {
                    L->end = p->prev;
                }
                // caso 2: o elemento está no meio da lista
                else {
                    p->next->prev = p->prev;
                }

                free(p);
                p = NULL;
                L->size--;
            }
            else {
                p = p->next;
            }
        }
    }
    free(val);
}

void check_empty_list(const List* L, const char* function_name) {
    if (list_is_empty(L)) {
        fprintf(stderr, "ERROR in '%s'\n", function_name);
        fprintf(stderr, "List is empty\n");
        exit(EXIT_FAILURE);
    }
}

size_t List_size(const List* L) {
    check_empty_list(L, "List_size");
    return L->size;
}

Team* List_first_val(const List* L) {
    check_empty_list(L, "List_first_val");
    return L->begin->val;
}

Team* List_last_val(const List* L) {
    check_empty_list(L, "List_last_val");
    return L->end->val;
}

Team* List_get_val(const List* L, int index) {
    check_empty_list(L, "List_get_val");

    if (index < 0 || index >= L->size) {
        fprintf(stderr, "ERROR in 'List_get_val'\n");
        fprintf(stderr, "invalid index: %d\n", index);
        fprintf(stderr, "Try an index within [0, %lu]\n", L->size - 1);
        exit(EXIT_FAILURE);
    }

    Node* p = L->begin;
    for (int i = 0; i != index; i++) {
        p = p->next;
    }

    return p->val;
}

void initialize_stats(Statistics* stats) {
    stats->goals_scored = 0;
    stats->goals_conceded = 0;
    stats->yellow_cards = 0;
    stats->red_cards = 0;
    stats->fouls = 0;
}

Championship* create_championship(unsigned int matches) {
    Championship* c = (Championship*)calloc(1, sizeof(Championship));
    c->matches = matches;
    c->rounds = 5; //log2(matches);
    c->list_teams = list_create();
    return c;
}

Team* create_team(Championship* c, const char* name, const char* stadium, const char* city, const char* coach) {
    Team* team = (Team*)calloc(1, sizeof(Team));
    team->players = (Player**)calloc(25, sizeof(Player*));
    team->name = strdup(name);
    team->stadium = strdup(stadium);
    team->city = strdup(city);
    team->coach = strdup(coach);
    team->n_players = 0;

    initialize_stats(&(team->stats));
    list_add_last(c->list_teams, team);

    return team;
}

List* get_champ_teams(Championship* c) {
    return c->list_teams;
}

void remove_team(List* L, Team* team) {
    return List_remove(L, team);
}

void add_player(Team* team, char* name, unsigned int age, Position position) {
    if (team->n_players >= 25) {
        printf("O time já possui 25 jogadores. Não é possível adicionar mais.\n");
        return;
    }

    Player* player = (Player*)calloc(1, sizeof(Player));
    player->name = strdup(name);
    player->age = age;
    player->position = position;

    initialize_stats(&(player->stats));

    team->players[team->n_players] = player;
    team->n_players++;
}

void remove_player(Team* team, Player* p) {
    int j;

    for (j = 0; j < team->n_players; j++) {
        if (team->players[j] == p) {
            break;
        }
    }

    if (j == team->n_players) {
        return;
    }

    free(team->players[j]);

    for (int i = j; i < team->n_players - 1; i++) {
        team->players[i] = team->players[i + 1];
    }

    team->n_players--;
}

Player* get_player(Team* team, const char* name) {
    for (int i = 0; i < team->n_players; i++) {
        if (strcmp(team->players[i]->name, name) == 0) {
            return team->players[i];
        }
    }
    return NULL;
}

Team* get_team(Championship* c, const char* name) {
    Node* p = c->list_teams->begin;

    while (p != NULL) {
        Team* team = p->val;
        if (strcmp(team->name, name) == 0) {
            return team;
        }
        p = p->next;
    }
    return NULL;
}

void remove_team_by_name(Championship* c, char* name) {
    Team* team = get_team(c, name);
    remove_team(c, team);
}