#include <stdio.h>
#include <stdlib.h>
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



int coup_valide(int grille[N][N], int ligne, int colonne, int joueur){
    int i, j;
    int joueur_adverse;
    if (joueur == noir){
        joueur_adverse = blanc;
    }
    else {
        joueur_adverse = noir;
    }
    if (!case_valide(ligne, colonne) || !case_vide(grille, ligne, colonne)){
        return 0;
    }

    // Vertical haut
    i = ligne - 1;
    if (grille[i][colonne] == joueur){
        return 0;
    }
    while(case_valide(i, colonne) && grille[i][colonne] == joueur_adverse){
        i--;
    }
    if (case_valide(i, colonne) && grille[i][colonne] == joueur){
        return 1;
    }

    // Vertical bas
    i = ligne + 1;
    if (grille[i][colonne] == joueur){
        return 0;
    }
    while(case_valide(i, colonne) && grille[i][colonne] == joueur_adverse){
        i++;
    }
    if (case_valide(i, colonne) && grille[i][colonne] == joueur){
        return 1;
    }

    // Horizontal gauche
    j = colonne - 1;
    if (grille[ligne][j] == joueur){
        return 0;
    }
    while(case_valide(ligne, j) && grille[ligne][j] == joueur_adverse){
        j--;
    }
    if (case_valide(ligne, j) && grille[ligne][j] == joueur){
        return 1;
    }

    // Horizontal droite
    j = colonne + 1;
    if (grille[ligne][j] == joueur){
        return 0;
    }
    while(case_valide(ligne, j) && grille[ligne][j] == joueur_adverse){
        j++;
    }
    if (case_valide(ligne, j) && grille[ligne][j] == joueur){
        return 1;
    }

    // Diagonale haut gauche
    i = ligne - 1;
    j = colonne - 1;
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

    // Diagonale haut droite
    i = ligne - 1;
    j = colonne + 1;
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

    // Diagonale bas gauche
    i = ligne + 1;
    j = colonne - 1;
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

    // Diagonale bas droite
    i = ligne + 1;
    j = colonne + 1;
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
    if (peut_jouer(grille,noir) || peut_jouer(grille,blanc)){
        return 0;
    }
    return 1;
}

int gagnant(int grille[N][N]){
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
        return 1;
    }
    else if (nb_noir < nb_blanc){
        return 2;
    }
    return 0;
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
