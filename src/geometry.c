#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "geometry.h"

const char *place_to_string(enum color_t c, enum sort_t s)
{
  char *tab[3][2];
  tab[0][0] = "pas de pion : incolore";
  tab[1][1] = "pion : noir";
  tab[1][2] = "pion : blanc";
  if (tab[c][s] == NULL)
  {
    return "erreur";
  }
  return tab[c][s];
}

const char *dir_to_string(enum dir_t d)
{
  switch (d)
  {
  case 0:
    return "pas de direction";
    break;
  case 1:
    return "Est";
    break;
  case 2:
    return "Nord-Est";
    break;
  case 3:
    return "Nord";
    break;
  case 4:
    return "Nord-Ouest";
    break;
  case -1:
    return "Ouest";
    break;
  case -2:
    return "Sud-Ouest";
    break;
  case -3:
    return "Sud";
    break;
  case -4:
    return "Sud-Est";
    break;
  default:
    return "erreur";
  }
}
