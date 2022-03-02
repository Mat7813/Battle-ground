#ifndef __INTERACTIONS_H_
#define __INTERACTIONS_H_
#include <stdio.h>
#include "../include/structures.h"
#include "../include/structures_vagues.h"
#include "../include/vagues.h"
void attaque_entites(t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player);
void gestion_environnement(t_wave *vague_ennemie,t_wave *vague_joueur, joueur *player, SDL_Renderer *rendu);
tir *creer_tir(tir *t, int x, int y);
tir *etat_tir(tir *t);
void creer_defense(joueur *p, int x, int y, int degat, message *msg);
defense *etat_defense(defense *def);
void gestion_ligne_entite(t_wave *vague);
int fichier_existe(char *nom);
#endif
