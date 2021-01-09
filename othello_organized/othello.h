#ifndef OTHELLO_H
#define OTHELLO_H
#define N 8
#define noir 1
#define blanc 2


// rules_othello.c

int my_rand (int n);

void initialisation_grille(int grille[N][N]);

void affiche_grille(int grille[N][N]);

int case_valide(int ligne, int colonne);

int case_vide(int grille[N][N], int ligne, int colonne);

int verticale_haut(int grille[N][N], int ligne, int colonne, int joueur);

int verticale_bas(int grille[N][N], int ligne, int colonne, int joueur);

int horizontale_gauche(int grille[N][N], int ligne, int colonne, int joueur);

int horizontale_droite(int grille[N][N], int ligne, int colonne, int joueur);

int diagonale_haut_droite(int grille[N][N], int ligne, int colonne, int joueur);

int diagonale_haut_gauche(int grille[N][N], int ligne, int colonne, int joueur);

int diagonale_bas_droite(int grille[N][N], int ligne, int colonne, int joueur);

int diagonale_bas_gauche(int grille[N][N], int ligne, int colonne, int joueur);

int coup_valide(int grille[N][N], int ligne, int colonne, int joueur);

int peut_jouer(int grille[N][N],int joueur);

int joueur_suivant(int joueur);

int partie_finie(int grille[N][N]);

void gagnant(int grille[N][N]);

void score(int grille[N][N]);

// play_othello.c

void jouer(int grille[N][N],int ligne,int colonne,int joueur);

void entrer_coup(int grille[N][N], int *ligne, int *colonne, int joueur);

void partie_2_joueurs();

void strategie_naive(int grille[N][N], int *ligne, int *colonne, int joueur);

void strategie_minimax1(int grille[N][N], int *ligne, int *colonne, int joueur);

int eval_minimax(int grille[N][N], int joueur);

int strategie_minimax(int grille[N][N], int *ligne, int *colonne, int profondeur,int depth, int joueur, int maximizing_player);

void partie_vs_computer();

void computer_vs_computer();


#endif // OTHELLO_H
