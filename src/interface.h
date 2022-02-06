#ifndef __INTERFACE_H_
#define __INTERFACE_H_
#include "structures.h"
int charger_image(char *nom, SDL_Renderer *rendu, int x, int y, int option);
void demarrage(SDL_Renderer *rendu);
int menu_jouer_difficulte(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, int mode);
int sous_menu_jouer(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event);
void sous_menu_parametres(SDL_Window *window, SDL_Renderer *rendu);
void menu(SDL_Window *window, SDL_Renderer *rendu);
int initialise_jeu();
#endif
