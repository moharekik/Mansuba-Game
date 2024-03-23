#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "ploop.h"

int test_geometry(enum dir_t d, enum color_t c, enum sort_t s)
{
  printf("tests de geometry.c\n");
  const char *result1 = dir_to_string(d);
  printf("%d signifie %s\n", d, result1);
  const char *result2 = place_to_string(c, s);
  printf("%d et %d signifient %s\n", c, s, result2);
  return 0;
}

int test_world(unsigned int idx, enum color_t c, enum sort_t s)
{
  printf("\ntests de world.c\n");
  struct world_t *pw = world_init();
  // tests de world_set et world_set_sort
  world_set(pw, idx, c);
  world_set_sort(pw, idx, s);
  // tests de world_get
  enum color_t c0 = world_get(pw, idx);
  enum sort_t s0 = world_get_sort(pw, idx);
  printf("l'état de la case %d est %d\n", idx, s0);
  printf("la couleur de la case %d est %d\n", idx, c0);
  return 0;
}

int test_neighbor(unsigned int idx, enum dir_t d)
{
  printf("\ntest de get_neighbor\n");
  unsigned int n = get_neighbor(idx, d);
  printf("le voisin de %d dans la direction %d est %d\n", idx, d, n);
  return 0;
}

int test_neighbors(unsigned int idx)
{
  printf("\ntests de get_neighbors\n");
  struct neighbors_t neigh_idx = get_neighbors(idx);
  printf("pour la position %d\n", idx);
  int k = 0;
  while (neigh_idx.n[k].i != UINT_MAX)
  {
    printf("il y a un voisin en %d dans la direction %d\n", neigh_idx.n[k].i, neigh_idx.n[k].d);
    k++;
  }
  return 0;
}

int test_set(struct set_t *p1, struct set_t *p2)
{
  printf("\ntest de set\n");
  init_initial_positions(p1, p2);
  unsigned int n1 = p1->nb_positions;
  printf("p1 a %u positions de départ\n", n1);
  for (unsigned int i = 0; i < n1; i++)
  {
    printf("%u\n", p1->positions[i]);
  }
  printf("\n");
  unsigned int n2 = p2->nb_positions;
  printf("p2 a %u positions de départ\n", n2);
  for (unsigned int i = 0; i < n2; i++)
  {
    printf("%u\n", p2->positions[i]);
  }
  return 0;
}

int test_moves(unsigned int idx, struct world_t *w, struct set_t *m)
{
  printf("\ntest de moves\n");
  moves(idx, w, m, 1); // adapté aux pions
  if (m->nb_positions == 0)
    printf("Pas de déplacement possible\n");
  else
  {
    printf("Déplacement possible vers :\n");
    for (unsigned int k = 0; k < m->nb_positions; k++)
      printf("%d\n", m->positions[k]);
  }
  return 0;
}

int test_choice(int c)
{
  printf("\ntest de choice\n");
  struct set_pair p = initial_set_choice(c);
  test_set(&(p.s1), &(p.s2));
  return 0;
}

int test_has_won(int g, enum color_t c, struct world_t *w)
{
  printf("\ntest de choice\n");
  int result = has_won(g, c, w);
  if (result)
    printf("le joueur p%d a gagné\n", c);
  else
    printf("le joueur p%d n'a pas gagné\n", c);
  return 0;
}

int test_next_player(enum color_t c)
{
  printf("\ntest de next_player\n");
  enum color_t np = next_player(c);
  printf("current player is %d\n", c);
  printf("next player is %d\n", np);
  return 0;
}

int test_random_piece(struct world_t *w, enum color_t c)
{
  printf("\ntest de random_piece\n");
  unsigned int p = choose_random_piece_belonging_to(w, c);
  printf("on choisit aléatoirement le pion en case %d", p);
  return 0;
}

int test_random_move(struct world_t *w, unsigned int p)
{
  printf("\ntest de random_move\n");
  struct move_t m = choose_random_move_for_piece(w, p);
  printf("on part de %d et on arrive en %d\n", m.s, m.e);
  return 0;
}

int test_move_piece(struct world_t *w, struct move_t m, enum color_t c, enum sort_t s)
{
  printf("\ntest de move_piece\n");
  printf("état initiale : en %d %s et en %d %s\n", m.s, place_to_string(world_get(w, m.s), world_get_sort(w, m.s)), m.e, place_to_string(world_get(w, m.e), world_get_sort(w, m.e)));
  move_piece(w, m, c, s);
  printf("état initiale : en %d %s et en %d %s\n", m.s, place_to_string(world_get(w, m.s), world_get_sort(w, m.s)), m.e, place_to_string(world_get(w, m.e), world_get_sort(w, m.e)));
  return 0;
}

int test_random_player()
{
  printf("\ntest de random_player\n");
  int i;
  for (i = 0; i < 5; i++)
  {
    enum color_t p = get_random_player();
    printf("le joueur aléatoire est %d\n", p);
  }
  return 0;
}

int test_rand()
{
  srand(time(NULL));
  printf("\ntest de rand\n");
  int n;
  int i;
  for (i = 0; i < 100; i++)
  {
    n = rand() % 20 + 1;
    printf("%d\n", n);
  }
  return 0;
}

int test_moves_tower(unsigned int idx, struct world_t *w)
{
  printf("\ntest de moves_tower\n");
  struct set_t m;
  moves_tower(idx, w, &m);
  printf("les coups possibles à partir de %d sont :\n", idx);
  for (unsigned int i = 0; i < m.nb_positions; i++)
  {
    printf("%d\n", m.positions[i]);
  }
  return 0;
}

int test_moves_elephant(unsigned int idx, struct world_t *w)
{
  printf("\ntest de moves_elephant\n");
  struct set_t m;
  moves_elephant(idx, w, &m);
  printf("les coups possibles pour un éléphant à partir de %d sont :\n", idx);
  for (unsigned int i = 0; i < m.nb_positions; i++)
  {
    printf("%d\n", m.positions[i]);
  }
  return 0;
}

int test_nouveau_moves(unsigned int idx, struct world_t *w)
{
  printf("\ntest de la nouvelle version de moves\n");
  printf("pour une pièce de la case %d\n", idx);
  struct set_t mp;
  struct set_t mt;
  struct set_t me;
  init_nb_positions(&mp);
  init_nb_positions(&mt);
  init_nb_positions(&me);
  moves(idx, w, &mp, 1);
  moves(idx, w, &mt, 2);
  moves(idx, w, &me, 3);
  printf("pour un pion :\n");
  for (unsigned int i = 0; i < mp.nb_positions; i++)
  {
    printf("%d\n", mp.positions[i]);
  }
  printf("pour une tour :\n");
  for (unsigned int i = 0; i < mt.nb_positions; i++)
  {
    printf("%d\n", mt.positions[i]);
  }
  printf("pour un éléphant :\n");
  for (unsigned int i = 0; i < me.nb_positions; i++)
  {
    printf("%d\n", me.positions[i]);
  }
  return 0;
}

int main()
{
  init_neighbors(0);
  unsigned int idx = 12;
  enum sort_t s = PAWN;
  enum color_t c = BLACK;
  enum dir_t d = SOUTH;
  test_geometry(d, c, s);
  test_world(idx, c, s);
  test_neighbors(idx);
  // tets de set
  struct set_t p1;
  struct set_t p2;
  test_set(&p1, &p2);
  // test de moves
  struct world_t *pw = world_init();
  world_set_sort(pw, idx, s);
  world_set(pw, idx, c);
  world_set_sort(pw, 7, s);
  world_set(pw, 7, c);
  struct set_t m;
  init_nb_positions(&m);
  test_moves(idx, pw, &m);
  test_choice(0);
  test_has_won(0, c, pw);
  test_next_player(c);
  test_random_piece(pw, c);
  test_random_move(pw, idx);
  struct move_t sm;
  sm.s = idx;
  sm.e = 13;
  move_piece(pw, sm, c, s);
  test_random_player();
  // test_rand();
  // test de moves_tower
  struct world_t *pw2 = world_init();
  world_set_sort(pw2, 7, s);
  world_set(pw2, 7, c);
  world_set_sort(pw2, 12, s);
  world_set(pw2, 12, c);

  test_moves_tower(idx, pw2);
  // test de moves_elephant
  test_moves_elephant(idx, pw2);
  test_nouveau_moves(idx, pw2);
  return 0;
}
