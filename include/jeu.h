#ifndef __JEU_H_
#define __JEU_H_
#include <SDL2/SDL.h>

int jeu_classique(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, int difficulte);
int jeu_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event);
#endif
