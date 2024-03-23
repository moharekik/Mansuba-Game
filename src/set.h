#ifndef __SET_H__
#define __SET_H_

#include "world.h"
#include "neighbors.h"

/* Global structure useful for initial positions, potential moves for each pawn, pawns available for each player*/
struct set_t
{
  unsigned int positions[WORLD_SIZE];
  unsigned int nb_positions;
};

/* initialisation of number of positions */
void init_nb_positions(struct set_t *s);

/* add a position in the list of positions */
void add_position(struct set_t *s, int pos);

/* initialisation of initial for a standard game positions p1 and p2 */
void init_initial_positions(struct set_t *s1, struct set_t *s2);

/* initialisation of initial for a triangular game positions p1 and p2 */
void init_initial_positions_triangular(struct set_t *s1, struct set_t *s2);

/* returns the possible destinations for a pawn*/
void moves(unsigned int idx, struct world_t *w, struct set_t *m, enum sort_t s);

/* useful for initial_set_choice in project */
struct set_pair
{
  struct set_t s1;
  struct set_t s2;
};

/* duo of positions: start and end, useful for final loop */
struct move_t
{
  unsigned int s;
  int e;
};

/*moves for a tower*/
void moves_tower(unsigned int idx, struct world_t *w, struct set_t *m);

/*moves for an elephant*/
void moves_elephant(unsigned int idx, struct world_t *w, struct set_t *m);

/* to see if the int exists in set or not */
int is_in_set(struct set_t m, unsigned int idx);

/* to get all allowed positions */
struct set_t all_positions();

#endif // __SET_H__
