/*Labyrinthe.c*/

#include "labyrinthe.h"


/*Premiere partie*/

int lignIA(char* IA, int len) {
  int LA[len];
  int cpt=0;
  int temp;
  for (int k=1; k<sizeof(IA); ++k) {
    temp = IA[k]-cpt;
    if(temp>0) {
      for (int a=0; a<temp; ++a) {
        LA[cpt]=k-1;
        cpt++;
      }
    }
  }
  return LA;
}

labyrinthe creerMatrice (unsigned int lignes, unsigned int colonnes, char* A, char* IA, char* JA){
  labyrinthe tab[lignes][colonnes];
  int cpt=0;
  char* LA = lignIA(IA, sizeof(JA));
  for (int l=0; l<lignes; ++l) {
    for (int c=0; c<colonnes; ++c) {
      if(LA[cpt]==l && JA[cpt]==c) {
        tab[LA[cpt]][JA[cpt]] = A[cpt];
        cpt++;
      }
      else {
        tab[l][c]=0;
      }
    }
  }
  //for (int coord=0; coord<sizeof(JA); coord++)     // ATTRIBUE APRES QUE TOUT SOIT A ZERO, QUE CHOISIR ?
    //tab[LA[coord]][JA[coord]] = A[coord];
  return tab;
}

void afficherMatrice(labyrinthe lab, unsigned int lignes, unsigned int colonnes ){
  for (int l=0; l<lignes; ++l) {
    printf("\n\n");
    for (int c=0; c<colonnes; ++c)
      printf("%d ", lab[l][c]);
  }
}

int deplacementsPossibles(labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t posCourante, coordonnee_t* coordPossibles){
  int ligne = posCourante.ligne;
  int colonne = posCourante.colonne;
  int cpt=0;
  if(ligne==0) {
    if(lab[ligne+1][colonne]!=1) {
      coordPossibles[cpt].ligne = ligne+1;
      coordPossibles[cpt].colonne = colonne;
      cpt++;
    }
  }
  if(ligne==(sizeof(lab)/sizeof(lab[0]))-1) {
    if(lab[ligne-1][colonne]!=1) {
      coordPossibles[cpt].ligne = ligne-1;
      coordPossibles[cpt].colonne = colonne;
      cpt++;
    }
  }
  if(colonne==0) {
    if(lab[ligne][colonne+1]!=1) {
      coordPossibles[cpt].ligne = ligne;
      coordPossibles[cpt].colonne = colonne+1;
      cpt++;
    }
  }
  if(colonne==sizeof(lab[0])-1) {
    if(lab[ligne][colonne-1]!=1) {
      coordPossibles[cpt].ligne = ligne;
      coordPossibles[cpt].colonne = colonne-1;
      cpt++;
    }
  }
  if(cpt==0) {
    for (int i=-1; i<=1; ++i) {
      for (int j=-1; j<=1; ++j) {
        if(lab[ligne+i][colonne+j]!=1) {
          coordPossibles[cpt].ligne = ligne+i;
          coordPossibles[cpt].colonne = colonne+j;
          cpt++;
        }
      }
    }
  }
  return coordPossibles;
}

char verifierChemin(chemin_t ch, labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t depart ){
  if(ch.taille<2)    // AU MINIMUM DEPART ---> ARRIVEE
    return 0;
  for(int k=0; k<ch.taille; ++k) { 
    if(ch.coordonnees[k].ligne < 0 || ch.coordonnees[k].colonne < 0)  // VERIFICATION QU'ON NE SORS PAS DU LABYRINTHE EN HAUT ET A DROITE
      return 0;
    if(ch.coordonnees[k].ligne >= (sizeof(lab)/sizeof(lab[0])) || ch.coordonnees[k].colonne >= sizeof(lab[0]))    // IDEM A GAUCHE ET EN BAS
      return 0;
    coordonnee_t departTEMP;
    if(k==0)
      departTEMP = depart;
    else {
      departTEMP.ligne = ch.coordonnees[k-1].ligne;
      departTEMP.colonne = ch.coordonnees[k-1].colonne;
    }
    coordonnee_t* coordPossibles = deplacementsPossibles(lab, largeur, longueur, departTEMP, coordPossibles);
    int cnd = 0;
    for(int i=0; i<sizeof(coordPossibles); i++) {
      if(ch.coordonnees[k].ligne == coordPossibles[i].ligne && ch.coordonnees[k].colonne == coordPossibles[i].colonne)    // VERIFICATION QUE CHAQUE DEPLACEMENTS EST POSSIBLE EN PARTANT DE LA POSITION LE PRECEDANT
        cnd=1;
    }
    if(cnd==0)    // SI APRES PARCOUS DES DEPLACEMENTS POSSIBLES ONE NE TROUVE PAS CELUI PROPOSE ALORS FAIL
      return 0;
    cnd=0;
    if(k!=ch.taille-1 && lab[ch.coordonnees[k].ligne][ch.coordonnees[k].colonne] == 1)  // VERIFICATION QUE TOUTE CASE SAUF LA DERNIERE N'EST PAS UN 1
      return 0;
  }
  if(lab[ch.coordonnees[-1].ligne][ch.coordonnees[-1].colonne] !=2)    // VERIFICATION QUE LE DERNIER TERME MENE A UN 2
      return 0;
  
  if(lab[depart.ligne][depart.colonne]!=0) // VERIFICATION QUE LE DERNIER TERME MENE A UN 0
    return 0;
  return 1;
}

void afficherChemin(chemin_t ch ){
  printf("Depart ligne: %d , colonne: %d.\n", ch.coordonnees[0].ligne, ch.coordonnees[0].colonne);
  if(ch.taille>2) {  // SI IL Y A DES LIGNES ENTRE 'DEPART' ET 'ARRIVEE'
    for(int k=1; k<ch.taille-1; ++k)
      printf("Puis ligne: %d , colonne: %d.\n", ch.coordonnees[k].ligne, ch.coordonnees[k].colonne);
  }
  printf("Arrivee ligne: %d , colonne: %d.\n", ch.coordonnees[-1].ligne, ch.coordonnees[-1].colonne);
}


/*Seconde partie*/

chemin_t plusCourtCheminDynamique (labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  /*A faire*/
}

chemin_t* tousPlusCourtsChemins(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  /*A faire*/
}
