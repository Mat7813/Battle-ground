#ifndef __VAGUE_H_
#define __VAGUE_H_
#include <stdio.h>
#include "SDL2/SDL.h"

typedef struct entity
{
	void (*met_a_jour)(struct entity *);
	void (*charger_img)(struct entity *, SDL_Renderer *);
	int attaque; 		/*valeur qui correspond à l'attaque si l'entité doit attaquer ou non*/
	int pv;
	int type; 			/*attaque à distance ou de près*/
	int degat;
	int x;
	int y;
	int x_barre; 		/*valeur qui correspond à la position de la barre de vie*/
	int y_barre;
	int w;				/*dimensions de l'image affichée à l'écran (largeur)*/
	int h;				/*dimensions de l'image affichée à l'écran (hauteur)*/
	int x_image;		/*absisse du début sur l'image*/
	int y_image;		/*ordonnée du début sur l'image*/
	int w_image;		/*dimensions de l'image dans le fichier png (largeur)*/
	int h_image;		/*dimensions de l'image dans le fichier png (hauteur)*/
	int temps;			/*valeur qui correspond au nombre d'itérations de boucles à attendre avant qu'il commence à avancer*/
	int nb_pos;			/*correspond au nombre de position dans le fichier en mode déplacement*/
	int nb_pos_attaque; /*correspond au nombre de position dans le fichier en mode attaque*/
	char nom_fichier[100];
	char nom_fichier_attaque[100];
	int montant; 		/*indicateur permettant de savoir si les images sont en phases montantes ou ascendantes*/
} entite;

typedef struct wave
{
	entite *ent;
	struct wave *suiv;
	struct wave *prec;
} t_wave;

t_wave *creer_vague();
char *creer_char();
int hors_liste_survivant(t_wave *vague);
t_wave *suivant_entite_survivant(t_wave *vague);
t_wave *precedent_entite_survivant(t_wave *vague);
t_wave *fin_liste_survivant(t_wave *vague);
t_wave *deb_liste_survivant(t_wave *vague);
int liste_vide_survivant(t_wave *vague);
t_wave *ajouter_entite_survivant(t_wave *vague);
t_wave *supprimer_entite_survivant(t_wave *vague);
t_wave *vider_liste_survivant(t_wave *vague);
int compter_elem(t_wave *vague);
void met_a_jour_img_argent(joueur *j, SDL_Renderer *rendu);
void met_a_jour_images_separees(entite *ent);
void met_a_jour_images_sprite(entite *ent);
void charger_img_separees(entite *ent, SDL_Renderer *rendu);
void charger_img_sprite(entite *ent, SDL_Renderer *rendu);
#endif
