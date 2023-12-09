#ifndef READ_TEAMS_H
#define READ_TEAMS_H

#include "championship.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    AddTeam,
    DeleteTeam,
    ShowTeams,
    AddPlayer,
    DeletePlayer,
    ShowTeamByPlayer,
    Exit
} MenuOption;

bool menu();
Team* read_team_data(Championship* c);
Player* read_player_data();
int read_player_position();
void add_team(Championship* c);

#endif
