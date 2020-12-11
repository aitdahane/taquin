#include "victoire.h"
#include "menu-2.h"


void victoire(SDL_Surface *ecran)
{
    SDL_Surface *victoire;
    SDL_Rect positionVictoire;

    victoire = IMG_Load("images/victoire.png");
    positionVictoire.x = 0;
    positionVictoire.y = 0;

    SDL_BlitSurface(victoire, NULL, ecran, &positionVictoire);

    SDL_Flip(ecran);

    SDL_FreeSurface(victoire);

}
