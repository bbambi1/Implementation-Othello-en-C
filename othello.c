#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "othello.h"


// Initialise la grille en placant les 4 premiers pions

void initialsation_grille(int grille[N][N]){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            grille[i][j] = 0;
        }
    }
    grille[(N/2)-1][(N/2)-1] = noir;
    grille[N/2][N/2] = noir;
    grille[N/2][(N/2)-1] = blanc;
    grille[(N/2)-1][N/2] = blanc;
}


// Affiche la grille passee en argument

void affiche_grille(int grille[N][N]){
    printf("\n");
    for(int ligne = 0; ligne < N; ligne++){
        printf("%d.  ", ligne);
        for(int colonne = 0; colonne < N; colonne++){
            printf("%d  ", grille[ligne][colonne]);
        }
        printf("\n");
    }
    printf("\n    0. 1. 2. 3. 4. 5. 6. 7.\n");
}


// Renvoie True si on joue une case de la grille, False sinon

int case_valide(int ligne, int colonne){
    return ((ligne >= 0 && ligne < N) && (colonne >= 0 && colonne < N));
}


// Renvoie True si la case jouee est vide
int case_vide(int grille[N][N], int ligne, int colonne){
    return grille[ligne][colonne] == 0;
}

int verticale_haut(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne - 1;
    if (grille[i][colonne] == joueur){
        return 0;
    }
    while(case_valide(i, colonne) && grille[i][colonne] == joueur_adverse){
        i--;
    }
    if (case_valide(i, colonne) && grille[i][colonne] == joueur){
        return 1;
    }
    return 0;

}
int verticale_bas(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne + 1;
    if (grille[i][colonne] == joueur){
        return 0;
    }
    while(case_valide(i, colonne) && grille[i][colonne] == joueur_adverse){
        i++;
    }
    if (case_valide(i, colonne) && grille[i][colonne] == joueur){
        return 1;
    }
    return 0;

}
int horizontale_gauche(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int j = colonne - 1;
    if (grille[ligne][j] == joueur){
        return 0;
    }
    while(case_valide(ligne, j) && grille[ligne][j] == joueur_adverse){
        j--;
    }
    if (case_valide(ligne, j) && grille[ligne][j] == joueur){
        return 1;
    }
    return 0;

}
int horizontale_droite(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int j = colonne + 1;
    if (grille[ligne][j] == joueur){
        return 0;
    }
    while(case_valide(ligne, j) && grille[ligne][j] == joueur_adverse){
        j++;
    }
    if (case_valide(ligne, j) && grille[ligne][j] == joueur){
        return 1;
    }
    return 0;

}
int diagonale_haut_droite(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne - 1;
    int j = colonne + 1;
    if (grille[i][j] == joueur){
        return 0;
    }
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        j++;
    i--;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        return 1;
    }
    return 0;

}
int diagonale_haut_gauche(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne - 1;
    int j = colonne - 1;
    if (grille[i][j] == joueur){
        return 0;
    }
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        j--;
    i--;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        return 1;
    }
    return 0;

}
int diagonale_bas_droite(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne + 1;
    int j = colonne + 1;
    if (grille[i][j] == joueur){
        return 0;
    }
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        j++;
    i++;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        return 1;
    }
    return 0;
}
int diagonale_bas_gauche(int grille[N][N], int ligne, int colonne, int joueur){
    int joueur_adverse=joueur_suivant(joueur);
    int i = ligne + 1;
    int j = colonne - 1;
    if (grille[i][j] == joueur){
        return 0;
    }
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        j--;
    i++;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        return 1;
    }
    return 0;
}



int coup_valide(int grille[N][N], int ligne, int colonne, int joueur){
    if (!case_valide(ligne, colonne) || !case_vide(grille, ligne, colonne)){
        return 0;
    }
    return verticale_bas(grille,ligne,colonne,joueur)||verticale_haut(grille,ligne,colonne,joueur)||horizontale_droite(grille,ligne,colonne,joueur)||horizontale_gauche(grille,ligne,colonne,joueur)||diagonale_bas_droite(grille,ligne,colonne,joueur)||diagonale_bas_gauche(grille,ligne,colonne,joueur)||diagonale_haut_droite(grille,ligne,colonne,joueur)||diagonale_haut_gauche(grille,ligne,colonne,joueur);

}


int peut_jouer(int grille[N][N], int joueur){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (coup_valide(grille, i, j, joueur)){
                return 1;
            }
        }
    }
    return 0;
}


int joueur_suivant(int joueur){
    return (joueur % 2) + 1;
}


void entrer_coup(int grille[N][N], int *ligne, int *colonne, int joueur){
    printf ("\nC'est au tour du joueur %d de jouer\n", joueur);
    printf("\nEntrez la ligne correspondant au coup que vous souhaitez jouer :\n");
    scanf("\n%d", ligne);
    printf("\nEntrez la colonne correspondant au coup que vous souhaitez jouer :\n");
    scanf("\n%d", colonne);
    while (!coup_valide(grille, *ligne, *colonne, joueur)){
        printf ("\nCe coup n'est pas valide\nChoisissez une autre case\n");
        printf("\nEntrez la ligne correspondant au coup que vous souhaitez jouer :\n");
        scanf("\n%d", ligne);
        printf("\nEntrez la colonne correspondant au coup que vous souhaitez jouer :\n");
        scanf("\n%d", colonne);
    }
}


int partie_finie(int grille[N][N]){
    if ((peut_jouer(grille,noir) || peut_jouer(grille,blanc))){
        return 0;
    }
    return 1;
}


void gagnant(int grille[N][N]){
    int nb_noir = 0;
    int nb_blanc = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if (grille[i][j] == 1){
                nb_noir++;
            }
            else if (grille[i][j]==2){
                nb_blanc++;
            }
        }
    }
    if (nb_noir > nb_blanc){
        printf("Le joueur 1 gagne!\n");
    }
    else if (nb_noir < nb_blanc){
        printf("Le joueur 2 gagne !\n");
    }
    else{
        printf("C'est un atch nul !\n");
    }
}


void score(int grille[N][N]){
    int nb_noir = 0;
    int nb_blanc = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if (grille[i][j] == 1){
                nb_noir++;
            }
            else if (grille[i][j]==2){
                nb_blanc++;
            }
        }
    }
    printf("\nJoueur 1 : %d points\nJoueur 2 : %d points", nb_noir, nb_blanc);
}


void jouer(int grille[N][N],int ligne,int colonne,int joueur){
    int i, j;
    int joueur_adverse;
    if (joueur == noir){
        joueur_adverse = blanc;
    }
    else {
        joueur_adverse = noir;
    }
    grille[ligne][colonne] = joueur;

    // Vertical vers le haut
    i = ligne - 1;
    while (case_valide(i, colonne) && grille[i][colonne] == joueur_adverse){
        i--;
    }
    if (case_valide(i, colonne) && grille[i][colonne] == joueur){
        for (int k = i+1; k < ligne; k++){
            grille[k][colonne] = joueur;
        }
    }

    // Vertical vers le bas
    i = ligne + 1;
    while (case_valide(i, colonne) && grille[i][colonne] == joueur_adverse){
        i++;
    }
    if (case_valide(i, colonne) && grille[i][colonne] == joueur){
        for (int k = i-1; k > ligne; k--){
            grille[k][colonne] = joueur;
        }
    }

    // Horizontal vers la droite
    j = colonne + 1;
    while (case_valide(ligne, j) && grille[ligne][j] == joueur_adverse){
        j++;
    }
    if (case_valide(ligne, j) && grille[ligne][j] == joueur){
        for (int k = j-1; k > colonne; k--){
            grille[ligne][k]=joueur;
        }
    }

    // Horizontal vers la gauche
    j = colonne - 1;
    while (case_valide(ligne, j) && grille[ligne][j] == joueur_adverse){
        j--;
    }
    if (case_valide(ligne, j) && grille[ligne][j] == joueur){
        for (int k = j+1; k < colonne; k++){
            grille[ligne][k] = joueur;
        }
    }

    // Diagonale haut gauche
    i = ligne - 1;
    j = colonne - 1;
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        i--;
        j--;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        i++;
        j++;
        while(grille[i][j] == joueur_adverse){
            grille[i][j] = joueur;
            i++;
            j++;
        }
    }

    // Diagonale haut droite
    i = ligne - 1;
    j = colonne + 1;
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        i--;
        j++;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        i++;
        j--;
        while(grille[i][j] == joueur_adverse){
            grille[i][j] = joueur;
            i++;
            j--;
        }
    }

    // Diagonale bas gauche
    i = ligne + 1;
    j = colonne - 1;
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        i++;
        j--;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        i--;
        j++;
        while(grille[i][j] == joueur_adverse){
            grille[i][j] = joueur;
            i--;
            j++;
        }
    }

    // Diagonale bas droite
    i = ligne + 1;
    j = colonne + 1;
    while(case_valide(i, j) && grille[i][j] == joueur_adverse){
        i++;
        j++;
    }
    if (case_valide(i, j) && grille[i][j] == joueur){
        i--;
        j--;
        while(grille[i][j] == joueur_adverse){
            grille[i][j] = joueur;
            i--;
            j--;
        }
    }
}


void partie_2_joueurs(){
    int joueur = 1;
    int ligne, colonne;
    // Initialisation de la grille
    int grille[N][N];
    initialsation_grille(grille);
    affiche_grille(grille);

    // Partie joueur vs joueur
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
    gagnant(grille);

}


void partie_vs_computer(){
    int joueur = 1;
    int ligne, colonne;
    // Initialisation de la grille
    int grille[N][N];
    initialsation_grille(grille);
    affiche_grille(grille);

    // Partie joueur vs machine
    while(!partie_finie(grille)){
        if (joueur == 1){


            entrer_coup(grille, &ligne, &colonne, joueur);
            jouer(grille, ligne, colonne, joueur);
            affiche_grille(grille);
            score(grille);
            if (peut_jouer(grille, joueur_suivant(joueur))){
                joueur = joueur_suivant(joueur);
            }
            else{
                printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
            }
        }
        else{


            //srand(time(NULL));
            ligne = rand()%8;
            colonne = rand()%8;
            while(!coup_valide(grille,ligne,colonne,joueur)){
                //srand(time(NULL));
                ligne = rand()%8;
                colonne = rand()%8;
            }
            jouer(grille, ligne, colonne, joueur);
            affiche_grille(grille);
            score(grille);
            if (peut_jouer(grille, joueur_suivant(joueur))){
                joueur = joueur_suivant(joueur);
            }
            else{
                printf("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
            }
        }
    }
    gagnant(grille);
}


void computer_vs_computer(){
    //srand(time(NULL));
    int joueur = 1;
    int ligne, colonne;
    // Initialisation de la grille
    int grille[N][N];
    initialsation_grille(grille);
    affiche_grille(grille);

    // Partie machine vs machine
    //srand(time(NULL));
    while(!partie_finie(grille)){
        //srand(time(NULL));
        if (joueur == 1){
            //srand(time(NULL));
            printf("\ncondition1\n");
            ligne = my_rand(8);
            colonne = my_rand(8);
            while(!coup_valide(grille,ligne,colonne,joueur)){
                //srand(time(NULL));
                ligne = my_rand(8);
                colonne =my_rand(8);
                printf("\n1  ligne=%d col=%d \n",ligne,colonne);
            }
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
        else {
            printf("\ncondition2\n");
            //srand(time(NULL));
            ligne = my_rand(8);
            colonne = my_rand(8);
            while(!coup_valide(grille,ligne,colonne,joueur)){
                //srand(time(NULL));
                ligne = my_rand(8);
                colonne = my_rand(8);
                printf("\n2 ligne=%d col=%d \n",ligne,colonne);
            }
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
    }
    gagnant(grille);
}
int my_rand (int n)
{
   static int first = 0;

   if (first == 0)
   {
      srand (time (NULL));
      first = 1;
   }
   return (rand ()%n);
}
