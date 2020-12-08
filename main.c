#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "othello.h"


int main()
{
    //srand(time(NULL));
    //partie_2_joueurs();

    //partie_vs_computer();

    //computer_vs_computer();
    /*int l1[]={0,0,1,1,1,0,2,1};
    int l2[]={0,0,2,0,2,2,2,1};
    int l3[]={1,0,2,2,1,1,2,1};
    int l4[]={1,1,2,1,1,1,2,0};
    int l5[]={1,2,1,2,1,1,2,2};
    int l6[]={2,2,2,1,1,1,2,0};
    int l7[]={2,2,1,2,1,1,1,1};
    int l8[]={2,1,2,2,2,2,2,0};
    int grille[8][8] ;
    for(int i=0;i<8;i++){
        grille[0][i]=l1[i];
    }
    for(int i=0;i<8;i++){
        grille[1][i]=l2[i];
    }
    for(int i=0;i<8;i++){
        grille[2][i]=l3[i];
    }
    for(int i=0;i<8;i++){
        grille[3][i]=l4[i];
    }
    for(int i=0;i<8;i++){
        grille[4][i]=l5[i];
    }
    for(int i=0;i<8;i++){
        grille[5][i]=l6[i];
    }
    for(int i=0;i<8;i++){
        grille[6][i]=l7[i];
    }
    for(int i=0;i<8;i++){
        grille[7][i]=l8[i];
    }
    affiche_grille(grille);
    printf("%d\n%d\n%d\n",partie_finie(grille),peut_jouer(grille,1),peut_jouer(grille,2));
    score(grille);
    printf("coup valide %d\n",coup_valide(grille,3,7,1));*/


    /*srand( time( NULL ) );
    printf( "%d\n", rand() );
    printf( "%d\n", rand() );
    printf( "%d\n", rand() );

    printf( "%d\n", rand() );
    printf( "%d\n", rand() );
    printf( "%d\n", rand() );  */
    //printf("%d\n",my_rand(8));

    int j1=0;
    int j2=0;
    int nul=0;
    for (int i=0;i<1000;i++){
        int p=computer_vs_computer_stat();
        if (p==0){
            nul++;
        }
        else if (p==1){
            j1++;
        }
        else{
            j2++;
        }
    }
    printf("nul= %d   j1= %d   j2= %d ",nul,j1,j2);


    return 0;
}
