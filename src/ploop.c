#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "neighbors.h"
#include "ploop.h"

struct set_pair initial_set_choice(int g)
{
    struct set_pair p;
    switch (g)
    {
    case 0:
    case 1:
    case 4:
    case 5:
        init_initial_positions(&(p.s1), &(p.s2));
        break;
    case 2:
    case 3:
        init_initial_positions_triangular(&(p.s1), &(p.s2));
    }
    return p;
}

int has_won(int g, enum color_t c, struct world_t *w)
{
    struct set_pair p = initial_set_choice(g);
    int npi = p.s1.nb_positions;
    switch (g)
    {
    case 0:
    case 2:
    case 4:

        if (c == BLACK)
        {
            for (int i = 0; i < npi; i++)
            {
                if (world_get(w, p.s2.positions[i]) == BLACK)
                    return 1;
            }
        }
        if (c == WHITE)
        {
            for (int i = 0; i < npi; i++)
            {
                if (world_get(w, p.s1.positions[i]) == WHITE)
                    return 1;
            }
        }
        break;
    case 1:
    case 3:
    case 5:

        if (c == BLACK)
        {
            for (int i = 0; i < npi; i++)
            {
                if (world_get(w, p.s2.positions[i]) != BLACK)
                    return 0;
            }
            return 1;
        }
        if (c == WHITE)
        {
            for (int i = 0; i < npi; i++)
            {
                if (world_get(w, p.s1.positions[i]) != WHITE)
                    return 0;
            }
            return 1;
        }
        break;
    }
    return 0;
}
enum color_t get_random_player()
{
    enum color_t n = rand() % 2 + 1;
    return n;
}

enum color_t next_player(enum color_t c)
{
    if (c == WHITE)
        return BLACK;
    else
        return WHITE;
}

unsigned int choose_random_piece_belonging_to(struct world_t *w, enum color_t c)
{
    struct set_t pawns;
    init_nb_positions(&pawns);
    for (unsigned int i = 0; i < WORLD_SIZE; i++)
    {
        if (world_get(w, i) == c)
            add_position(&pawns, i);
    }
    int n = rand() % pawns.nb_positions;
    return pawns.positions[n];
}

void init_game(int g, struct world_t *w)
{
    struct set_pair sp = initial_set_choice(g);
    unsigned int i;
    for (i = 0; i < sp.s1.nb_positions; i++)
    {
        enum sort_t n = rand() % 3 + 1;
        world_set_sort(w, sp.s1.positions[i], n);
        world_set(w, sp.s1.positions[i], 1);
        world_set_sort(w, sp.s2.positions[i], n);
        world_set(w, sp.s2.positions[i], 2);
    }
}

struct move_t choose_random_move_for_piece(struct world_t *w, unsigned int p)
{
    struct move_t m;
    m.s = p;
    struct set_t sm;
    init_nb_positions(&sm);
    enum sort_t s = world_get_sort(w, p);
    moves(p, w, &sm, s);
    if (sm.nb_positions != 0)
    {
        int n = rand() % sm.nb_positions;
        m.e = sm.positions[n];
    }
    else
    {
        m.e = -1;
    }
    return m;
}

void move_piece(struct world_t *w, struct move_t m, enum color_t c, enum sort_t s)
{
    world_set_sort(w, m.e, s);
    world_set(w, m.e, c);
    world_set_sort(w, m.s, NO_SORT);
    world_set(w, m.s, NO_COLOR);
}

int show(struct world_t *w)
{
    printf("\n  ");
    struct set_t positions = all_positions();
    for (unsigned int i = 0; i < HEIGHT; i++)
    {
        for (unsigned int j = 0; j < WIDTH; j++)
        {
            unsigned int idx = i * WIDTH + j;
            if (!is_in_set(positions, idx))
                printf("   ");
            else
            {
                switch (world_get(w, idx))
                {
                case 0:
                    printf("..");
                    break;
                case 1:
                    if (world_get_sort(w, idx) == 1)
                        printf("\033[%dmP1\033[m", 91);
                    else if (world_get_sort(w, idx) == 2)
                        printf("\033[%dmT1\033[m", 91);
                    else
                        printf("\033[%dmE1\033[m", 91);
                    break;
                case 2:
                    if (world_get_sort(w, idx) == 1)
                        printf("\033[%dmP2\033[m", 94);
                    else if (world_get_sort(w, idx) == 2)
                        printf("\033[%dmT2\033[m", 94);
                    else
                        printf("\033[%dmE2\033[m", 94);
                    break;
                default:
                    break;
                }
                if (get_neighbor(idx, 1) != UINT_MAX)
                    printf("_");
            }
        }
        printf("\n  ");
        for (unsigned int k = 0; k < WIDTH; k++)
        {
            if (get_neighbor(i * WIDTH + k, -3) != UINT_MAX)
                printf("|");
            else
                printf(" ");
            if (get_neighbor(i * WIDTH + k, -4) != UINT_MAX)
                printf("\\");
            else
                printf(" ");
            if ((k != WIDTH - 1) && (get_neighbor(i * WIDTH + k + 1, -2) != UINT_MAX))
                printf("/");
            else
                printf(" ");
        }
        printf("\n  ");
        for (unsigned int k = 0; k < WIDTH; k++)
        {
            if (get_neighbor(i * WIDTH + k, -3) != UINT_MAX)
                printf("|");
            else
                printf(" ");
            if ((k != WIDTH - 1) && (get_neighbor(i * WIDTH + k + 1, -2) != UINT_MAX))
                printf("/");
            else
                printf(" ");
            if (get_neighbor(i * WIDTH + k, -4) != UINT_MAX)
                printf("\\");
            else
                printf(" ");
        }
        printf("\n  ");
    }
    printf("\n");
    return 0;
}
