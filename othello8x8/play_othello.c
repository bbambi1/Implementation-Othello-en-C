#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "othello.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


// Permet de jouer un coup (placer un pion sur la grille et retourner les pions adverses encadrés)

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


// Utile dans les parties avec un joeur non machine (permet de rentrer un coup valide)

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


// Simule une partie entre deux joueurs (non machine)

void partie_2_joueurs(){
    int joueur = 1;
    int ligne, colonne;

    // Initialisation de la grille
    int grille[N][N];
    initialisation_grille(grille);
    printf("\nDebut de la partie\n");
    affiche_grille(grille);
    printf("\nJoueur 1 : 0 point\nJoueur 2 : 0 point\n");

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





//Strategie naive de notre joueur "computer"

void strategie_naive(int grille[N][N], int *ligne, int *colonne, int joueur){
    *ligne = my_rand(N);
    *colonne = my_rand(N);
    while(!coup_valide(grille, *ligne, *colonne, joueur)){
        *ligne = my_rand(N);
        *colonne = my_rand(N);
    }
}


// Fonction d'évaluation de l'algorithme Min-Max

int eval_minimax(int grille[N][N], int joueur){
    int l[] = {500, -150, 30, 10, 10, 30, -150, 500,-150, -250, 0, 0, 0, 0, -250, -150,30, 0, 1, 2, 2, 1, 0, 30,10, 0, 2, 16, 16, 2, 0, 10,10, 0, 2, 16, 16, 2, 0, 10,30, 0, 1, 2, 2, 1, 0, 30,-150, -250, 0, 0, 0, 0, -250, -150,500, -150, 30, 10, 10, 30, -150, 500};

    int matrice_heuristique[N][N] ;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
        matrice_heuristique[i][j] = l[i + N*j];
        }
    }
    int eval = 0 ;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if (grille[i][j] == joueur){
                eval += matrice_heuristique[i][j];
            }
        }
    }
    return eval;
}


// Algorithme Min-Max

int strategie_minimax(int grille[N][N], int *ligne, int *colonne, int profondeur, int depth, int joueur, int maximizing_player){
    if ((profondeur == 0) || !peut_jouer(grille, joueur)){
        return eval_minimax(grille, joueur_suivant(joueur));
    }
    if (maximizing_player){
        int value = -100000000;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if (coup_valide(grille, i, j, joueur)){

                    // on copie notre grille
                    int copie_grille[N][N];
                    for(int i = 0; i < N; i++){
                        for(int j = 0; j < N; j++){
                            copie_grille[i][j] = grille[i][j];
                        }
                    }

                    jouer(copie_grille, i, j, joueur);
                    int next_player = joueur_suivant(joueur);
                    int value_bis = value;
                    value = MAX(value, strategie_minimax(copie_grille, ligne, colonne, profondeur - 1, depth, next_player, 0));
                    if ((value > value_bis) && (profondeur == depth)){
                        *ligne = i;
                        *colonne = j;
                    }
                    value_bis = value;
                }
            }
        }
        return value;
    }
    else{
        int value = 100000000;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if (coup_valide(grille, i, j, joueur)){

                    // on copie notre grille
                    int copie_grille[N][N];
                    for(int i = 0; i < N; i++){
                        for(int j = 0; j < N; j++){
                            copie_grille[i][j] = grille[i][j];
                        }
                    }

                    jouer(copie_grille, i, j, joueur);
                    int next_player = joueur_suivant(joueur);
                    int value_bis = value;
                    value = MIN(value, strategie_minimax(copie_grille, ligne, colonne, profondeur - 1, depth, next_player, 1));
                    if ((value < value_bis) && (profondeur == depth)){
                        *ligne = i;
                        *colonne = j;
                    }
                    value_bis = value;
                }
            }
        }
        return value;
    }
}


// Elagage alpha - beta 

int alpha_beta(int grille[N][N], int *ligne, int *colonne, int joueur, int alpha, int beta, int profondeur, int depth, int maximizing_player){
    int value;
    if ((profondeur == 0) || !peut_jouer(grille, joueur)){
        return eval_minimax(grille, joueur_suivant(joueur));
    }
    if (maximizing_player){
        value = -100000000;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if (coup_valide(grille, i, j, joueur)){

                    // on copie notre grille
                    int copie_grille[N][N];
                    for(int i = 0; i < N; i++){
                        for(int j = 0; j < N; j++){
                            copie_grille[i][j] = grille[i][j];
                        }
                    }

                    jouer(copie_grille, i, j, joueur);
                    int next_player = joueur_suivant(joueur);
                    int value_bis = value;
                    value = MAX(value, alpha_beta(copie_grille, ligne, colonne, next_player, alpha, beta, profondeur - 1, depth, 0));
                    if ((value > value_bis) && (profondeur == depth)){
                        *ligne = i;
                        *colonne = j;
                    }
                    value_bis = value;
                    if (value >= beta){
                        return value;
                    }
                    alpha = MAX(alpha, value);
                }
            }
        }
    }
    else{
        value = 100000000;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if (coup_valide(grille, i, j, joueur)){

                    // on copie notre grille
                    int copie_grille[N][N];
                    for(int i = 0; i < N; i++){
                        for(int j = 0; j < N; j++){
                            copie_grille[i][j] = grille[i][j];
                        }
                    }

                    jouer(copie_grille, i, j, joueur);
                    int next_player = joueur_suivant(joueur);
                    int value_bis = value;
                    value = MIN(value, alpha_beta(copie_grille, ligne, colonne, next_player, alpha, beta, profondeur - 1, depth, 1));
                    if ((value < value_bis) && (profondeur == depth)){
                        *ligne = i;
                        *colonne = j;
                    }
                    value_bis = value;
                    if (alpha >= value){
                        return value;
                    }
                    beta = MIN(beta, value);
                }
            }
        }
    }
    return value;
}


//Simule une partie entre un joueur et l'ordinateur

void partie_vs_computer(){
    int joueur = 1;
    int ligne, colonne;

    printf("\nVous êtes le joueur 1 !");

    // Choix de la strategie des joueurs "computer"
    int strategie = 0;
    int depth = 0;
    while ((strategie != 1) && (strategie != 2) && (strategie != 3)){
        printf("\nQuelle strategie souhaitez-vous utiliser pour le joueur ordinateur 1 ?\n1 = naif\n2 = minimax\n3 = alpha-beta\n");
        scanf("\n%d", &strategie);
        switch(strategie){
            case 1 :
                break;
            case 2 :
                break;
            case 3 :
                break;
            default :
            printf("\nStrategie non reconnue\n");
        }
    }
    if ((strategie == 2) || (strategie == 3)){
        printf("\nChoisissez la profondeur que vous souhaitez utiliser (entrer un entier, par exemple : 2)\n");
        scanf("\n%d", &depth);
    }

    // Initialisation de la grille
    int grille[N][N];
    initialisation_grille(grille);
    printf("\nDebut de la partie\n");
    affiche_grille(grille);
    printf("\nJoueur 1 : 0 point\nJoueur 2 : 0 point\n");

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
            if (strategie == 1){
                strategie_naive(grille, &ligne, &colonne, joueur);
            }
            else if (strategie == 2){
                strategie_minimax(grille, &ligne, &colonne, depth, depth, joueur, 1);
            }
            else{
                alpha_beta(grille, &ligne, &colonne, joueur, -1000000000, 1000000000, depth, depth, 1);
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


// Simule une partie ordinateur contre ordinateur

void computer_vs_computer(){
    int joueur = 1;
    int ligne, colonne;

    // Choix de la strategie des joueurs "computer"
    int strategie1 = 0;
    int depth1 = 0;
    int strategie2 = 0;
    int depth2 = 0;
    // Stratégie du joueur 1
    while ((strategie1 != 1) && (strategie1 != 2) && (strategie1 != 3)){
        printf("\nQuelle strategie souhaitez-vous utiliser pour le joueur ordinateur 1 ?\n1 = naif\n2 = minimax\n3 = alpha-beta\n");
        scanf("\n%d", &strategie1);
        switch(strategie1){
            case 1 :
                break;
            case 2 :
                break;
            case 3 :
                break;
            default :
            printf("\nStrategie non reconnue\n");
        }
    }
    if ((strategie1 == 2) || (strategie1 == 3)){
        printf("\nChoisissez la profondeur que vous souhaitez utiliser (entrer un entier, par exemple : 2)\n");
        scanf("\n%d", &depth1);
    }

    // Stratégie du joueur 2
    while ((strategie2 != 1) && (strategie2 != 2) && (strategie2 != 3)){
        printf("\nQuelle strategie souhaitez-vous utiliser pour le joueur ordinateur 1 ?\n1 = naif\n2 = minimax\n3 = alpha-beta\n");
        scanf("\n%d", &strategie2);
        switch(strategie2){
            case 1 :
                break;
            case 2 :
                break;
            case 3 :
                break;
            default :
            printf("\nStrategie non reconnue\n");
        }
    }
    if ((strategie2 == 2) || (strategie2 == 3)){
        printf("\nChoisissez la profondeur que vous souhaitez utiliser (entrer un entier, par exemple : 2)\n");
        scanf("\n%d", &depth2);
    }

    // Initialisation de la grille
    int grille[N][N];
    initialisation_grille(grille);
    printf("\nDebut de la partie\n");
    affiche_grille(grille);
    printf("\nJoueur 1 : 0 point\nJoueur 2 : 0 point\n");

    // Partie machine vs machine
    while(!partie_finie(grille)){
        if (joueur == 1){
            if (strategie1 == 1){
                strategie_naive(grille, &ligne, &colonne, joueur);
            }
            else if (strategie1 == 2){
                strategie_minimax(grille, &ligne, &colonne, depth1, depth1, joueur, 1);
            }
            else{
                alpha_beta(grille, &ligne, &colonne, joueur, -1000000000, 1000000000, depth1, depth1, 1);
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
            if (strategie2 == 1){
                strategie_naive(grille, &ligne, &colonne, joueur);
            }
            else if (strategie2 == 2){
                strategie_minimax(grille, &ligne, &colonne, depth2, depth2, joueur, 1);
            }
            else{
                alpha_beta(grille, &ligne, &colonne, joueur, -1000000000, 1000000000, depth2, depth2, 1);
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
