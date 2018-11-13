#include "labyrinthe.h"
#include "test_matrices.h"

int main(){
  /* Tests de la création et affichage de matrices */
  labyrinthe lab1,lab2,lab3;

  // test1
  lab1 = creerMatrice(4,4, testA1, testIA1, testJA1);
  printf("\nLabyrinthe créé:");
  afficherMatrice(lab1,4,4);
  printf("\nMatrice attendue:");
  printf("\n%s",strMat1());

  //test2
  lab2 = creerMatrice(10,10, testA2, testIA2, testJA2);
  printf("\nLabyrinthe créé:\n");
  afficherMatrice(lab2,10,10);
  printf("\nMatrice attendue:");
  printf("\n%s",strMat2());

  //test3
  lab3 = creerMatrice(10,10, testA3, testIA3, testJA3);
  printf("\nLabyrinthe créé\n");
  afficherMatrice(lab3,10,10);
  printf("\nMatrice attendue:");
  printf("\n%s",strMat3());

  /* Tests de la vérification et de l'affichage des chemins */

  coordonnee_t * coords = (coordonnee_t*) malloc(100*sizeof(coordonnee_t));
  coordonnee_t coord;

  coord.ligne=0;
  coord.colonne=0;
  coords[0]=coord;

  coord.ligne=1;
  coord.colonne=1;
  coords[1]=coord;

  coord.ligne=2;
  coord.colonne=0;
  coords[2]=coord;
  
  coord.ligne=3;
  coord.colonne=0;
  coords[3]=coord;

  
  chemin_t ch1;
  ch1.coordonnees=coords;
  ch1.taille=4;

  coord.ligne=0;
  coord.colonne=0;

  printf("\nTests chemins sur la matrice:\n");
  afficherMatrice(lab1,4,4);
  printf("\nChemin:");
  afficherChemin(ch1);
  printf("\nverification chemin valide: %d", verifierChemin(ch1,lab1,4,4,coord));
  printf("\nvaleur attendue: 1\n");
  
  coord.colonne = 1;
  coords[0]=coord;

  coord.colonne = 2;
  coords[1]=coord;
  ch1.taille=2;

  coord.colonne = 0;
  printf("\nChemin:");
  afficherChemin(ch1);
  printf("\nverification chemin, 1ere coordonnee: %d", verifierChemin(ch1,lab1,4,4,coord));
  printf("\nvaleur attendue: 0\n");

  coords[0]=coord;

  coord.colonne =2;
  coords[1]=coord;
  ch1.taille=2;

  coord.colonne=0;
  printf("\nChemin:");
  afficherChemin(ch1);
  printf("\nverification chemin, coordonnees non adjacentes: %d", verifierChemin(ch1,lab1,4,4,coord));
  printf("\nvaleur attendue: 0\n");

  
  coords[0]=coord;
  coord.ligne=1;
  coords[1]=coord;
  
  ch1.taille=2;

  coord.ligne=0;
  printf("\nChemin:");
  afficherChemin(ch1);
  printf("\nverification chemin, mur: %d", verifierChemin(ch1,lab1,4,4,coord));
  printf("\nvaleur attendue: 0\n");


  
  
  return 1;
}
