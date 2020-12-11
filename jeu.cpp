#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "jeu.h"


void jouer(SDL_Surface *ecran, char mode)
{

    int nbCoups = 0;

    SDL_Surface *infini;
    SDL_Rect positionInfini;

    Etat etatInitial ;
    Etat etatFinal;
     //genereEtatInitial(&etatInitial, &etatFinal);
    etatInitial.M[0][0] = 2;
    etatInitial.M[0][1] = 8;
    etatInitial.M[0][2] = 3;
    etatInitial.M[1][0] = 1;
    etatInitial.M[1][1] = 6;
    etatInitial.M[1][2] = 4;
    etatInitial.M[2][0] = 7;
    etatInitial.M[2][1] = 0;
    etatInitial.M[2][2] = 5;
    etatInitial.g = 0;
    etatInitial.h = 4;

    etatFinal.M[0][0] = 1;
    etatFinal.M[0][1] = 2;
    etatFinal.M[0][2] = 3;
    etatFinal.M[1][0] = 8;
    etatFinal.M[1][1] = 0;
    etatFinal.M[1][2] = 4;
    etatFinal.M[2][0] = 7;
    etatFinal.M[2][1] = 6;
    etatFinal.M[2][2] = 5;

    //genereEtatInitial(&etatInitial, &etatFinal);

    int *P = (int*)(etatInitial.M) ;
    ///-----------------------------------------------------------
    SDL_Surface* menu ;
    SDL_Surface* buttonHelp ;
    SDL_Surface* buttonClose ;
    ///----------------------------------------------------------
    buttonHelp = IMG_Load("images/options/help.png");
    buttonClose = IMG_Load("images/options/close.png");
    ///----------------------------------------------------------
    SDL_Rect positionMenu;
    SDL_Rect positionHelp;
    SDL_Rect positionClose;
    ///-------------------------------------------------------------
    SDL_Surface *arrierePlan = IMG_Load("images/arriere-plan.jpg") ;
    SDL_Rect positionArrierePlan ;
    positionArrierePlan.x = 0 ;
    positionArrierePlan.y = 0 ;
    SDL_BlitSurface(arrierePlan, NULL, ecran, &positionArrierePlan);
    ///---------------------------------------------------------------
    ///---------------------------------------------------------------
    SDL_Surface *cellule[9] ;
    cellule[0] = IMG_Load("images/cases/0.jpg") ;
    cellule[1] = IMG_Load("images/cases/1.jpg") ;
    cellule[2] = IMG_Load("images/cases/2.jpg") ;
    cellule[3] = IMG_Load("images/cases/3.jpg") ;
    cellule[4] = IMG_Load("images/cases/4.jpg") ;
    cellule[5] = IMG_Load("images/cases/5.jpg") ;
    cellule[6] = IMG_Load("images/cases/6.jpg") ;
    cellule[7] = IMG_Load("images/cases/7.jpg") ;
    cellule[8] = IMG_Load("images/cases/8.jpg") ;
    SDL_Rect positionCellule ;
    ///-----------------------------------------------------------------
    positionMenu.x = 0 ;
    positionMenu.y = 0 ;

    positionHelp.x = 0.5 * CELLULE ;
    positionHelp.y = 0.5 * CELLULE ;

    positionClose.x = 5.5 * CELLULE;
    positionClose.y = 0.5 * CELLULE;
    ///--------------------------------------------------------------------
    SDL_Rect positionZero; /// On rep�re la case vide

    SDL_Rect positionActuel;

    positionZero = genereTaquin(P, ecran, cellule);

    if (mode == 'f')
    {
        infini = IMG_Load("images/mode/infini.png");
        positionInfini.x = 3 * CELLULE;
        positionInfini.y = 8 * CELLULE;
        SDL_BlitSurface(infini, NULL, ecran, &positionInfini);
    }

    else if (mode == 'm')
    {
        nbCoups = rechercheAetoile(etatInitial, etatFinal , genereSuccesseur );
        nbCoups *= 2;
        afficheNbCoups(ecran, nbCoups);

    }

    else if (mode == 'h')
    {
        nbCoups = rechercheAetoile(etatInitial, etatFinal , genereSuccesseur );
        afficheNbCoups(ecran, nbCoups);

    }

    SDL_Surface *taquinFinal = IMG_Load("images/but.jpg") ;
    SDL_Rect positionBut;
    positionBut.x = CELLULE * 2.5 ;
    positionBut.y = CELLULE * 5.5 ;
    SDL_BlitSurface(taquinFinal, NULL, ecran, &positionBut) ;

    SDL_Flip(ecran) ;


    int continuer = 0;
    int finPartie = 0;
    float n, m;
    int a, b, a0, b0;

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
                    if ((m >= 0.5) && (m <= 1.5) && (n >= 0.5) && (n <= 1.5))
                    {
                        buttonHelp = IMG_Load("images/options/help-hover.png");
                    }
                    else if ((m >= 5.5) && (m <= 6.5) && (n >= 0.5) && (n <= 1.5))
                    {
                        buttonClose = IMG_Load("images/options/close-hover.png");
                    }

                    else
                    {
                        buttonHelp = IMG_Load("images/options/help.png");
                        buttonClose = IMG_Load("images/options/close.png");


                    }

                      SDL_BlitSurface(buttonHelp, NULL, ecran, &positionHelp) ;
                      SDL_BlitSurface(buttonClose, NULL, ecran, &positionClose) ;

              }
                break ;
            case SDL_MOUSEBUTTONUP:
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        positionActuel.x = event.button.x;
                        positionActuel.y = event.button.y;
                        if ((positionActuel.x >= (2 * CELLULE)) && (positionActuel.x <= (5 * CELLULE)) && (positionActuel.y >= 2 * CELLULE) && (positionActuel.y <= (5 * CELLULE)))
                        {
                            a = (positionActuel.y - 2 * CELLULE) / CELLULE;
                            b = (positionActuel.x - 2 * CELLULE) / CELLULE;
                            a0 = (positionZero.y - 2 * CELLULE) / CELLULE;
                            b0 = (positionZero.x - 2 * CELLULE) / CELLULE;

                            if(deplacementPossible(a, b, a0, b0) && !(finPartie))
                            {
                                deplacer(&etatInitial.M[a][b], &etatInitial.M[a0][b0]);
                                if (mode == 'm' || mode == 'h')
                                {
                                    nbCoups--;
                                    afficheNbCoups(ecran, nbCoups);
                                }
                                positionZero = genereTaquin(P, ecran, cellule) ;

                                if (etatSolution(etatInitial, etatFinal))
                                {
                                    victoire(ecran);
                                    finPartie = 1;
                                }
                                else if (nbCoups < 0)
                                {
                                    echec(ecran);
                                    finPartie = 1;
                                }
                            }
                       }
                        else if ((m >= 5.5) && (m <= 6.5) && (n >= 0.5) && (n <= 1.5))
                        {
                            menu2(ecran);
                            continuer = 1;
                        }
                        break;
                    }
                }
            }
            SDL_Flip(ecran);
        }
    }
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

}

SDL_Rect genereTaquin(int *P, SDL_Surface *ecran, SDL_Surface **cellule)
{
    SDL_Rect pos;
    SDL_Rect positionZero;
    int i,j;
    for (i = 0; i < TAILLE; i++)
    {
        for(j = 0; j < TAILLE; j++)
        {
            pos.x = CELLULE * (2+j) ;
            pos.y = CELLULE * (2+i) ;
            SDL_BlitSurface(cellule[*(P+i*3+j)], NULL, ecran, &pos) ;
            if (*(P+i*3+j) == 0)
            {
                positionZero.x = pos.x ;
                positionZero.y = pos.y ;
            }
        }
    }
    return positionZero ;

}


int deplacementPossible(int a, int b, int a0, int b0)
{
    if ((a == a0 + 1) && (a0 != 2) && (b == b0)) return 1 ;
    else if ((a == a0 - 1) && (a0 != 0) && (b == b0)) return 1 ;
    else if ((b == b0 + 1) && (b0 != 2) && (a == a0)) return 1 ;
    else if ((b == b0 - 1) && (b0 != 0) && (a == a0)) return 1 ;
    return 0;
}


void deplacer(int* m, int* n)
{
    int aide;
    aide = *m;
    *m = *n;
    *n = aide;
}


int estSolution(int *P)
{
    int i, j;
    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE-1; j++)
        {
            if (*(P + i * TAILLE + j) != (i * TAILLE + j + 1)) return 0;
        }
    }
    return 1;
}



