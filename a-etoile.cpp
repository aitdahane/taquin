#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "aEtoile.h"

void genereEtatInitial(Etat *eC, Etat *eF)
{
    int i, j;
    int k, l;
    int flag;
    int T[TAILLE][TAILLE] = {{0,1,2},{3,4,5},{6,7,8}};
    srand(time(NULL));
    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            flag = 1 ;
            while(flag)
            {
                k = rand() % TAILLE ;
                l = rand() % TAILLE ;
                if (T[l][k] != TAILLE*TAILLE)
                {
                    eC->M[i][j] = T[l][k] ;
                    T[l][k] = TAILLE * TAILLE ;
                    flag = 0 ;
                }
            }
        }
    }
    eC->h = h(*eC, *eF);
    eC->g = 0;

}

int estEtat(Etat e1, Etat e2)
{
    int i, j;
    for(i = 0 ; i < TAILLE ; i++ )
        for(j = 0 ; j < TAILLE ; j++ )
            if( e1.M[i][j] != e2.M[i][j] )
                  return 0;
    return 1;
}

int etatSolution(Etat eC ,Etat eF)
{
    return estEtat(eC, eF);
}

int appartient(Etat e, Liste *l, int *c0)
{
    Noeud *parcours = l->debut;
    while(parcours != NULL)
    {
        if(estEtat(parcours->etat, e))
        {
            *c0 = parcours->etat.g + parcours->etat.h;
            return 1;
        }
        parcours = parcours->suivant;
    }
    return 0;
}



int h(Etat eC, Etat eF)
{
    int valeur_h = 9;
    int i, j;
    for(i = 0; i < TAILLE; i++)
        for( j = 0 ; j < TAILLE ; j++ )
            if( eC.M[i][j] == eF.M[i][j] ) valeur_h--;
    return valeur_h;
}

Etat extraire(Liste *l)
{
    Noeud *n = l->debut;
    Etat e = n->etat;
    l->debut = l->debut->suivant;
    free(n);
    return e;
}

void inserer(Etat e, Liste *l)
{
    Noeud *parcours = l->debut, *precedent = parcours, *n;
    n = (Noeud*)malloc(sizeof(Noeud));
    n->etat = e;

    if( l->debut == NULL )
    {
        l->debut = n;
        l->debut->suivant = NULL;
    }

    else
    {
        while ((parcours != NULL) && ((parcours->etat.h + parcours->etat.g) < (e.g + e.h)))
        {
            precedent = parcours;
            parcours = parcours->suivant;
        }
        if (parcours == NULL)
        {
           precedent->suivant = n ;
           n->suivant = NULL;
        }
        else
        {
            if(parcours == l->debut)
            {
                n->suivant = parcours;
                l->debut = n;
            }
            else
            {
                n->suivant = parcours;
                precedent->suivant = n;
            }
        }
    }
}

void insererAlaFin(Etat e ,Liste *l)
{
    Noeud *parcours = l->debut , *n;
    n = (Noeud*)malloc(sizeof(Noeud));
    n->etat = e;
    n->suivant = NULL;
    if(parcours == NULL)
        l->debut = n;
    else
    {
        while(parcours->suivant != NULL)
            parcours = parcours->suivant;
        parcours->suivant = n;
    }
}



void haut(Etat eC, Etat eF, Liste *l, int a, int b)
{
    if( a > 0 )
    {
        eC.M[a][b] = eC.M[a-1][b];
        eC.M[a-1][b] = 0;
        eC.h = h(eC, eF);
        inserer(eC , l);
    }
}

void bas(Etat eC ,Etat eF, Liste *l ,int a, int b)
{
    if( a < 2 )
    {
        eC.M[a][b] = eC.M[a+1][b];
        eC.M[a+1][b] = 0;
        eC.h = h(eC, eF);
        inserer(eC, l);
    }
}

void gauche(Etat eC, Etat eF, Liste *l, int a, int b)
{
    if( b > 0 )
    {
        eC.M[a][b] = eC.M[a][b-1];
        eC.M[a][b-1] = 0;
        eC.h = h(eC, eF);
        inserer(eC , l);
    }
}

void droite(Etat eC, Etat eF, Liste *l, int a, int b)
{
    if( b < 2 )
    {
        eC.M[a][b] = eC.M[a][b+1];
        eC.M[a][b+1] = 0;
        eC.h = h(eC, eF);
        inserer(eC, l);
    }
}



void genereSuccesseur(Etat eC, Etat eF, Liste *l)
{
    int a,b;
    int i, j;
    for( i = 0 ; i < TAILLE ; i++ )
        for( j = 0 ; j < TAILLE ; j++ )
            if( eC.M[i][j] == 0 )
              {
                 a=i;
                 b=j;
               }
    eC.g++;
    haut(eC, eF, l, a, b);
    bas(eC, eF, l, a, b);
    droite(eC, eF, l, a, b);
    gauche(eC, eF, l, a, b);
}



void supprimer(Etat e ,Liste *l)
{
    Liste l0 = *l;
    Noeud *parcours = l->debut->suivant;
    l->debut = NULL;
    insererAlaFin(l0.debut->etat, l);
    while( parcours != NULL && !estEtat(parcours->etat, e))
    {
       insererAlaFin( parcours->etat, l);
       parcours = parcours->suivant;
    }
//    if( parcours != NULL && !estEtat(l0.debut->etat, parcours->etat))
//        insererAlaFin(parcours->etat, l);
}


int rechercheAetoile(Etat eI, Etat eF, void genereSuccesseur(Etat e , Etat f, Liste *l))
{
    Liste listeNoeuds, noeudsDejaTraites, listeSuccesseur;
    int c;
    int c0;
    listeNoeuds.debut = NULL ;
    Etat etatCourant;
    Noeud *parcours;

    inserer(eI, &listeNoeuds);
    noeudsDejaTraites.debut = NULL;
    while(listeNoeuds.debut != NULL)
    {
        etatCourant = extraire(&listeNoeuds);
        listeSuccesseur.debut = NULL;
        if (etatSolution(etatCourant, eF))
        {
           return etatCourant.g;
        }
        else
        {
            genereSuccesseur(etatCourant, eF, &listeSuccesseur);

            for(parcours = listeSuccesseur.debut ; parcours ; parcours = parcours->suivant )
            {
                    c = h(parcours->etat, eF) + etatCourant.g + 1;
                    if(!appartient(parcours->etat, &listeNoeuds, &c0) && !appartient(parcours->etat, &noeudsDejaTraites, &c0))
                    {
                        inserer( parcours->etat , &listeNoeuds);
                    }
                    else
                    {
                        if (appartient(parcours->etat, &listeNoeuds, &c0))
                        {
                            if (c < c0)
                            {
                                parcours->etat.g = c - (parcours->etat.h);
                            }
                        }
                        else
                        {
                            if (appartient(parcours->etat, &noeudsDejaTraites, &c0))
                            {
                                if(c < c0)
                                {
                                    supprimer(parcours->etat , &noeudsDejaTraites);
                                    inserer(parcours->etat, &listeNoeuds);
                                }
                            }
                        }
                }
            }
            inserer(etatCourant , &noeudsDejaTraites);
        }
    }
    return 0;
}







