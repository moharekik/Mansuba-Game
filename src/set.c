#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "set.h"

void init_nb_positions(struct set_t *s)
{
  s->nb_positions = 0;
}

void add_position(struct set_t *s, int pos)
{
  s->positions[s->nb_positions] = pos;
  s->nb_positions++;
}

void init_initial_positions(struct set_t *s1, struct set_t *s2)
{
  int i;
  init_nb_positions(s1);
  init_nb_positions(s2);
  for (i = 0; i < HEIGHT; i++)
  {
    add_position(s1, WIDTH * i);
    add_position(s2, WIDTH * i + WIDTH - 1);
  }
}

void init_initial_positions_triangular(struct set_t *s1, struct set_t *s2)
{
  init_nb_positions(s1);
  init_nb_positions(s2);
  unsigned int extra = (WIDTH - 1) / 4;
  unsigned int t1, t2, l, d;
  d = WIDTH - 2 * extra;
  for (l = 0; l < extra; l++)
  {
    t1 = extra + l * WIDTH;
    for (unsigned int k = 0; k < l + 1; k++)
    {
      add_position(s1, t1);                   // initial positions for the 1st small triangle player 1
      add_position(s1, t1 + d * WIDTH);       // initial positions for the 3rd small triangle player 1
      add_position(s2, t1 + d * (WIDTH + 1)); // initial positions for the 2nd small triangle player 2
      t1++;
    }
    t2 = (extra + l) * WIDTH + l;
    for (unsigned int k = extra - l; k > 0; k--)
    {
      add_position(s1, t2);                   // initial oositions for the 2nd small triangle player 1
      add_position(s2, t2 + d);               // initial oositions for the 1st small triangle player 2
      add_position(s2, t2 + d * (WIDTH + 1)); // initial oositions for the 3rd small triangle player 2
      t2++;
    }
  }
}

struct set_t all_positions()
{
  struct set_t positions;
  init_nb_positions(&positions);
  for (unsigned int i = 0; i < WORLD_SIZE; i++)
  {
    struct neighbors_t nei = get_neighbors(i);
    if (nei.n[0].i != UINT_MAX)
      add_position(&positions, i);
  }
  return positions;
}