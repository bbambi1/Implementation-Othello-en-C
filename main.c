#include <stdio.h>
#include <stdlib.h>
#include "othello.h"


int main()
{
    int grille[N][N];
    initialsation_grille(grille);
    affiche_grille(grille);
    // test coup valide
    int t=coup_valide(grille,5,2,4);
    printf("%d\n",t);


}
