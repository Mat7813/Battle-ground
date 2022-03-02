#ifndef __SURVIVANT_H_
#define __SURVIVANT_H_
#include "../include/interface.h"
#include "../include/structures_vagues.h"
t_wave* charger_niveau(char *nom);
void creer_joueur(joueur *player);
void ajouter_voisin(joueur *player, t_wave *vague, message *msg);
int etat_partie_survivant(t_wave *vagues, joueur *player);
void message_box(message *msg, char nom_fic[100]);
int demarrer_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, char lvl);
void deroulement_vagues(joueur *player, t_wave *vagues, SDL_Renderer *rendu, int camp);
int fin_partie_survivant(t_wave *vagues);
#endif
