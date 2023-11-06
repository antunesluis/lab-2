#ifndef FOOTBALL_LEAGUE_H
#define FOOTBALL_LEAGUE_H

#include <stdbool.h>
#include <stddef.h>

#include "list.h"

typedef struct _statistics Statistics;
typedef struct _championship Championship;
typedef struct _team Team;
typedef struct _coache Coach;
typedef struct _player Player;
typedef struct _statistics Statistics;
typedef struct _doubly_linked_list DoublyLinkedList, List;

typedef enum {
    Goalkeeper,
    RightBack,
    LeftBack,
    Defender,
    Midfielder,
    Forward
} Position;

Team* create_team(Championship* c, const char* name, const char* stadium, const char* city);
Championship* create_championship(unsigned int matches);

char* get_team_name(Team* team);
char* get_team_stadium(Team* team);
char* get_team_city(Team* team);
List* get_champ_teams(Championship* c);

void add_coach(Team* team, const char* name);
void add_player(Team* team, char* name, unsigned int age, Position position);

#endif