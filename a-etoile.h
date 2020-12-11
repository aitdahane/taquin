#ifndef AETOILE2_H_INCLUDED
#define AETOILE2_H_INCLUDED
#include <time.h>
#include "constantes.h"

typedef struct Etat
{
    int M[TAILLE][TAILLE];
    int h;
    int g;
}Etat;

typedef struct Noeud
{
    Etat etat;
    struct Noeud *suivant;
}Noeud;

typedef struct Liste
{
    Noeud *debut;
}Liste;
void genereEtatInitial(Etat *eC, Etat *eF);

int estEtat(Etat e1, Etat e2);

int etatSolution(Etat eC ,Etat eF);

int appartient(Etat e, Liste *l, int *c0);

int h(Etat eC, Etat eF);

Etat extraire(Liste *l);

void inserer(Etat e, Liste *l);

void insererAlaFin(Etat e ,Liste *l);

void droite(Etat eC, Etat eF, Liste *l, int a, int b);
void gauche(Etat eC, Etat eF, Liste *l, int a, int b);
void haut(Etat eC, Etat eF, Liste *l, int a, int b);
void bas(Etat eC, Etat eF, Liste *l, int a, int b);

void genereSuccesseur(Etat eC, Etat eF, Liste *l);

void supprimer(Etat e ,Liste *l);

int rechercheAetoile(Etat eI, Etat eF, void genereSuccesseur(Etat e , Etat f, Liste *l));

#endif // AETOILE2_H_INCLUDED
