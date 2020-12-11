#include "menu-1.h"
#include "jeu.h"

void menu1(SDL_Surface *ecran)
{

    /// On cree l'ensemble des surfaces n�cessaires
    SDL_Surface* menu;
    SDL_Surface* buttonPlay;
    SDL_Surface* buttonHelp;
    SDL_Surface* buttonClose;

    menu = IMG_Load("images/menu-1.jpg") ;
    buttonPlay = IMG_Load("images/options/play.png") ;
    buttonHelp = IMG_Load("images/options/help.png");
    buttonClose = IMG_Load("images/options/close.png");

    /// On positionne les surfaces
    SDL_Rect positionMenu;
    SDL_Rect positionPlay;
    SDL_Rect positionHelp;
    SDL_Rect positionClose;

    positionMenu.x = 0 ;
    positionMenu.y = 0 ;
    positionPlay.x = 2 * CELLULE ;
    positionPlay.y = 6 * CELLULE ;
    positionHelp.x = 0.5 * CELLULE ;
    positionHelp.y = 0.5 * CELLULE ;
    positionClose.x = 5.5 * CELLULE;
    positionClose.y = 0.5 * CELLULE;

    ///On colle les surfaces dans l'ecran
    SDL_BlitSurface(menu, NULL, ecran, &positionMenu) ;
    SDL_BlitSurface(buttonPlay, NULL, ecran, &positionPlay) ;
    SDL_BlitSurface(buttonHelp, NULL, ecran, &positionHelp) ;
    SDL_BlitSurface(buttonClose, NULL, ecran, &positionClose) ;

    ///On met � jour l'ecran
    SDL_Flip(ecran) ;

    ///On passe aux �v�nements
    float m, n;
    int continuer = 0;
    while (!continuer)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    continuer = 1;
                    break;
                }
                case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        continuer = 1;

                }
                break;
                case SDL_MOUSEMOTION :
                {
                    m = event.motion.x / CELLULE;
                    n = event.motion.y / CELLULE;
                    if ((m >= 2) && (m <= 5) && (n >= 6) && (n <= 7))
                    {
                        buttonPlay = IMG_Load("images/play-hover.png") ;
                    }
                    else if ((m >= 0.5) && (m <= 1.5) && (n >= 0.5) && (n <= 1.5))
                    {
                        buttonHelp = IMG_Load("images/options/help-hover.png");
                    }
                    else if ((m >= 5.5) && (m <= 6.5) && (n >= 0.5) && (n <= 1.5))
                    {
                        buttonClose = IMG_Load("images/options/close-hover.png");
                    }
                    else
                    {
                        buttonPlay = IMG_Load("images/play.png") ;
                        buttonHelp = IMG_Load("images/options/help.png");
                        buttonClose = IMG_Load("images/options/close.png");
                    }
                    SDL_BlitSurface(buttonPlay, NULL, ecran, &positionPlay) ;
                    SDL_BlitSurface(buttonHelp, NULL, ecran, &positionHelp) ;
                    SDL_BlitSurface(buttonClose, NULL, ecran, &positionClose) ;
                }
                break ;
                case SDL_MOUSEBUTTONUP :
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        m = event.button.x / CELLULE;
                        n = event.button.y / CELLULE;
                        if ((m >= 2) && (m <= 5) && (n >= 6) && (n <= 7))
                        {
                            menu2(ecran) ;
                            continuer = 1;
                        }
                        else if ((m >= 5.5) && (m <= 6.5) && (n >= 0.5) && (n <= 1.5))
                        {
                            continuer = 1;
                        }
                    }
                }
                break;
            }
        }
        SDL_Flip(ecran);
    }

    ///On lib�re les surfaces
    SDL_FreeSurface(menu);
    SDL_FreeSurface(buttonPlay);
    SDL_FreeSurface(buttonHelp);
    SDL_FreeSurface(buttonClose);
}
