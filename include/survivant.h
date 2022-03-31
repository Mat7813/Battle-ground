#ifndef __SURVIVANT_H_
#define __SURVIVANT_H_
#include "interface.h"
#include "structures.h"
#include "vague.h"
#include "SDL2/SDL.h"

t_wave *charger_niveau(char *nom);
joueur *creer_joueur();
int etat_partie_survivant(t_wave *vague, joueur *player);
void message_box(message *msg, char nom_fic[100]);
int demarrer_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, char lvl);
int deroulement_vague(joueur *player, t_wave *vague, SDL_Renderer *rendu, int camp);
int fin_partie(t_wave *vague);
int return_message();
#endif