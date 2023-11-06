#include "football_league.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> 
#include <string.h>
#include <math.h>

typedef enum {
    Goalkeeper,
    RightBack,
    LeftBack,
    Defender,
    Midfielder,
    Forward
} Position;

typedef struct _coache {
    char* name;
} Coach;

typedef struct _player {
    Position position;
    Statistics stats;
    char* name;
    unsigned int age;
} Player;

typedef struct _team {
    Statistics stats;
    Player* players[25];
    Coach* coach;
    unsigned int n_players;
    char* name;
    char* stadium;
    char* city;
} Team;

typedef struct _championship {
    List* teams;
    unsigned int rounds;
    unsigned int matches;
} Championship;

typedef struct _statistics {
    unsigned int goals_scored;
    unsigned int goals_conceded;
    unsigned int yellow_cards;
    unsigned int red_cards;
    unsigned int fouls;
} Statistics;

Championship* create_championship(unsigned int matches) {
    Championship* c = (Championship*)calloc(1, sizeof(Championship));
    c->matches = matches;
    c->rounds = log2(matches);
    c->teams = List_create();
    return c;
}

void initialize_stats(Statistics* stats) {
    stats->goals_scored = 0;
    stats->goals_conceded = 0;
    stats->yellow_cards = 0;
    stats->red_cards = 0;
    stats->fouls = 0;
}

void create_team(Championship* c, const char* name, const char* stadium, const char* city) {
    Team* team = (Team*)calloc(1, sizeof(Team));
    team->name = strdup(name);
    team->stadium = strdup(stadium);
    team->city = strdup(city);
    team->n_players = 0;

    initialize_stats(&(team->stats));
    List_add_last(c, team);
}

void create_player(Team* team, char* name, unsigned int age, Position position) {
    Player* player = (Player*)calloc(1, sizeof(Player));
    player->name = strdup(name);
    player->age = age;
    player->position = position;

    initialize_stats(&(player->stats));

    if (team->n_players < 25) {
        team->players[team->n_players] = player;
        team->n_players++;
    }
}

void add_coach(Team* team, const char* name) {
    Coach* coach = (Coach*)calloc(1, sizeof(Coach));
    coach->name = strdup(name);

    team->coach = coach;
}