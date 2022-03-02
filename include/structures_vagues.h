#ifndef __DIVERS_H_
#define __DIVERS_H_
#include <stdio.h>
#include <stdlib.h>
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
