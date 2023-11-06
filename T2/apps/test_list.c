#include "list.h"
#include "football_league.h"
#include <stdio.h>


int main() {

    printf("aaiiiiiiiiii\n");

    Championship* c = create_championship(8);
    Team* t1 = create_team(c, "ijk", "lmn", "opq");
    add_coach(t1, "jorjao");
    add_player(t1, "rodrigo", 20, 3);
    List* teams = get_champ_teams(c);

    Team* t2 = create_team(c, "abc", "dce", "fgh");
    add_coach(t2, "jorjao2");
    add_player(t2, "rodrigo2", 202, 32);
    List_print(teams);

    printf("\n----------Removendo time ijk\n");
    remove_team(teams, t1);
    List_print(teams);

    return 0;
}