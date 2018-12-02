/*Labyrinthe.c*/

#include "labyrinthe.h"
#include <math.h>

typedef struct CHEMINTAB {
  int size; 
  chemin_t* chList;
} chTab_t;
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
  printf("(%d,%d).\n", ch.coordonnees[ch.taille-1].ligne, ch.coordonnees[ch.taille-1].colonne);
}


/*Seconde partie*/

chemin_t incrChemin(chemin_t chemin, coordonnee_t point) {
  chemin.coordonnees[chemin.taille++] = point;
  return chemin;
}

chemin_t init_chemin(unsigned int maxLen) {
  chemin_t ch;
  ch.coordonnees = (coordonnee_t *) malloc(maxLen*sizeof(coordonnee_t));
  ch.taille = 0;
  return ch;
}

unsigned int minimumPossibles(labyrinthe lab, labyrinthe M2, unsigned int size, coordonnee_t* possibles, unsigned int len, coordonnee_t posCourante) {
  unsigned int index = size*size;
  unsigned char caseRefuse = 0;
  for(int k=0; k<len; ++k) {
    if((M2[posCourante.ligne][posCourante.colonne] >= M2[possibles[k].ligne][possibles[k].colonne]) || (M2[posCourante.ligne][posCourante.colonne] == 0)){
      if(index > M2[possibles[k].ligne][possibles[k].colonne])
        index = M2[possibles[k].ligne][possibles[k].colonne];
      caseRefuse = 0;
    }
  }
  return index;
}


void tourbillonM2(labyrinthe lab, labyrinthe M2, unsigned int size, coordonnee_t depart) {
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
            if(lab[posCourante.ligne][posCourante.colonne] != 1) {
              len = deplacementsPossibles(lab, size, size, posCourante, possibles);
              index = minimumPossibles(lab, M2, size, possibles, len, posCourante);
              if(M2[posCourante.ligne][posCourante.colonne]!=index+1){
                M2[posCourante.ligne][posCourante.colonne] = index+1;
                cpt++;
              }
          }
        }
      }
      for(int n=0; n<depl; ++n) {
        posCourante.ligne+=signe;
        if(((posCourante.colonne >= 0) && (posCourante.colonne < size)) && ((posCourante.ligne >= 0) && (posCourante.ligne < size))) {
          if(lab[posCourante.ligne][posCourante.colonne] != 1) {
            len = deplacementsPossibles(lab, size, size, posCourante, possibles);
            index = minimumPossibles(lab, M2, size, possibles, len, posCourante);
            if(M2[posCourante.ligne][posCourante.colonne]!=index+1) {
              M2[posCourante.ligne][posCourante.colonne] = index+1;
              cpt++;
            }
          }
        }
      }
    }
    if(cpt==0) {
      return;
    }
  }
}

coordonnee_t smallestExit(labyrinthe lab, labyrinthe M2, unsigned int size) {
  coordonnee_t exitMin;
  unsigned int indexMin = size*size;
  for(int i=0; i<size; ++i) {
    for(int j=0; j<size; ++j) {
      if(lab[i][j] == 2) {
        if(indexMin > M2[i][j]) {
          indexMin = M2[i][j];
          exitMin.ligne = i;
          exitMin.colonne = j;
        }
      }
    }
  }
  return exitMin;
}

chemin_t wayToExit(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, chemin_t ch) {  // LA POSITION COURANTE EST CH[-1]
  coordonnee_t* coordPossible = (coordonnee_t *) malloc(8*sizeof(int));
  int posLigne = ch.coordonnees[ch.taille-1].ligne;
  int posColonne = ch.coordonnees[ch.taille-1].colonne;
  int len = deplacementsPossibles(lab, largeur, longueur, ch.coordonnees[ch.taille-1], coordPossible);
  unsigned int cpt = 0;
  for(int k=0; k<len; ++k) {
    if(M2[coordPossible[k].ligne][coordPossible[k].colonne] == M2[posLigne][posColonne]-1) {
      coordPossible[cpt++] = coordPossible[k];
    }
  }
  if(cpt>0) {
    ch = incrChemin(ch, coordPossible[0]);
    if(M2[coordPossible[0].ligne][coordPossible[0].colonne] == 0) {
      return ch;
    }
    return wayToExit(lab, M2, largeur, longueur, ch);
  } 
}

chemin_t plusCourtCheminDynamique (labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart) {
  M2[depart.ligne][depart.colonne] = 0;
  tourbillonM2(lab, M2, largeur, depart);
  coordonnee_t posExit = smallestExit(lab, M2, largeur);
  chemin_t chemin = init_chemin(M2[posExit.ligne][posExit.colonne]+1);
  chemin = incrChemin(chemin, posExit);
  chemin = wayToExit(lab, M2, largeur, longueur, chemin);
  return chemin;
}

chemin_t copyChTab(chemin_t copy, chemin_t ch) {
  copy.taille = ch.taille;
  for(int k=0; k<ch.taille; k++) {
    copy.coordonnees[k].ligne = ch.coordonnees[k].ligne;
    copy.coordonnees[k].colonne = ch.coordonnees[k].colonne;
  }
  return copy;
}

chTab_t wayToExitAll(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, int maxLen, chTab_t allChemin) {
  coordonnee_t* coordPossible = (coordonnee_t *) malloc(8*sizeof(int));
  int actualIndex = maxLen-1;
  unsigned int cpt;
  unsigned int len;
  int preSizeChemin;
  while(actualIndex>=0) {
    preSizeChemin = allChemin.size;
    for(int nbCh=0; nbCh<preSizeChemin; nbCh++) {
      len = deplacementsPossibles(lab, largeur, longueur, allChemin.chList[nbCh].coordonnees[allChemin.chList[nbCh].taille-1], coordPossible);  
      cpt=0;
      for(int t=0; t<len; ++t) {
        if(M2[coordPossible[t].ligne][coordPossible[t].colonne] == actualIndex)
          coordPossible[cpt++] = coordPossible[t];
      }
  
      allChemin.chList[nbCh].coordonnees[allChemin.chList[nbCh].taille++] = coordPossible[0];  //ASSIGN COORDPOSSIBLE[0]

      if(cpt>1) {
        for(int a=1; a<cpt; ++a) {
          allChemin.chList[allChemin.size] = copyChTab(allChemin.chList[allChemin.size], allChemin.chList[nbCh]);  //DUPLICATION DE LA TABLE nbCh
          allChemin.size++;
          allChemin.chList[allChemin.size-1].coordonnees[allChemin.chList[nbCh].taille-1].ligne = coordPossible[a].ligne;
          allChemin.chList[allChemin.size-1].coordonnees[allChemin.chList[nbCh].taille-1].colonne = coordPossible[a].colonne;
        }
      }
    }
    actualIndex--;
  }
  return allChemin;
}


chemin_t* tousPlusCourtsChemins(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  M2[depart.ligne][depart.colonne] = 0;
  tourbillonM2(lab, M2, largeur, depart);
  coordonnee_t posExit = smallestExit(lab, M2, largeur);
  chTab_t allChemin;
  allChemin.chList = (chemin_t *) malloc((M2[posExit.ligne][posExit.colonne]+1)*sizeof(chemin_t));
  for(int k=0; k<(M2[posExit.ligne][posExit.colonne]+1); ++k) {
    allChemin.chList[k] = init_chemin(M2[posExit.ligne][posExit.colonne]+1);
  }
  allChemin.size = 1;
  allChemin.chList[0].coordonnees[0] = posExit;
  allChemin.chList[0].taille = 1;
  printf("\n");
  allChemin = wayToExitAll(lab, M2, largeur, longueur, M2[posExit.ligne][posExit.colonne], allChemin);
  return allChemin.chList;
}