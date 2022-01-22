#include <stdio.h>
#include <stdlib.h>

typedef struct def{
	int type_def;
	char *nom_fichier;
	int degat;
}defense;

typedef struct joue{
	int argent;
	int pv;
	char *nom;
	entite *ent;
	entite *suiv;
	entite *prec;
}joueur;

typedef struct entity{
	int type_entite;
	int pv;
	int degat;
	int x;
	char *nom_fichier;
}entite;

typedef struct vague{
	entite *ent;
	vague *suiv;
	vague *prec;
}wave;

typedef struct part{
	wave *vague;
	part *suiv;
}partie_surv;

typedef struct partc{
	entite *ent;
	partc *suiv;
	partc *prec;
}partie_class;
