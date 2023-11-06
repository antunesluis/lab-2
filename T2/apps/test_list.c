#include "list.h"
#include "football_league.h"
#include <stdio.h>


int main() {

    printf("aaiiiiiiiiii\n");

    Championship* c = create_championship(8);
    Team* temp = create_team(c, "ijk", "lmn", "opq");
    add_coach(temp, "jorjao");
    add_player(temp, "rodrigo", 20, 3);
    List* teams = get_champ_teams(c);
    List_print(teams);

    Team* temp2 = create_team(c, "abc", "dce", "fgh");
    add_coach(temp2, "jorjao2");
    add_player(temp2, "rodrigo2", 202, 32);
    List_print(teams);

    return 0;
}