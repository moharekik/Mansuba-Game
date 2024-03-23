#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "ploop.h"

int main()
{
    srand(time(NULL));
    if (((SEED == 2) || (SEED == 3)) && ((((WIDTH - 1) % 4) != 0) || (WIDTH != HEIGHT)))
        printf("pour la grille triangulaire il faut que WIDTH-1 soit un multiple de 4 et le plateau soit carré !\n");
    else
    {
        init_neighbors(SEED);
        unsigned int nb_turns = 0;
        struct world_t *w = world_init();
        init_game(SEED, w);
        enum color_t current_player = get_random_player();
        unsigned int p;
        struct move_t m;
        show(w);
        while (!has_won(SEED, next_player(current_player), w) && nb_turns < MAX_TURNS)
        {
            p = choose_random_piece_belonging_to(w, current_player);
            printf("Le joueur %d a choisi la position %d\n", current_player, p);
            m = choose_random_move_for_piece(w, p);
            if (m.e != -1)
            {
                move_piece(w, m, current_player, world_get_sort(w, m.s));
                printf("  et passe à la position %d\n", m.e);
            }
            else
                printf("  mais la pièce est bloquée\n");
            current_player = next_player(current_player);
            nb_turns++;
            show(w);
        }
        if (nb_turns == MAX_TURNS)
            printf("\033[%dmégalité\033[m\n", 93);
        else
            printf("\033[%dmle vainqueur est le joueur %d en %d tours\033[m\n", 92, next_player(current_player), nb_turns);
    }
    return 0;
}
