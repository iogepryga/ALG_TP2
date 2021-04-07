#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef A234_H
#define A234_H
#include "a234.h"
#endif

#include "pile.h"



// FONCTIONS GENERALES :
#define max(a,b) ((a)>(b)?(a):(b))
#define nb_cles(a) (a->t-1)
#define derniere_cles(a) (a->t-2)
#define derniere_noeud(a) (a->t-1)

#define init2noeud(a,cle,fils1,fils2) a->t=2;a->cles[1]=cle;a->fils[1]=fils1;a->fils[2]=fils2;
#define init3noeud(a,cle1,cle2,fils1,fils2,fils3) a->t=3;a->cles[0]=cle1;a->cles[1]=cle2;a->fils[0]=fils1;a->fils[1]=fils2;a->fils[2]=fils3;
#define init4noeud(a,cle1,cle2,cle3,fils1,fils2,fils3,fils4) a->t=3;a->cles[0]=cle1;a->cles[1]=cle2;a->cles[2]=cle3;a->fils[0]=fils1;a->fils[1]=fils2;a->fils[2]=fils3;a->fils[3]=fils4;

// <--------------------------------->
/* 
 * Précondition : a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : Affiche les spécifications (2 noeuds 3 noeuds 4 noeuds) d'un noeud de manière formaté
 */
void afficher_noeud(Arbre234 a) {
  if(a == NULL)
    printf("NULL\n");
  else if(a->t == 0)
    printf("0noeud\n");
  else if(a->t == 2)
    printf("2noeud : (%d)\n", a->cles[1]);
  else if(a->t == 3)
    printf("3noeud : (%d,%d)\n", a->cles[0], a->cles[1]);
  else 
    printf("4noeud : (%d,%d,%d)\n", a->cles[0], a->cles[1], a->cles[2]);
  return;
}
// <--------------------------------->
/* 
 * Précondition : a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : renvoi la hauteur de l'arbre
 */
int hauteur (Arbre234 a) {
  if (a == NULL)
    return 0 ;
  if (a->t == 0)
    return 0 ;
  int h0 = hauteur (a->fils [0]) ;
  int h1 = hauteur (a->fils [1]) ;
  int h2 = hauteur (a->fils [2]) ;
  int h3 = hauteur (a->fils [3]) ;
  return 1 + max (max (h0,h1),max (h2,h3)) ;
} 
// <--------------------------------->
/* 
 * Précondition : a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : renvoi 1 si :
 * - tous les fils d'un noeud sont des 0noeud.
 * - a == NULL
 * - a est un 0noeud
 */
int dernier_noeud(Arbre234 a) {
  // if (a == NULL || a->t == 0)
  //   return 1;
  // if(a->t == 2 && a->fils[1]->t == 0 && a->fils[2]->t == 0)
  //   return 1;
  // if(a->t == 3 && a->fils[0]->t == 0 && a->fils[1]->t == 0 && a->fils[2]->t == 0)
  //   return 1;
  // if(a->t == 4 && a->fils[0]->t == 0 && a->fils[1]->t == 0 && a->fils[2]->t == 0 && a->fils[3]->t == 0)
  //   return 1;
  // return 0;
  return a == NULL 
        || a->t == 0 
        || (a->t == 2 && a->fils[1]->t == 0 && a->fils[2]->t == 0) 
        || (a->t == 3 && a->fils[0]->t == 0 && a->fils[1]->t == 0 && a->fils[2]->t == 0)
        || (a->t == 4 && a->fils[0]->t == 0 && a->fils[1]->t == 0 && a->fils[2]->t == 0 && a->fils[3]->t == 0);
}
// FIN FONCTIONS GENERALES



// POUR NOEUD_MAX :
// <--------------------------------->
/* 
 * Précondition : a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : la somme des clés du noeud donné
 */
int sum_cles(Arbre234 a) {
  if(a == NULL || a->t == 0)
    return 0;
  if(a->t == 2) {
    return a->cles[1];
  } else {
    int sum = 0;
    for(int i = 0 ; i < nb_cles(a) ; i++) {
      sum += a->cles[i];
    }
    return sum;
  }
}
// FIN POUR NOEUD_MAX



// POUR AFFICHAGE_CES_TRIEES_NONRECURSIVE
typedef struct {
  int indice ;
  pnoeud234 noeud ;
} elem, *pelem ;

pelem elem_allouer() {
  return (pelem)malloc(sizeof(elem));
}
// FIN POUR AFFICHAGE_CES_TRIEES_NONRECURSIVE



// POUR DETRUIRE CLE :
Arbre234 noeud_parent(Arbre234 a, Arbre234 filston) { // précondition : filston appartient à a !
  if(a == NULL || filston == NULL || a->t == 0 || filston->t == 0)
    return NULL;
  if(a == filston)
    return filston;
  while(a->t != 0) {
    if(a->t == 2) { // à enlever si on corrige l'implem de ajout-cle et lire_affichage
      if(a->fils[1] == filston || a->fils[2] == filston) {
        return a;
      } else if (filston->cles[1] < a->cles[1]) {
        a = a->fils[1];
      } else {
        a = a->fils[2];
      }
    } else {
      for(int i = 0 ; i < nb_cles(a) ; i ++) {
        if(a->fils[i] == filston) {
          return a;
        } else if (filston->cles[1] < a->cles[i]) {
          a = a->fils[i];
          break;
        } else if (i == derniere_cles(a)) {
          a = a->fils[derniere_noeud(a)];
        }
      }
    }
  }
  return NULL ;
}

int ou_est_ma_cle(Arbre234 a, int cle) { // Précondition : 
  if(a == NULL || a->t == 0)
    return -1;
  if(a->t > 2) {
    for(int i = 0 ; i < nb_cles(a); i++) {
      if(a->cles[i] == cle)
        return i;
    }
    return -1;
  }
  if (a->cles[1] != cle)
    return -1;
  return 1;
}

int ou_est_mon_fils(Arbre234 a, Arbre234 filston) { // Précondition : 
  if(a == NULL || a->t == 0)
    return -1;
  if(a->t > 2) {
    for(int i = 0 ; i < a->t; i++) {
      if(a->fils[i] == filston)
        return i;
    }
  } else {
    if(a->fils[1] == filston)
        return 1;
    if(a->fils[2] == filston)
        return 2;
  }
  return -1;
}

void fusion(Arbre234 a) {
  if(a == NULL && a->t != 2 && a->fils[1]->t != 2 && a->fils[2]->t != 2)
    return;
  Arbre234 tmp;
  a->cles[0] = a->fils[1]->cles[1];
  a->cles[2] = a->fils[2]->cles[1];

  a->fils[0] = a->fils[1]->fils[1];

  tmp = a->fils[1];
  a->fils[1] = tmp->fils[2];
  free(tmp);

  a->fils[3] = a->fils[2]->fils[2];

  tmp = a->fils[2];
  a->fils[2] = tmp->fils[1];
  free(tmp);
}
// FIN POUR DETRUIRE CLE



// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// <--------------------------------->
/* 
 * Précondition :  a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : nombre de clés total dans l'arbre. Si racine vide ou feuille -> return 0
 * Comment : Fonction récursive postfixe, parcours en profondeur de tout l'arbre. Condition d'arret : a == NULL ou a est une feuille, c'est à dire un noeud avec 0 clé.
 * /!\ Cette fonction va dans les feuilles /!\
 * 3 cas :
 * 1 : c'est un 2noeud -> appel recursif sur ses 2 fils aux indices 1 et 2 du array "fils" et on ajout 1 (un 2noeud à 1 clé);
 * 2 : c'est un 3 ou 4noeud -> appel recursif sur leur fils qui sont cette fois-ci rangé dans l'ordre dans l'array "fils" donc on boucle simplement sur les fils
 * 3 : c'est un 0noeud , une feuille sans clé -> pas de clé? return 0
 */
int NombreCles (Arbre234 a) {
  if(a == NULL || a->t == 0)
    return 0;
  if (a->t == 2) // à enlever si on corrige l'implémentation de ajout-cle et lire_affichage
    return NombreCles(a->fils[1]) + NombreCles(a->fils[2]) + 1;
  int sum = 0;
  for(int i = 0; i < a->t ; i++) {
    sum += NombreCles(a->fils[i]);
  }
  return sum + nb_cles(a);
}
// <--------------------------------->
/*
 * Précondition :  a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : La clé max de tout l'arbre a. Si racine vide ou feuille -> return 0
 * Comment : Fonction récursive de base, on appel recursivement sur le fils "le plus à droite" tant que celui-ci n'est une feuille .
 * Dans ce cas, on retourne la cle la plus à droite de ce dernier noeud.
 */
int CleMax (Arbre234 a) {
  if(a == NULL || a->t == 0)
    return 0;
  if (a->t == 2) { // à enlever si on corrige l'implémentation de ajout-cle et lire_affichage
    if(a->fils[2]->t != 0)
      return CleMax(a->fils[2]);
    else
      return a->cles[1];
  } else {
    if(a->fils[derniere_noeud(a)]->t != 0)
      return CleMax(a->fils[derniere_noeud(a)]);
    else
      return a->cles[derniere_cles(a)];
  }
}
// <--------------------------------->
/*
 * Précondition :  a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : La clé min de tout l'arbre a. Si racine vide ou feuille -> return 0
 * Comment : Fonction récursive de base, on appel recursivement sur le fils "le plus à gauche" tant que celui-ci n'est une feuille .
 * Dans ce cas, on retourne la cle la plus à gauche de ce dernier noeud.
 */
int CleMin (Arbre234 a) {
  if(a == NULL || a->t == 0)
    return 0;
  if(a->t == 2) { // à enlever si on corrige l'implem de ajout-cle et lire_affichage
    if(a->fils[1]->t != 0)
      return CleMin(a->fils[1]);
    else 
      return a->cles[1];
  } else {
    if(a->fils[0]->t != 0)
      return CleMin(a->fils[0]);
    else
      return a->cles[0];
  }
}
// <--------------------------------->
/*
 * Précondition :  a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : La noeud contenant la cle , si pas trouvé renvoi NULL
 * Comment : Fonction non recursive
 * Le principe est le suivant : on cherche la position de la cle parmis les cles du noeud exploré actuellement, avec ça on sait dans quel fils aller ensuite.
 * On s'arrête dès qu'on a atteint le fond de l'arbre (a->t == 0) ou alors lorsqu'on a trouvé la cle
 * Dans le cas d'un 2noeud : si la cle recherchée est plus grande que la clé du noeud exploré : on explore le fils "à droite" sinon celui "de gauche"
 * Pour un 3 et 4 noeud, on boucle sur les cles, dès qu'on trouve une cle du noeud supérieur à celle recherchée , on explore le fils "juste à gauche"
 * (c'est à dire celui qui contient des clés comprises entre la cle du noeud d'avant (itération précédente) et la cle du noeud etudié actuellement).
 * Si aucune des clés du noeud n'est supéreur (on a atteint la dernière cle (i == derniere_cles(a)), alors on explore le dernier fils ("le plus à droite").
 */
Arbre234 RechercherCle (Arbre234 a, int cle) {
  if(a == NULL)
    return NULL;
  while(a->t != 0) {
    if(a->t == 2) { // à enlever si on corrige l'implémentation de ajout-cle et lire_affichage
      if(a->cles[1] == cle) {
        return a;
      } else if (cle < a->cles[1]) {
        a = a->fils[1];
      } else {
        a = a->fils[2];
      }
    } else {
      for(int i = 0 ; i < nb_cles(a) ; i ++) {
        if(a->cles[i] == cle) {
          return a;
        } else if (cle < a->cles[i]) {
          a = a->fils[i];
          break;
        } else if (i == derniere_cles(a)) {
          a = a->fils[derniere_noeud(a)];
        }
      }
    }
  }
  return NULL ;
}
// <--------------------------------->
/*
<<<<<<< HEAD
 * Précondition : a est NULL OU pointe sur un structure Arbre234 et pas une adresse qui correspond pas à une structure Arbre234
 * Sortie : R mais modifie les valeur pointé par feuille, noeud2, noeud3 et noeud4
 * Comment : Vraiment besoin d'expliqué ? Fonction recursive préfixe. Parcours en profondeur de tout l'arbre. Condition d'arret : a est NULL ou a pointe sur une feuille
 * On incremente les valeurs en fonction des specification du noeud exploré.
=======
 * Précondition :  a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : Ne renvoi rien mais modifie les valeur pointées par feuille, noeud2, noeud3 et noeud4
 * Comment : Fonction recursive préfixe. Parcours en profondeur de tout l'arbre. Condition d'arret : a est NULL ou a pointe sur une feuille
 * On incremente les valeurs en fonction des spécification du noeud.
>>>>>>> 430db8a97436e316609a7be8ffacf93dfd315b93
 */
void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4) { // # invitation recursive 
  if(a == NULL)
    return;
  if(a->t == 0) {
    *feuilles +=1;
    return;
  }
  if(a->t == 2) { // à enlever si on corrige l'implémentation de ajout-cle et lire_affichage
    *noeud2 += 1;
    AnalyseStructureArbre(a->fils[1],feuilles,noeud2,noeud3,noeud4);
    AnalyseStructureArbre(a->fils[2],feuilles,noeud2,noeud3,noeud4);
  } else {
    if(a->t == 3)
      *noeud3 += 1;
    else
      *noeud4 += 1;
    for(int i = 0 ; i < a->t ; i++) 
      AnalyseStructureArbre(a->fils[i],feuilles,noeud2,noeud3,noeud4);
  }
}
// <--------------------------------->
/*
 * Précondition :  a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : noeud avec la somme des cles la plus grande de tout l'arbre.
 * Comment : Fonction recursive postfix. Parcours en profondeur de tout l'arbre. Condition d'arret : a est NULL ou a pointe sur une feuille ou tout les fils du noeud sont des feuilles.
 * On cherche le noeud_max de chacun des fils puis on regarde lequel à la somme de ses clés la plus grande et on le retourne.
 * PS : Le array tmp sert juste à enregister le noeud de chacun des fils pour les traiter ensuite.
 */
Arbre234 noeud_max (Arbre234 a) {
  if(a == NULL || a->t == 0)
    return NULL;
  if(dernier_noeud(a))
    return a;
  Arbre234 tmp[4], max;
  if(a->t == 2) { // à enlever si on corrige l'implémentation de ajout-cle et lire_affichage
    tmp[0] = noeud_max(a->fils[1]);
    tmp[1] = noeud_max(a->fils[2]);
    if(sum_cles(tmp[0]) < sum_cles(tmp[1]))
      return tmp[1];
    else 
      return tmp[0];
  } else {
    for(int i = 0 ; i < a->t; i++)
      tmp[i] = noeud_max(a->fils[i]);
    max = a;
    for(int i = 1; i < a->t ; i++) {
      if(sum_cles(tmp[i]) > sum_cles(max))
        max = tmp[i];
    }
    return max;
  }
}
// <--------------------------------->
/*
 * Précondition :  a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : noeud avec la somme des cles la plus grande de tout l'arbre.
 * Comment : Fonction itérative.
 * Principe : Onutilise deux piles pour repéré les changement de niveaux/profondeur
 */
void Afficher_Cles_Largeur (Arbre234 a) {
  if(a == NULL || a->t == 0) {printf("\n"); return ;}
  ppile_t pile[2];pile[0] = creer_pile();pile[1] = creer_pile();
  int ipile = 0;
  empiler(pile[ipile],a);
  Arbre234 tmp;
  while(!pile_vide(pile[ipile])) {
    while(!pile_vide(pile[ipile])) {
      tmp = depiler(pile[ipile]);
      if(tmp->t == 2) { // à enlever si on corrige l'implémentation de ajout-cle et lire_affichage
        if(tmp->fils[1] != NULL && tmp->fils[1]->t != 0)
          empiler(pile[!ipile],tmp->fils[1]);
        if(tmp->fils[2] != NULL && tmp->fils[2]->t != 0)
          empiler(pile[!ipile],tmp->fils[2]);
        printf("%d  ", tmp->cles[1]);
      } else {
        for(int i = 0 ; i < tmp->t ; i++) {
          if(tmp->fils[i] != NULL && tmp->fils[i]->t != 0)
            empiler(pile[!ipile],tmp->fils[i]);
        }
        for(int i = 0 ; i < nb_cles(tmp) ; i++) {
          printf("%d ",tmp->cles[i]);
        }
        printf(" ");
      }
    }
    ipile = !ipile;
    printf("\n");
  }
  detruire_pile(pile[0]);
  detruire_pile(pile[1]);
  return ;
}
// <--------------------------------->
/*
 * Précondition :  a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : noeud avec la somme des cles la plus grande de tout l'arbre.
 * Comment : Fonction recursive infixe. Parcours en profondeur de tout l'arbre. Condition d'arret : a est NULL ou a pointe sur une feuille.
 * On imprime une cle entre 2 explorations de fils.
 * Pour les 3noeud et 4noeud : on boucle sur les cles.
 */
void Affichage_Cles_Triees_Recursive (Arbre234 a) {
  if(a == NULL || a->t == 0)
    return;
  if(a->t == 2) {
    Affichage_Cles_Triees_Recursive(a->fils[1]);
    printf("%d ", a->cles[1]);
    Affichage_Cles_Triees_Recursive(a->fils[2]);
  } else {
    for(int i = 0 ; i < nb_cles(a) ; i++) {
      Affichage_Cles_Triees_Recursive(a->fils[i]);
      printf("%d ", a->cles[i]);
      if(i == derniere_cles(a)) {
        Affichage_Cles_Triees_Recursive(a->fils[derniere_noeud(a)]);
      }
    }
  }
}
// <--------------------------------->
/*
 * Précondition :  a est NULL ou point sur un structure noeud234 valide. a ne doit pas être l'adresse d'une structure autre que noeud234.
 * Sortie : noeud avec la somme des cles la plus grande de tout l'arbre.
 * Comment : Fonction itérative.
 * L'idée est de se servir d'une pile comme stack.
 * A tout moment, la tête de pile contient le noeud parent du noeud actuel.
 */
void Affichage_Cles_Triees_NonRecursive (Arbre234 a) {
  if(a == NULL || a->t == 0)
    return;
  pelem tmp = elem_allouer(),tmp_bis; tmp->noeud=a; tmp->indice = 0;
  ppile_t pile = creer_pile();
  empiler(pile,tmp);
  while(!pile_vide(pile)) {
    tmp = (pelem)depiler(pile);
    if(tmp->indice < tmp->noeud->t) {
      tmp->indice += 1;
      empiler(pile,tmp);
      tmp_bis = elem_allouer(); tmp_bis->noeud = tmp->noeud->fils[tmp->indice - 1 + (tmp->noeud->t==2)]; tmp_bis->indice = 0;
      empiler(pile,tmp_bis);
      if(tmp->indice != 1)
        printf("%d ", tmp->noeud->cles[tmp->indice - 2 + (tmp->noeud->t==2)]);
    } else {
      free(tmp);
    }
  }
  detruire_pile(pile);
}


int main (int argc, char **argv) {
  Arbre234 a ;

  if (argc != 2) {
    fprintf (stderr, "il manque le parametre nom de fichier\n") ;
    exit (-1) ;
  }
  a = lire_arbre (argv [1]) ;

  printf ("\n==== Afficher arbre ====\n") ;
  afficher_arbre (a, 0) ;

  printf ("\n==== pointer ====\n") ;
  printf("a = %p\n",a) ;
  printf("a->fils[1] = %p\n",a->fils[1]) ;
  printf("a->fils[2] = %p\n",a->fils[2]) ;

  printf ("\n==== a->t ====\n") ;
  printf("a->t = %d\n",a->t) ;
  printf("a->fils[1]->t = %d\n",a->fils[1]->t) ;
  printf("a->fils[2]->t = %d\n",a->fils[2]->t) ;

  printf ("\n==== sum_cles ====\n") ;
  printf("sum_cles(a) = %d\n",sum_cles(a)) ;
  printf("sum_cles(a->fils[1]) = %d\n",sum_cles(a->fils[1])) ;
  printf("sum_cles(a->fils[2]) = %d\n",sum_cles(a->fils[2])) ;

  printf ("\n==== dernier_noeud ====\n") ;
  printf("dernier_noeud(a) = %d\n",dernier_noeud(a)) ;
  printf("dernier_noeud(a->fils[1]) = %d\n",dernier_noeud(a->fils[1])) ;
  printf("dernier_noeud(a->fils[2]) = %d\n",dernier_noeud(a->fils[2])) ;

  printf ("\n==== NombreCles ====\n") ;
  printf("NombreCles(a) = %d\n",NombreCles(a)) ;
  printf("NombreCles(a->fils[1]) = %d\n",NombreCles(a->fils[1])) ;
  printf("NombreCles(a->fils[2]) = %d\n",NombreCles(a->fils[2])) ;

  printf ("\n==== CleMax ====\n") ;
  printf("CleMax(a) = %d\n",CleMax(a)) ;
  printf("CleMax(a->fils[1]) = %d\n",CleMax(a->fils[1])) ;
  printf("CleMax(a->fils[2]) = %d\n",CleMax(a->fils[2])) ;

  printf ("\n==== CleMin ====\n") ;
  printf("CleMin(a) = %d\n",CleMin(a)) ;
  printf("CleMin(a->fils[1]) = %d\n",CleMin(a->fils[1])) ;
  printf("CleMin(a->fils[2]) = %d\n",CleMin(a->fils[2])) ;

  printf ("\n==== RechercherCle ====\n");
  printf("RechercherCle(a,50) : ");
  afficher_noeud(RechercherCle(a,50));
  printf("RechercherCle(a->fils[1],50) : ");
  afficher_noeud(RechercherCle(a->fils[1],50));
  printf("RechercherCle(a->fils[2],50) : ");
  afficher_noeud(RechercherCle(a->fils[2],50));

  int n2 = 0, n3 = 0, n4 = 0, feuils = 0;
  printf ("\n==== AnalyseStructureArbre ====\n") ;
  AnalyseStructureArbre(a,&feuils,&n2,&n3,&n4);
  printf("AnalyseStructureArbre de a : %d, %d, %d, %d\n", feuils, n2, n3, n4);
  n2 = 0; n3 = 0; n4 = 0; feuils = 0;
  AnalyseStructureArbre(a->fils[1],&feuils,&n2,&n3,&n4);
  printf("AnalyseStructureArbre de a->fils[1] : %d, %d, %d, %d\n", feuils, n2, n3, n4);
  n2 = 0, n3 = 0, n4 = 0, feuils = 0;
  AnalyseStructureArbre(a->fils[2],&feuils,&n2,&n3,&n4);
  printf("AnalyseStructureArbre de a->fils[2] : %d, %d, %d, %d\n", feuils, n2, n3, n4);

  printf ("\n==== noeud_max ====\n") ;
  printf("noeud_max(a) : ");
  afficher_noeud(noeud_max(a));
  printf("noeud_max(a->fils[1]) : ");
  afficher_noeud(noeud_max(a->fils[1]));
  printf("noeud_max(a->fils[2]) : ");
  afficher_noeud(noeud_max(a->fils[2]));

  printf ("\n==== Afficher_Cles_Largeur ====\n") ;
  printf("Afficher_Cles_Largeur(a) : \n"); Afficher_Cles_Largeur(a);
  printf("Afficher_Cles_Largeur(a->fils[1]) : \n"); Afficher_Cles_Largeur(a->fils[1]);
  printf("Afficher_Cles_Largeur(a->fils[2]) : \n"); Afficher_Cles_Largeur(a->fils[2]);

  printf ("\n==== Affichage_Cles_Triees_Recursive ====\n") ;
  printf("Affichage_Cles_Triees_Recursive(a) : "); Affichage_Cles_Triees_Recursive(a); printf("\n");
  printf("Affichage_Cles_Triees_Recursive(a->fils[1]) : "); Affichage_Cles_Triees_Recursive(a->fils[1]); printf("\n");
  printf("Affichage_Cles_Triees_Recursive(a->fils[2]) : "); Affichage_Cles_Triees_Recursive(a->fils[2]); printf("\n");

  printf ("\n==== Affichage_Cles_Triees_NonRecursive ====\n") ;
  printf("Affichage_Cles_Triees_NonRecursive(a) : "); Affichage_Cles_Triees_NonRecursive(a); printf("\n");
  printf("Affichage_Cles_Triees_NonRecursive(a->fils[1]) : "); Affichage_Cles_Triees_NonRecursive(a->fils[1]); printf("\n");
  printf("Affichage_Cles_Triees_NonRecursive(a->fils[2]) : "); Affichage_Cles_Triees_NonRecursive(a->fils[2]); printf("\n");

  printf ("\n\n==== Detruire_Cle ====\n") ;
  //On gérère l'arbre un arbre :
  Arbre234 tmp[23], racine = tmp[0];
  for(int i = 0; i < 23 ; i++) {
    tmp[i] = allouer_noeud();
  }
  init2noeud(tmp[0],16,tmp[1],tmp[2]); // P
  init3noeud(tmp[1],3,8,tmp[3],tmp[4],tmp[5]); // C,H
  init2noeud(tmp[2],22,tmp[6],tmp[7]); // V
  init3noeud(tmp[3],1,2,tmp[8],tmp[9],tmp[10]); // A,B
  init3noeud(tmp[4],5,6,tmp[11],tmp[12],tmp[13]); // E,F
  init2noeud(tmp[5],14,tmp[14],tmp[15]); // N
  init3noeud(tmp[6],18,19,tmp[16],tmp[17],tmp[18]); // R,S
  init4noeud(tmp[7],24,25,26,tmp[19],tmp[20],tmp[21],tmp[22]); // X,Y,Z

  int ordre_destruction[11] = {1,14,8,18,3,16,5,6,22,2,24}; // A,N,H,R,C,P,E,F,V,B,X,


  printf("\nArbre de départ: \n");
  afficher_arbre (racine, 0) ;

  for(int i = 0 ; i < 11 ; i++) {
    printf("\nDetruire_cle(%d) (cad %c) :\n",ordre_destruction[i],(char)(ordre_destruction[i]+((int)'A')-1));
    // Detruire_cle(&racine,ordre_destruction[i]);
    afficher_arbre (racine, 0) ;
  } 



}
