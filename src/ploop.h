#ifndef __PROJECT_H__
#define __PROJECT_H__

#include "set.h"

/** The Seed defines what kind of game we  play */
#ifndef SEED
#define SEED 0
#endif

/* the number of turns before a draw */
#define MAX_TURNS (2 * WORLD_SIZE)

/* tells the initials sets of positions for the type of rules chosen */
struct set_pair initial_set_choice(int c);

/* tells if the player who just played has won the game */
int has_won(int g, enum color_t c, struct world_t *w);

enum color_t next_player(enum color_t c);

unsigned int choose_random_piece_belonging_to(struct world_t *w, enum color_t c);

struct move_t choose_random_move_for_piece(struct world_t *w, unsigned int p);

void move_piece(struct world_t *w, struct move_t m, enum color_t c, enum sort_t s);

enum color_t get_random_player();

void init_game(int g, struct world_t *w);

int show(struct world_t *w);

#endif // __PROJECT_H__