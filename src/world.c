#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "world.h"

struct space
{
  enum color_t color;
  enum sort_t sort;
};

struct world_t
{
  struct space board[WORLD_SIZE];
};

struct world_t *world_init()
{
  static struct world_t world;
  int i = 0;
  while (i < WORLD_SIZE)
  {
    world.board[i].color = 0;
    world.board[i].sort = 0;
    i++;
  }
  return &world;
}

enum color_t world_get(const struct world_t *b, unsigned int idx)
{
  return b->board[idx].color;
}

void world_set(struct world_t *b, unsigned int idx, enum color_t c)
{
  b->board[idx].color = c;
}

enum sort_t world_get_sort(const struct world_t *b, unsigned int idx)
{
  return b->board[idx].sort;
}

void world_set_sort(struct world_t *b, unsigned int idx, enum sort_t s)
{
  b->board[idx].sort = s;
}
