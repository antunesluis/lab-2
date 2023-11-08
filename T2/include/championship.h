#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

#include <stdbool.h>
#include <stddef.h>

typedef enum {
    Goalkeeper,
    RightBack,
    LeftBack,
    Defender,
    Midfielder,
    Forward
} Position;

typedef struct _team Team;
typedef struct _statistics Statistics;
typedef struct _championship Championship;
typedef struct _team Team;
typedef struct _coache Coach;
typedef struct _player Player;
typedef struct _statistics Statistics;
typedef struct _doubly_node DoubliNode, Node;
typedef struct _doubly_linked_list DoublyLinkedList, List;

Node* node_crete(Team* val);
List* list_create();
void list_destroy(List** L_ref);
bool list_is_empty(const List* L);
void list_add_first(List* L, Team* val);
void list_add_last(List* L, Team* val);
void list_print(const List* L);
void list_inverted_print(const List* L);
void list_remove(List* L, Team* val);
size_t list_size(const List* L);
Team* list_first_val(const List* L);
Team* list_last_val(const List* L);
Team* list_get_val(const List* L, int index);


Championship* create_championship(unsigned int matches);
void add_coach(Team* team, const char* name);
void add_player(Team* team, char* name, unsigned int age, Position position);
void remove_team(List* L, Team* team);
void remove_team_by_name(Championship* c, char* name);
void remove_player(Team* team, Player* p);
List* get_champ_teams(Championship* c);
Team* create_team(Championship* c, const char* name, const char* stadium, const char* city, const char* coach);
Team* get_team(Championship* c, const char* name);
Player* get_player(Team* team, const char* name);


#endif