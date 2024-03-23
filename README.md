# Project Mansuba

Auteurs: Mohamed Rekik et Théodore Jankowiak

La page de spécification du projet :

<https://www.labri.fr/perso/renault/working/teaching/projets/2022-23-S5-Mansuba.php>

La page du projet sur la forge :

https://thor.enseirb-matmeca.fr/ruby/projects/projetss5

La page des projets en général :

<https://www.labri.fr/perso/renault/working/teaching/projets/projets.php>

## Options du Makefile

La commande de compilation est :
make [argument] [définition d'un paramétre]

Sans argument, c'est le programme principal qui compile uniquement avec les valeurs par défaut:
_ Les dimensions du plateau (WIDTH=5 et HEIGHT=4)
_ Type du jeu (SEED=0)

Les différents arguments possibles sont:
project: pour complier le programme principal
test: pour compiler le programme du test et l'exécuter à la fois
clean: pour supprimerles exécutables du programme principal et du test

Les différents paramétres que l'on peut définir à l'exécution sont :
WIDTH: pour spécifier le nombre des colonne du monde, c'est-à-dire la "largeur"
HEIGHT: pour spécifier le nombre de ligne du monde, c'est-à-dire la "hauteur"
SEED: pour choisir le type du jeu (
SEED=0 pour un plateau rectangulaire et une victoire simple
SEED=1 pour un plateau rectangulaire et une victoire complexe
SEED=2 pour un plateau triangulaire et une victoire simple
SEED=3 pour un plateau triangulaire et une victoire complexe
SEED=4 pour un plateau cylindrique et une victoire simple
SEED=5 pour un plateau cylindrique et une victoire complexe )

## Conditions:

Pour les plateaux triangulaires on doit avoir WIDTH = HEIGHT = 4\*k+1 avec k un entier naturel non nul; dans le cas contraire, un message d'erreur apparaît.

## Exemples

"make" ou "make project" compile le programme principal.
"make WIDTH=14 HEIGHT=9" ou "make project WIDTH=14 HEIGHT=9" compile le programme principal avec un plateau de largeur 14 et de hauteur 9.
"make WIDTH=14 HEIGHT=9 SEED=2" ou "make project WIDTH=14 HEIGHT=9 SEED=2" compile le programme principal avec un plateau de largeur 14 et de hauteur 9 pour le plateau triangulaire.
