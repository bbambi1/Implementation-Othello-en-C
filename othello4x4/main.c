#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "othello4x4.h"


int main()
{   
    int partie = 0;

    while ((partie != 1) && (partie != 2) && (partie != 3)){
        printf("\nQuelle partie souhaitez-vous lancer ?\n1 = joueur_vs_joueur\n2 = joueur_vs_computer\n3 = computer_vs_computer\nEntrez votre choix (nombre entier uniquement) : ");
        scanf("\n%d", &partie);
        switch(partie){
            case 1 : 
                partie_2_joueurs();
                break;
            case 2 : 
                partie_vs_computer();
                break;
            case 3 : 
                computer_vs_computer();
                break;
            default : 
            printf("\nPartie non reconnue\n");
            break;
        }
    }
    //printf("\n%d ", computer_vs_computer_stat());
    return 0;
}
