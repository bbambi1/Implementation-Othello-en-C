#include <stdio.h>
#include <stdlib.h>
#include "othello.h"


int main()
{
    // Initialisation de la grille
    int grille[N][N];
    initialsation_grille(grille);
    affiche_grille(grille);

    // Test coup valide
    int t = coup_valide(grille,5,2,4);
    printf("%d\n",t);
}
