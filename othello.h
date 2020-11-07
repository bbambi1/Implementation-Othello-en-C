#ifndef OTHELLO_H
#define OTHELLO_H
#define N 8
#define noir 1
#define blanc 2


void initialsation_grille(int grille[N][N]) ;

void affiche_grille(int grille[N][N]) ;

int case_valide(int ligne, int colonne) ;

int case_vide(int grille[N][N], int ligne, int colonne) ;

int coup_valide(int grille[N][N], int ligne, int colonne, int joueur) ;

int peut_jouer(int grille[N][N],int joueur);

int joueur_suivant(int joueur){return joueur%2+1;}

#endif // OTHELLO_H
