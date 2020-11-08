#include <stdio.h>
#include <stdlib.h>
#include "othello.h"


int main()
{
    int joueur = 1;
    int ligne, colonne;
    // Initialisation de la grille
    int grille[N][N];
    initialsation_grille(grille);
    affiche_grille(grille);

    // Partie test
    while(!partie_finie(grille)){
    	entrer_coup(grille, &ligne, &colonne, joueur);
    	jouer(grille, ligne, colonne, joueur);
    	affiche_grille(grille);
    	score(grille);
    	if (peut_jouer(grille, joueur_suivant(joueur))){
    		joueur = joueur_suivant(joueur);
    	}
    	else {
    		printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
    	}
    }
    return 0;
}
