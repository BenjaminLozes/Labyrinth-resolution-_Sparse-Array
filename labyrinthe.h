/************************************************************************ 

                               Labyrinthe.h

*************************************************************************/
#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

/* Types */

// Un labyrinthe est une matrice composee de 0 (chemin), de 1 (mur),
// et d'un ou plusieurs 2 (sortie)
typedef unsigned char** labyrinthe;

// Une coordonnee est constituee d'un indice de ligne et d'un indice
// de colonne dans la matrice labyrinthe
typedef struct COORD {
  int ligne;
  int colonne;
} coordonnee_t;

// Un chemin se compose d'un tableau de coordonnees (qu'il faut
// allouer dynamiquement) et du nombre de cases dans le chemin
typedef struct CHEMIN {
  coordonnee_t * coordonnees;
  int taille;
} chemin_t;

/* Declaration des fonctions */

//La fonction creerMatrice prend en parametre une matrice creuse
//decrite sous forme CSR et renvoie le pointeur vers la matrice
//correspondante.
labyrinthe creerMatrice (unsigned int lignes, unsigned int colonnes, char* A, char* IA, char* JA);

// La fonction afficherLabyrinthe affiche le labyrinthe fourni en
// parametre
void afficherMatrice( labyrinthe lab, unsigned int lignes, unsigned int colonnes );

// La fonction deplacementsPossibles retourne le nombre de deplacements
// possibles depuis la position courante, et remplit le tableau
// coordPossibles avec les coordonnees accessibles
int deplacementsPossibles( labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t posCourante, coordonnee_t* coordPossibles);

// La fonction verifChemin verifie que le chemin fourni en parametre
// est correct : les deplacements sont valides et le chemin rejoint
// l'entree du labyrinthe a l'une de ses sorties. La fonction retourne
// 1 si le chemin est valide et 0 sinon
char verifierChemin( chemin_t ch, labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t depart );

// La fonction afficherChemin affiche le chemin fourni en parametre
void afficherChemin( chemin_t ch );



// La fonction plusCourtCheminDynamique trouve le plus court chemin
// valide reliant l'entree du labyrinthe et l'une de ses sorties, en
// explorant par programmation dynamique. Le chemin trouve est renvoyé
// par la fonction. Le labyrinthe M2 permet de connaitre la distance
// minimale separant chaque case deja visitee a la case de depart. Les
// modifications sur le labyrinthe M2 doivent etre realisees en place
// et non sur une copie de M2.  Cette fonction peut faire appel a des
// fonctions auxiliaires, par exemple une fonction qui explore les
// chemins et ecrit dans M2, et une fonction qui construit le chemin
// solution à la fin.
chemin_t plusCourtCheminDynamique ( labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart);


chemin_t* tousPlusCourtsChemins(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart);
