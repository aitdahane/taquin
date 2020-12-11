#include "menu2.h"
#include "jeu.h"

void menu2(SDL_Surface *ecran)
{

    ///On cree l'ensemble des surfaces nécessaires--------------------------------------------------
    SDL_Surface* menu ;
    SDL_Surface* buttonHelp ;
    SDL_Surface* buttonClose ;
    SDL_Surface* easy;
    SDL_Surface* medium;
    SDL_Surface* hard;

    menu = IMG_Load("Images/menu2.jpg") ;
    buttonHelp = IMG_Load("Images/Options/help.png");
    buttonClose = IMG_Load("Images/Options/close.png");
    easy = IMG_Load("Images/Menu/easy.png");
    medium = IMG_Load("Images/Menu/medium.png");
    hard = IMG_Load("Images/Menu/hard.png");

    ///On positionne les surfaces---------------------------------------------------
    SDL_Rect positionMenu;
    SDL_Rect positionHelp;
    SDL_Rect positionClose;
    SDL_Rect positionEasy;
    SDL_Rect positionMedium;
    SDL_Rect positionHard;

    positionMenu.x = 0 ;
    positionMenu.y = 0 ;

    positionHelp.x = 0.5 * CELLULE ;
    positionHelp.y = 0.5 * CELLULE ;

    positionClose.x = 5.5 * CELLULE;
    positionClose.y = 0.5 * CELLULE;

    positionEasy.x = 2 * CELLULE ;
    positionEasy.y = 2 * CELLULE ;

    positionMedium.x = 2 * CELLULE ;
    positionMedium.y = 4 * CELLULE ;

    positionHard.x = 2 * CELLULE ;
    positionHard.y = 6 * CELLULE ;

    ///On colle les surfaces dans l'ecran----------------------------------------------------------
    SDL_BlitSurface(menu, NULL, ecran, &positionMenu) ;
    SDL_BlitSurface(buttonHelp, NULL, ecran, &positionHelp) ;
    SDL_BlitSurface(buttonClose, NULL, ecran, &positionClose) ;
    SDL_BlitSurface(easy, NULL, ecran, &positionEasy);
    SDL_BlitSurface(medium, NULL, ecran, &positionMedium);
    SDL_BlitSurface(hard, NULL, ecran, &positionHard);

    ///On met à jour l'ecran-----------------------------------------------------------
    SDL_Flip(ecran);

    ///On passe aux évènements------------------------------------------------------------
    int continuer = 0;
    float n, m;
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
                    break;
                }
                case SDL_MOUSEMOTION :
                {
                    m = event.motion.x / CELLULE;
                    n = event.motion.y / CELLULE;
                    if ((m >= 2) && (m <= 5) && (n == 2))
                    {
                        easy = IMG_Load("Images/Menu/easyHover.png") ;
                    }
                    else if ((m >= 2) && (m <= 5) && (n == 4))
                    {
                        medium = IMG_Load("Images/Menu/mediumHover.png") ;
                    }
                    else if ((m >= 2) && (m <= 5) && (n == 6))
                    {
                        hard = IMG_Load("Images/Menu/hardHover.png") ;
                    }
                    else if ((m >= 0.5) && (m <= 1.5) && (n >= 0.5) && (n <= 1.5))
                    {
                        buttonHelp = IMG_Load("Images/Options/helpHover.png");
                    }
                    else if ((m >= 5.5) && (m <= 6.5) && (n >= 0.5) && (n <= 1.5))
                    {
                        buttonClose = IMG_Load("Images/Options/closeHover.png");
                    }
                    else
                    {
                        buttonHelp = IMG_Load("Images/Options/help.png");
                        buttonClose = IMG_Load("Images/Options/close.png");
                        easy = IMG_Load("Images/Menu/easy.png");
                        medium = IMG_Load("Images/Menu/medium.png");
                        hard = IMG_Load("Images/Menu/hard.png");
                    }

                      SDL_BlitSurface(buttonHelp, NULL, ecran, &positionHelp) ;
                      SDL_BlitSurface(buttonClose, NULL, ecran, &positionClose) ;
                      SDL_BlitSurface(easy, NULL, ecran, &positionEasy);
                      SDL_BlitSurface(medium, NULL, ecran, &positionMedium);
                      SDL_BlitSurface(hard, NULL, ecran, &positionHard);
                }
                break ;
                case SDL_MOUSEBUTTONUP :
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        m = event.button.x / CELLULE;
                        n = event.button.y / CELLULE;
                        if ((m >= 2) && (m <= 5) && (n == 2))
                        {
                            jouer(ecran, 'f') ;
                            continuer = 1;

                        }
                        else if ((m >= 2) && (m <= 5) && (n == 4))
                        {
                            jouer(ecran, 'm');
                            continuer = 1;


                        }
                        else if ((m >= 2) && (m <= 5) && (n == 6))
                        {
                            jouer(ecran, 'h');
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

    SDL_FreeSurface(menu);
    SDL_FreeSurface(buttonClose);
    SDL_FreeSurface(buttonHelp);
    SDL_FreeSurface(easy);
    SDL_FreeSurface(medium);
    SDL_FreeSurface(hard);

}
