#ifndef __CLASSIQUE_H_
#define __CLASSIQUE_H_
#include "interface.h"
#include "structures.h"
#include "vague.h"
#include "survivant.h"
#include "SDL2/SDL.h"

int etat_partie_classique(t_wave *vague, joueur *player);
int demarrer_classique(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, char lvl);
void deroulement_vague_classique(joueur *player, t_wave *vague, SDL_Renderer *rendu, int camp);
int fin_partie_classique(t_wave *vague);
#endif
