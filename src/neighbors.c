#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "neighbors.h"
#include <limits.h>

struct links_t
{
  struct neighbors_t neighbors[WORLD_SIZE];
};

struct links_t links;

void init_links(struct links_t *lin)
{
  for (unsigned int k = 0; k < WORLD_SIZE; k++)
  {
    for (unsigned int j = 0; j < MAX_NEIGHBORS + 1; j++)
    {
      lin->neighbors[k].n[j].i = UINT_MAX;
      lin->neighbors[k].n[j].d = NO_DIR;
    }
  }
}

void init_standard(struct links_t *lin)
{
  int k;
  for (k = 0; k < WORLD_SIZE; k++)
  {
    int j = 0;
    if (k % WIDTH != WIDTH - 1) // EAST
    {
      lin->neighbors[k].n[j].i = k + 1;
      lin->neighbors[k].n[j].d = 1;
      j++;
      if (k > WIDTH - 1) // NEAST
      {
        lin->neighbors[k].n[j].i = k - WIDTH + 1;
        lin->neighbors[k].n[j].d = 2;
        j++;
      }
      if (k < WORLD_SIZE - WIDTH) // SEAST
      {
        lin->neighbors[k].n[j].i = k + WIDTH + 1;
        lin->neighbors[k].n[j].d = -4;
        j++;
      }
    }
    if (k % WIDTH != 0) // WEST
    {
      lin->neighbors[k].n[j].i = k - 1;
      lin->neighbors[k].n[j].d = -1;
      j++;
      if (k > WIDTH - 1) // NWEST
      {
        lin->neighbors[k].n[j].i = k - WIDTH - 1;
        lin->neighbors[k].n[j].d = 4;
        j++;
      }
      if (k < WORLD_SIZE - WIDTH) // SWEST
      {
        lin->neighbors[k].n[j].i = k + WIDTH - 1;
        lin->neighbors[k].n[j].d = -2;
        j++;
      }
    }
    if (k < WORLD_SIZE - WIDTH) // SOUTH
    {
      lin->neighbors[k].n[j].i = k + WIDTH;
      lin->neighbors[k].n[j].d = -3;
      j++;
    }
    if (k > WIDTH - 1) // NORTH
    {
      lin->neighbors[k].n[j].i = k - WIDTH;
      lin->neighbors[k].n[j].d = 3;
      j++;
    }
  }
}

void up_triangle(struct links_t *relations, unsigned int extra)
{
  unsigned int k, l, limit, start, end;
  limit = WIDTH - extra;
  for (l = 0; l < limit; l++)
  {
    start = (l + extra) * WIDTH + l;
    end = (l + extra) * WIDTH + limit - 1;
    for (k = start; k < end + 1; k++)
    {
      int j = 0;
      if (k != end) // EAST & SEAST
      {
        relations->neighbors[k].n[j].i = k + 1;
        relations->neighbors[k].n[j].d = 1;
        j++;
        relations->neighbors[k].n[j].i = k + WIDTH + 1;
        relations->neighbors[k].n[j].d = -4;
        j++;
      }
      if (k != start) // WEST & SOUTH
      {
        relations->neighbors[k].n[j].i = k - 1;
        relations->neighbors[k].n[j].d = -1;
        j++;
        relations->neighbors[k].n[j].i = k + WIDTH;
        relations->neighbors[k].n[j].d = -3;
        j++;
      }
      if (l != 0) // NWEST & NORTH
      {
        relations->neighbors[k].n[j].i = k - WIDTH - 1;
        relations->neighbors[k].n[j].d = 4;
        j++;
        relations->neighbors[k].n[j].i = k - WIDTH;
        relations->neighbors[k].n[j].d = 3;
        j++;
      }
    }
  }
}

void down_triangle(struct links_t *relations, unsigned int extra)
{
  unsigned int k, l, limit, start, end;
  limit = WIDTH - extra;
  for (l = 0; l < limit; l++)
  {
    start = l * WIDTH + extra;
    end = start + l;
    for (k = start; k < end + 1; k++)
    {
      int j = 0;
      if (l != limit - 1) // SOUTH & SEAST
      {
        relations->neighbors[k].n[j].i = k + WIDTH;
        relations->neighbors[k].n[j].d = -3;
        j++;
        relations->neighbors[k].n[j].i = k + WIDTH + 1;
        relations->neighbors[k].n[j].d = -4;
        j++;
      }
      if (k != start) // WEST & NWEST
      {
        relations->neighbors[k].n[j].i = k - 1;
        relations->neighbors[k].n[j].d = -1;
        j++;
        relations->neighbors[k].n[j].i = k - WIDTH - 1;
        relations->neighbors[k].n[j].d = 4;
        j++;
      }
      if (k != end) // EAST & NORTH
      {
        relations->neighbors[k].n[j].i = k + 1;
        relations->neighbors[k].n[j].d = 1;
        j++;
        relations->neighbors[k].n[j].i = k - WIDTH;
        relations->neighbors[k].n[j].d = 3;
        j++;
      }
    }
  }
}

int already_exists(struct vector_t vect, struct neighbors_t list)
{
  unsigned int j = 0;
  while (list.n[j].i != UINT_MAX)
  {
    if ((list.n[j].i == vect.i) && (list.n[j].d == vect.d))
      return 1;
    j++;
  }
  return 0;
}

void add_neighbor(struct vector_t vect, struct neighbors_t *list)
{
  unsigned int j = 0;
  while (list->n[j].i != UINT_MAX)
  {
    j++;
  }
  list->n[j].i = vect.i;
  list->n[j].d = vect.d;
}

void star_shape(struct links_t *a, struct links_t *b)
{
  unsigned int k, j;
  for (k = 0; k < WORLD_SIZE; k++)
  {
    j = 0;
    while (b->neighbors[k].n[j].i != UINT_MAX)
    {
      if (!already_exists(b->neighbors[k].n[j], a->neighbors[k]))
        add_neighbor(b->neighbors[k].n[j], &(a->neighbors[k]));
      j++;
    }
  }
}

void cylindrical_shape(struct links_t *lin)
{
  init_standard(lin);
  struct vector_t vect_n;
  vect_n.d = 3;
  struct vector_t vect_ne;
  vect_ne.d = 2;
  struct vector_t vect_nw;
  vect_nw.d = 4;
  struct vector_t vect_s;
  vect_s.d = -3;
  struct vector_t vect_se;
  vect_se.d = -4;
  struct vector_t vect_sw;
  vect_sw.d = -2;
  for (unsigned int k = 0; k < WIDTH; k++)
  {
    // NORTH
    vect_n.i = WORLD_SIZE - WIDTH + k;
    add_neighbor(vect_n, &(lin->neighbors[k]));
    // NEAST
    if (k != WIDTH - 1)
    {
      vect_ne.i = WORLD_SIZE - WIDTH + k + 1;
      add_neighbor(vect_ne, &(lin->neighbors[k]));
    }
    // NWEST
    if (k != 0)
    {
      vect_nw.i = WORLD_SIZE - WIDTH + k - 1;
      add_neighbor(vect_nw, &(lin->neighbors[k]));
    }

    unsigned int idx = WORLD_SIZE - WIDTH + k;
    // SOUTH
    vect_s.i = k;
    add_neighbor(vect_s, &(lin->neighbors[idx]));
    // SEAST
    if (k != WIDTH - 1)
    {
      vect_se.i = k + 1;
      add_neighbor(vect_se, &(lin->neighbors[idx]));
    }
    // SWEST
    if (k != 0)
    {
      vect_sw.i = k - 1;
      add_neighbor(vect_sw, &(lin->neighbors[idx]));
    }
  }
}

void init_neighbors(unsigned int seed)
{
  init_links(&links);
  switch (seed)
  {
  case 0:
  case 1:

    init_standard(&links);
    break;
  case 2:
  case 3:
    if ((((WIDTH - 1) % 4) == 0) && (WIDTH == HEIGHT))
    {
      unsigned int extra = (WIDTH - 1) / 4;
      up_triangle(&links, extra);
      struct links_t relations;
      init_links(&relations);
      down_triangle(&relations, extra);
      star_shape(&links, &relations);
    }
    break;
  case 4:
  case 5:
    cylindrical_shape(&links);
  }
}

unsigned int get_neighbor(unsigned int idx, enum dir_t d)
{
  int k = 0;
  while (links.neighbors[idx].n[k].i != UINT_MAX)
  {
    if (links.neighbors[idx].n[k].d == d)
    {
      return links.neighbors[idx].n[k].i;
    }
    k++;
  }
  return links.neighbors[idx].n[k].i;
}

struct neighbors_t get_neighbors(unsigned int idx)
{
  return links.neighbors[idx];
}
