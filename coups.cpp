#include "coups.h"

void afficheNbCoups(SDL_Surface *ecran, int nbCoups)
{
    char coups[3] = "";

    SDL_Surface *texte;
    SDL_Surface *font;

    SDL_Rect positionNbCoups ;
    SDL_Rect positionSurface ;

    TTF_Init();
    TTF_Font *police = NULL;
    sprintf(coups, "%d", nbCoups);
    police = TTF_OpenFont("font/diwanltr.ttf", 50);
    SDL_Color couleurNoire = {255, 255, 170};
    texte = TTF_RenderText_Blended(police, coups, couleurNoire);
    font = IMG_Load("images/coups.jpg");

    positionNbCoups.x = 3.25 * CELLULE;
    positionNbCoups.y = 7.25 * CELLULE;

    positionSurface.x = 2.5 * CELLULE ;
    positionSurface.y = 7.8 * CELLULE;

    SDL_BlitSurface(font, NULL, ecran, &positionSurface);
    SDL_BlitSurface(texte, NULL, ecran, &positionNbCoups);

    SDL_Flip(ecran);

    TTF_CloseFont(police);
    TTF_Quit();
}
