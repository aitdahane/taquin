#include "echec.h"


void echec(SDL_Surface *ecran)
{
    SDL_Surface *echec;
    SDL_Rect positionEchec;

    echec = IMG_Load("images/echec.png");
    positionEchec.x = 0;
    positionEchec.y = 0;

    SDL_BlitSurface(echec, NULL, ecran, &positionEchec);

    SDL_Flip(ecran);

    SDL_FreeSurface(echec);

}
