#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "othello.h"


int main()
{
    //partie_2_joueurs();

    //partie_vs_computer();

    //computer_vs_computer();

    int joueur_1 = 0;
    int joueur_2 = 0;
    int nul=0;
    for (int i = 0; i< 10; i++){
        int p = computer_vs_computer_stat();
        printf("%d\n",i);
        if (p == 0){
            nul++;
        }
        else if (p==1){
            joueur_1++;
        }
        else{
            joueur_2++;
        }
    }
    printf("\nnul= %d   joueur_1= %d   joueur_2= %d\n",nul,joueur_1,joueur_2);
    return 0;
}
