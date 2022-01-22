#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void charger_niveau(char *nom, wave *vagues);
void charger_joueur(joueur *player);
int etat_partie_survivant(wave *vagues, joueur *player);
int demarrer_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event);
