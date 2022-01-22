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
}joueur;

typedef struct entity{
	int type_entite;
	int pv;
	int degat;
	int x;
	char *nom_fichier;
}entite;

typedef struct wave{
 entite *ent;
 struct wave *suiv;
 struct wave *prec;
}t_wave;

typedef struct part{
	t_wave *vague;
	struct part *suiv;
}partie_surv;

typedef struct partc{
	entite *ent;
	struct partc *suiv;
	struct partc *prec;
}partie_class;
