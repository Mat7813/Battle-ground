#ifndef __STRUCTURES_H_
#define __STRUCTURES_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct mes{
	int temps; /*temps d'affichage*/
	char nom_fichier[100];
	int x;
	int y;
}message;

typedef struct def{
	int indice_vie;
	char nom_fichier[100];
	int degat;
	int temps; /*interval entre chaque tir*/
	int x;
	int y;
}defense;

typedef struct tir_s{
	int indice_vie; /*Cet indice sert à savoir si une entite doit etre détruite ou pas lorsqu'elle est modifiée dans une autre fonction. Cela permet de la détruire dans les bonnes fonctions et éviter les erreur de segmentation*/
	int x;
	int y;
	char nom_fichier[100];
}tir;

typedef struct joue{
	tir *t;
	defense *def;
	int argent;
	int pv;
	char nom[50];
}joueur;

typedef struct entity{
	int attaque; /*valeur qui correspon à l'attaque si l'entité doit attaquer ou non*/
	int pv;
	int degat;
	int x;
	int y;
	int x_barre;
	int y_barre;
	int temps; /*valeur qui correspond au nombre d'itérations de boucles à attendre avant qu'il commence à avancer*/
	char nom_fichier[100];
	char nom_fichier_attaque[100];
	int montant; /*indicateur permettant de savoir si les images sont en phases montantes ou ascendantes*/
}entite;

typedef struct wave{
 entite *ent;
 struct wave *suiv;
 struct wave *prec;
}t_wave;

#endif
