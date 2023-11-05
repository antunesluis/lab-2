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

typedef struct _team {
    char* name;
    char* stadium;
    char* city;
    Statistics stats;
} Team;

typedef struct _championship {
    List* teams;
    unsigned int rounds;
    unsigned int matches;
} Championship;

typedef struct _coache {
    char* name;
} Coach;

typedef struct _player {
    char* name;
    unsigned int age;
    Position position;
    Statistics stats;
} Player;

typedef struct _statistics {
    unsigned int goals_scored;
    unsigned int goals_conceded;
    unsigned int yellow_cards;
    unsigned int red_cards;
    unsigned int fouls;
} Statistics;

void create_championship(unsigned int matches, Championship* c) {
    c->matches = matches;
    c->rounds = log2(matches);
    c->teams = List_create();
    return c;
}