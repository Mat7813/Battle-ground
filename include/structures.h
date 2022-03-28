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
	int create;/*si le joueur est en train de créer ou non des unités (1 ou 0)*/
	int x_create;
	char nom[50];
	char argent_img[15][22]; //correspond aux fichiers contenant les noms des images pour l'argent (0.png, 1.png etc...)
}joueur;

#endif
