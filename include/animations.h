#ifndef __ANIMATIONS_H_
#define __ANIMATIONS_H_
#include "interface.h"

void afficher_survivant(SDL_Renderer *rendu, joueur *player, int pause);
void animation_tir_gauche(SDL_Renderer *rendu, joueur *player);
void animation_attaque(SDL_Renderer *rendu, t_wave *vague);
#endif
