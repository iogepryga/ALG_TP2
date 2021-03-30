#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define nb_cles(a) (a->t-1)
#define derniere_cles(a) (a->t-2)
#define derniere_noued(a) (a->t-1)


int hauteur (Arbre234 a)
{
  int h0, h1, h2, h3 ;
  
  if (a == NULL)
    return 0 ;

  if (a->t == 0)
    return 0 ;

  h0 = hauteur (a->fils [0]) ;
  h1 = hauteur (a->fils [1]) ;
  h2 = hauteur (a->fils [2]) ;
  h3 = hauteur (a->fils [3]) ;

  return 1 + max (max (h0,h1),max (h2,h3)) ;
} 

int NombreCles (Arbre234 a)
{
  if(a == NULL) {
    return 0;
  } else if (a->t == 0) {
    return 0;
  //} else if (a->t == 2 || a->t == 3 || a->t == 4) {
  } else {
    int sum = 0;
    for(int i = 0; i < a->t ; i++) {
      sum += NombreCles(a->fils[i]);
    }
    return sum + (a->t -1);
  }
  // return 0 ;
}

int CleMax (Arbre234 a)
{
  if(a == NULL) {
    return 0;
  } else if (a->t == 0) {
    return 0;
  } else {
    while(a->fils[a->t-1]->t != 0) {
      a = a->fils[a->t-1];
    }
    return a->cles[derniere_cles(a)];
  }
}

int CleMin (Arbre234 a)
{
  if(a == NULL) {
    return 0;
  } else if (a->t == 0) {
    return 0;
  } else {
    while(a->fils[0]->t != 0) {
      a = a->fils[0];
    }
    return a->cles[0];
  }
}

Arbre234 RechercherCle (Arbre234 a, int cle)
{
  if(a == NULL)
    return NULL;
  while(a->t != 0) {
    for(int i = 0 ; i < nb_cles(a) ; i ++) {
      if(a->cles[i] == cle) {
        return a;
      } else if (a->cles[i] < cle) {
        a = a->fils[i];
        break;
      } else if (i == derniere_cles(a)) {
        a = a->fils[derniere_noued(a)];
      }
    }
  }
  return NULL ;
}

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4) // # invitation recursive
{
  /*
     calculer le nombre de feuilles, de 2-noeuds, 3-noeuds,et 4-noeuds
  */
}

Arbre234 noeud_max (Arbre234 a)
{
  /*
    Retourne le noeud avec la somme maximale des cles internes
  */
  
  return NULL ;
}


void Afficher_Cles_Largeur (Arbre234 a)
{
  /*
    Afficher le cles de l'arbre a avec
    un parcours en largeur
  */

  return ;
}

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
  /* 
     Afficher les cles en ordre croissant
     Cette fonction sera recursive
  */
     
}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
    /* 
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */

}


void Detruire_Cle (Arbre234 *a, int cle)
{
  /*
    retirer la cle de l'arbre a
  */

  return ;
}




int main (int argc, char **argv)
{
  Arbre234 a ;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv [1]) ;

  printf ("==== Afficher arbre ====\n") ;
  
  afficher_arbre (a, 0) ;

}
