#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED


#include "menu-2.h"
#include "a-etoile.h"
#include "victoire.h"
#include "echec.h"
#include "coups.h"
#include <SDL/SDL_ttf.h>

SDL_Rect genereTaquin(int *P, SDL_Surface *ecran, SDL_Surface **cellule);
int deplacementPossible(int a, int b, int a0, int b0);
void deplacer(int* m, int* n);
int estSolution(int *P);
void jouer(SDL_Surface *ecran, char mode);


#endif // JEU_H_INCLUDED
