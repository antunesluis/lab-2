#include "championship.h"
#include "read_teams.h"

#include <stdio.h>

int main() {
    Championship* C = create_championship();
    menu(C);

    return 0;
}