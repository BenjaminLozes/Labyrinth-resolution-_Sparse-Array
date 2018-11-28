/*Labyrinthe.c*/

#include "labyrinthe.h"
#include <math.h>

/*Premiere partie*/


void afficherTab(char* tab, int len) {
  for(int a=0; a<len; ++a)
    printf("%d ", tab[a]);
  printf("\n");
}

int calcNbPoints(char* IA, int lignes) {
  int nbPts = 0;
  for(int x=1; x<lignes+1; ++x) {
    if(IA[x]>nbPts)
      nbPts=IA[x];
  }
  return nbPts;
}

char* lignIA(char* IA, int nbPts, int lignes) {
  char* LA = (char*) malloc(nbPts*sizeof(char));
  int cpt=0;
  int temp;
  for (int k=1; k<lignes+1; ++k) {
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

labyrinthe creerMatrice(unsigned int lignes, unsigned int colonnes, char* A, char* IA, char* JA){
  labyrinthe tab = (unsigned char **) malloc(lignes*sizeof(unsigned char *));
  for(unsigned short i=0; i<lignes; ++i){
    tab[i]=(unsigned char *) malloc(colonnes*sizeof(unsigned char));
    for(unsigned short l=0; l<colonnes; ++l) {
      tab[i][l] = 0;
    }
  }
  int nbPts = calcNbPoints(IA, lignes);
  char* LA = lignIA(IA, nbPts, lignes);
  for (int coord=0; coord<nbPts; coord++)     // ATTRIBUER LES VALEURS 1 ET 2 APRES QUE TOUT SOIT A ZERO
    tab[LA[coord]][JA[coord]] = A[coord];
  return tab;
}

void afficherMatrice(labyrinthe lab, unsigned int lignes, unsigned int colonnes ){
  for (unsigned short l=0; l<lignes; ++l) {
    printf("\n");
    for (unsigned short c=0; c<colonnes; ++c)
      printf("%d ", lab[l][c]);
  }
  printf("\n");
}

int deplacementsPossibles(labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t posCourante, coordonnee_t* coordPossibles){
  int ligne = posCourante.ligne;
  int colonne = posCourante.colonne;
  int cpt = 0;
  int icond[2] = {-1, 1};
  int jcond[2] = {-1, 1};

  if(ligne ==0)
    icond[0] = 0;
  else if(ligne >= longueur-1)
    icond[1] = 0;
  if(colonne == 0)
    jcond[0] = 0;
  else if(colonne >= largeur-1)
    jcond[1] = 0;

  //printf("Min ligne: %d, max ligne: %d, ", icond[0], icond[1]);
  //printf("Min colonne: %d, max colonne: %d", jcond[0], jcond[1]);

  for(int i = icond[0]; i<=icond[1]; i++) {
    for(int j = jcond[0]; j<=jcond[1]; j++) {
      if(!(i == 0 && j == 0)) {
        //printf("\n--Case = %d en i: %d et j: %d.", lab[ligne+i][colonne+j], i, j);
        if(lab[ligne+i][colonne+j] != 1) {
          //printf("\nLigne = %d et i: %d.", ligne+i, i);
          coordPossibles[cpt].ligne = ligne+i;
          //printf("\nColonne = %d et i: %d.", colonne+j, i);
          coordPossibles[cpt].colonne = colonne+j;
          ++cpt;
        }
      }
    }
  }
  return cpt;
}

 char verifierChemin(chemin_t ch, labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t depart ){
  if(ch.taille<2)    // AU MINIMUM DEPART ---> ARRIVEE
    return 0;

  int lenABligne = 0;
  int lenABcolonne = 0;
  for(int k=1; k<ch.taille; ++k) { // TEST SUR CHAQUES DEPLACEMENTS. ILS SONT PLACES AVANT LES TESTS UNITAIRES POUR EVITER DES DUMP DE MEMOIRE
    if(ch.coordonnees[k].ligne < 0 || ch.coordonnees[k].colonne < 0)  // VERIFICATION QU'ON NE SORS PAS DU LABYRINTHE EN HAUT ET A DROITE
      return 0;
    if(ch.coordonnees[k].ligne >= longueur || ch.coordonnees[k].colonne >= largeur)    // IDEM A GAUCHE ET EN BAS
      return 0;
    if(k!=0) {
      lenABligne = fabs(ch.coordonnees[k].ligne - ch.coordonnees[k-1].ligne);
      lenABcolonne = fabs(ch.coordonnees[k].colonne - ch.coordonnees[k-1].colonne);
      if(lenABligne < 0 || lenABligne > 1)
        return 0;
      if(lenABcolonne < 0 || lenABcolonne > 1)
        return 0;
    }
    if(lab[ch.coordonnees[k].ligne][ch.coordonnees[k].colonne] == 1)  // VERIFICATION QUE TOUTE CASE SAUF LA DERNIERE N'EST PAS UN 1
      return 0;
    else if(k==ch.taille-1) {
      if(lab[ch.coordonnees[k].ligne][ch.coordonnees[k].colonne] !=2)    // VERIFICATION QUE LE DERNIER TERME MENE A UN 2
        return 0;
    }
  }
  if(lab[depart.ligne][depart.colonne]!=0) // VERIFICATION QUE LE PREMIER TERME MENE A UN 0
    return 0;
  if((depart.ligne != ch.coordonnees[0].ligne) && (depart.colonne != ch.coordonnees[0].colonne))
    return 0;
  return 1;
} 

void afficherChemin(chemin_t ch ){
  for(int k=0; k<ch.taille-1; ++k) {
    printf("(%d,%d), ", ch.coordonnees[k].ligne, ch.coordonnees[k].colonne);
  }
  printf("(%d,%d).", ch.coordonnees[ch.taille-1].ligne, ch.coordonnees[ch.taille-1].colonne);
}


/*Seconde partie*/

unsigned int completeM2(labyrinthe M2, unsigned int size, coordonnee_t* coordPossibles, unsigned int len, unsigned int index, chemin_t ch) {
  //printf("ENTREE EN COMPLETEM2 \n");
  for(int i=0; i<len; ++i) {
    //printf("coorPoss: (%d,%d)\n", coordPossibles[i].ligne, coordPossibles[i].colonne);
  }
  unsigned int cpt = 0;
  unsigned char dejaDepart = 0;
  for(int k=0; k<len; ++k) {
    dejaDepart = 0;
    if((coordPossibles[k].ligne == ch.coordonnees[0].ligne) && (coordPossibles[k].colonne == ch.coordonnees[0].colonne))
      dejaDepart = 1;
    if((M2[coordPossibles[k].ligne][coordPossibles[k].colonne] == 0 && dejaDepart == 0) || (M2[coordPossibles[k].ligne][coordPossibles[k].colonne] > index)) {
      M2[coordPossibles[k].ligne][coordPossibles[k].colonne] = index;
      coordPossibles[cpt].ligne = coordPossibles[k].ligne;
      coordPossibles[cpt].colonne = coordPossibles[k].colonne;
      cpt++;
    }
  }
  if(cpt <3)
    return cpt;
  return 2;
}

int checkWin(labyrinthe lab, coordonnee_t* possibles, int len) {
  for(int k=0; k<len; ++k) {
    if(lab[possibles[k].ligne][possibles[k].colonne] == 2)
      return k;
  }
  return 0;
}

chemin_t incrChemin(chemin_t chemin, coordonnee_t point) {
  chemin.coordonnees[chemin.taille].ligne = point.ligne;
  chemin.coordonnees[chemin.taille].colonne = point.colonne;
  chemin.taille++;
  return chemin;
}

/*
void recurParcourir(labyrinthe lab, labyrinthe M2, unsigned int size, chemin_t ch, unsigned int index) {
  printf("DEPART : (%d,%d)\n", ch.coordonnees[ch.taille-1].ligne, ch.coordonnees[ch.taille-1].colonne);
  printf("CHEMIN : ");
  afficherChemin(ch);  //plusCourtCheminDynamique(lab1, M2, 4, 4, coord);
  //afficherMatrice(M2, size, size);
  index++;
  coordonnee_t* possibles = (coordonnee_t *) malloc(8*sizeof(int));
  unsigned int len;
  len = deplacementsPossibles(lab, size, size, ch.coordonnees[ch.taille-1], possibles);
  printf("len1 - %d\n", len);
  for(int k=0; k<len; ++k) {
    printf("(%d , %d)\n", possibles[k].ligne, possibles[k].colonne);
  }
  if(len == 0) {
    return M2;
  }
  len = completeM2(M2, size, possibles, len, index, ch);
  printf("\nlen2 = %d", len);
  for(int i=0; i<len; ++i) {
    printf("\n(%d,%d)", possibles[i].ligne, possibles[i].colonne);
  }
  afficherMatrice(M2, size, size);
  if(len == 0) {
    return M2;
  }
  ch.taille++;
  for(int i=0; i<len; ++i) {
    if(size*size < ch.taille)   // EXPLAIN
      return M2;
    ch.coordonnees[ch.taille-1] = possibles[i];
    recurParcourir(lab, M2, size, ch, index);
  }
}
*/

void recurParcourir(labyrinthe lab, labyrinthe M2, unsigned int size, chemin_t ch, unsigned int index) {
  //printf("(%d,%d)  ", ch.coordonnees[ch.taille-1].ligne, ch.coordonnees[ch.taille-1].colonne);
  afficherMatrice(M2, size, size);
  index++;
  coordonnee_t* possibles = (coordonnee_t *) malloc(8*sizeof(int));
  unsigned int len;
  len = deplacementsPossibles(lab, size, size, ch.coordonnees[ch.taille-1], possibles);
  if(len == 0) {
    return M2;
  }
  len = completeM2(M2, size, possibles, len, index, ch);
  if(len == 0) {
    return M2;
  }
  ch.taille++;
  for(int i=0; i<len; ++i) {
    if(size*size < ch.taille)   // EXPLAIN
      return M2;
    ch.coordonnees[ch.taille-1] = possibles[i];
    recurParcourir(lab, M2, size, ch, index);
    /*printf("\n");
    for(int k=0; k<ch.taille-1; ++k)
      printf("       ");*/
  }
}

chemin_t init_chemin(coordonnee_t depart, unsigned int maxLen) {
  chemin_t ch;
  coordonnee_t* chCoords = (coordonnee_t *) malloc(maxLen*sizeof(int));
  ch.coordonnees = chCoords;
  ch.coordonnees[0].ligne=depart.ligne;
  ch.coordonnees[0].colonne=depart.colonne;
  ch.taille = 1;
  return ch;
}

unsigned int maximum(unsigned int value1, unsigned int value2) {
  if(value1 < value2)
    return value2;
  return value1;
}

unsigned int minimumPossibles(labyrinthe lab, labyrinthe M2, unsigned int size, coordonnee_t* possibles, unsigned int len, coordonnee_t posCourante) {
  unsigned int index = size*size;
  unsigned char caseRefuse = 0;
  for(int k=0; k<len; ++k) {
    //printf("(%d,%d)\n", possibles[k].ligne, possibles[k].colonne);
    if((M2[posCourante.ligne][posCourante.colonne] >= M2[possibles[k].ligne][possibles[k].colonne]) || (M2[posCourante.ligne][posCourante.colonne] == 0)){
      if(index > M2[possibles[k].ligne][possibles[k].colonne])
        index = M2[possibles[k].ligne][possibles[k].colonne];
      caseRefuse = 0;
    }
  }
  //printf("index min: %d , M2 : %d \n", index, M2[posCourante.ligne][posCourante.colonne]);
  return index;
}

void parcourirM2(labyrinthe lab, labyrinthe M2, unsigned int size, coordonnee_t depart) {
  printf("ENTREE EN PARCOURIR\n");
  coordonnee_t* possibles = (coordonnee_t *) malloc(8*sizeof(int));
  unsigned int len, index ;
  coordonnee_t posCourante;
  unsigned int itemp, jtemp = 0;
  for(int repet=0; repet<1.5*size; ++repet) {
    for(unsigned int i=depart.ligne; i<depart.ligne+size; ++i) {
      for(unsigned int j=depart.colonne; j<depart.colonne+size; ++j) {
        itemp = i%size;
        jtemp = j%size;
        posCourante.ligne = itemp;
        posCourante.colonne = jtemp;
        len = deplacementsPossibles(lab, size, size, posCourante, possibles);
        printf("posCourante(%d , %d) , lenPossible: %d\n", itemp, jtemp, len);
        printf("--- itemp: %d != depart.ligne: %d OR jtemp: %d != depart.colonne: %d\n", itemp, depart.ligne, jtemp, depart.colonne);
        if(itemp != depart.ligne || jtemp != depart.colonne){
          printf("--- lab[itemp][jtemp]: %d != 1\n", lab[itemp][jtemp]);
          if(lab[itemp][jtemp]!=1) {
            index = minimumPossibles(lab, M2, size, possibles, len, posCourante);
            printf("Returned index: %d\n", index);
            printf("Max distance: %d", maximum( abs(depart.ligne-itemp), abs(depart.colonne-jtemp)));
            if(index < maximum( abs(depart.ligne-itemp), abs(depart.colonne-jtemp)))
              M2[itemp][jtemp] = maximum( abs(depart.ligne-itemp), abs(depart.colonne-jtemp));
            else
              M2[itemp][jtemp] = index+1;
          }
        }
        afficherMatrice(M2, size, size);
      }
    }
  }
}

void tourbillonM2(labyrinthe lab, labyrinthe M2, unsigned int size, coordonnee_t depart) {
  printf("ENTREE EN TOURBILLON\n");
  coordonnee_t* possibles = (coordonnee_t *) malloc(8*sizeof(int));
  unsigned int len, index ;
  int depl, signe;
  coordonnee_t posCourante;
  int cpt;
  for(int repet=0; repet<size; repet++) {
    posCourante = depart;
    cpt = 0;
    for(int depl=1; depl<size*2; ++depl) {
      signe = depl%2;
      if(signe==0)
        signe = -1;
      for(int n=0; n<depl; ++n) {
        posCourante.colonne+=signe;
        if(((posCourante.colonne >= 0) && (posCourante.colonne < size)) && ((posCourante.ligne >= 0) && (posCourante.ligne < size))) {
          printf("Depl: %d, Case: (%d,%d)\n", depl, posCourante.ligne, posCourante.colonne);
          len = deplacementsPossibles(lab, size, size, posCourante, possibles);
          index = minimumPossibles(lab, M2, size, possibles, len, posCourante);
          if(M2[posCourante.ligne][posCourante.colonne]!=index+1){
            M2[posCourante.ligne][posCourante.colonne] = index+1;
            cpt++;
          }
        }
      }
      for(int n=0; n<depl; ++n) {
        posCourante.ligne+=signe;
        if(((posCourante.colonne >= 0) && (posCourante.colonne < size)) && ((posCourante.ligne >= 0) && (posCourante.ligne < size))) {
          printf("Depl: %d, Case: (%d,%d)\n", depl, posCourante.ligne, posCourante.colonne);
          len = deplacementsPossibles(lab, size, size, posCourante, possibles);
          index = minimumPossibles(lab, M2, size, possibles, len, posCourante);
          if(M2[posCourante.ligne][posCourante.colonne]!=index+1){
            M2[posCourante.ligne][posCourante.colonne] = index+1;
            cpt++;
          }
        }
      }
      afficherMatrice(M2, size, size);
      printf("\n");
    }
    if(cpt==0) {
      printf("RACCOURCI de: %d", repet);
      return;
    }
  }
}

chemin_t plusCourtCheminDynamique (labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart) {
  M2[depart.ligne][depart.colonne] = 0;
  tourbillonM2(lab, M2, largeur, depart);
  return;
}


/*
chemin_t plusCourtCheminDynamique (labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart) {
  chemin_t ch = init_chemin(depart, 1+largeur*longueur/2);
  unsigned index = 0;
  recurParcourir(lab, M2, largeur, ch, index);
  printf("\n\n\n\n GAGNEEEEEEEE \n");
  afficherMatrice(M2, largeur ,longueur);
  return ch;
}
*/

/*chemin_t plusCourtCheminDynamique (labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart) {
  parcourirM2(lab, M2, largeur, depart);
  return;
}
*/
chemin_t* tousPlusCourtsChemins(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  /*A faire*/
}


// VERIFICATION FUTURES:
// VERIFIER POUR MATRICE 1X1 , 2X2, 3X3.