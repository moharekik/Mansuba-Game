#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "set.h"

int is_in_set(struct set_t m, unsigned int idx)
{
    unsigned int k = 0;
    while (k < m.nb_positions)
    {
        if (m.positions[k] == idx)
        {
            return 1;
        }
        k++;
    }
    return 0;
}

void simple_moves(struct set_t *m, struct world_t *w, struct neighbors_t nei)
{
    int k = 0;
    while (nei.n[k].i != UINT_MAX)
    {
        enum sort_t sort = world_get_sort(w, nei.n[k].i);
        if (sort == NO_SORT)
        {
            add_position(m, nei.n[k].i);
        }
        k++;
    }
}

void jumps(struct set_t *m, struct world_t *w, struct neighbors_t nei, unsigned int idx)
{
    unsigned int k = 0;
    while (nei.n[k].i != UINT_MAX)
    {
        enum sort_t sort = world_get_sort(w, nei.n[k].i);
        if (sort == PAWN)
        {
            unsigned int neighbor = get_neighbor(nei.n[k].i, nei.n[k].d);
            if (neighbor != UINT_MAX && world_get_sort(w, neighbor) == NO_SORT && neighbor != idx)
            {
                if (!is_in_set(*m, neighbor))
                {
                    add_position(m, neighbor);
                    struct neighbors_t neighbors = get_neighbors(neighbor);
                    jumps(m, w, neighbors, idx);
                }
            }
        }
        k++;
    }
}

/* research the possible moves of a tower for one direction*/
void moves_tower_one_dir(unsigned int idx, struct world_t *w, struct set_t *m, enum dir_t d)
{
    unsigned int nei = get_neighbor(idx, d);
    while ((nei != UINT_MAX))
    {
        if (world_get_sort(w, nei) == 0)
        {
            add_position(m, nei);
            nei = get_neighbor(nei, d);
        }
        else
            break;
    }
}

/* manages the moves for a tower*/

void moves_tower(unsigned int idx, struct world_t *w, struct set_t *m)
{
    int d;
    for (d = -3; d <= 3; d = d + 2)
    {
        moves_tower_one_dir(idx, w, m, d);
    }
}

/* manages the moves for an elephant */
void moves_elephant(unsigned int idx, struct world_t *w, struct set_t *m)
{
    int k;
    int d;
    int L[] = {-4, -2, 2, 4};
    for (k = 0; k < 4; k++)
    {
        d = L[k];
        unsigned int nei1 = get_neighbor(idx, d);
        if (nei1 != UINT_MAX)
        {
            unsigned int nei2 = get_neighbor(nei1, d);
            if (nei2 != UINT_MAX)
            {
                if (world_get_sort(w, nei2) == 0)
                    add_position(m, nei2);
            }
        }
    }
}

/* updates the possible moves, starting from one pawn in particular*/
void moves(unsigned int idx, struct world_t *w, struct set_t *m, enum sort_t s)
{
    if (s == 2)
        moves_tower(idx, w, m);
    else if (s == 3)
        moves_elephant(idx, w, m);
    else if (s == 1)
    {
        struct neighbors_t neighbors = get_neighbors(idx);
        simple_moves(m, w, neighbors);
        jumps(m, w, neighbors, idx);
    }
}
