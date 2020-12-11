#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <SDL/SDL.h>
#include <SDL_image.h>
#include "constantes.h"
#include "menu-1.h"


int main ( int argc, char** argv )
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* icon = IMG_Load("images/cases/0.jpg");

    SDL_Surface* ecran = SDL_SetVideoMode(L , H, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetIcon(icon, NULL);
    SDL_WM_SetCaption("Taquin interactif", NULL);

    menu1(ecran);

    SDL_FreeSurface(icon);
    SDL_FreeSurface(ecran);

    return 0;
}
