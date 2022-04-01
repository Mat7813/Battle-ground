#ifndef __INTERFACE_H_
#define __INTERFACE_H_
#include "structures.h"
#include "SDL2/SDL.h"

void convert_argent(joueur *p);
int quit_message();
void dessiner_rectangle_vide(SDL_Renderer *rendu, int code_couleur[4], int x, int y, int h, int w, int mode);
void dessiner_rectangle_plein(SDL_Renderer *rendu, int code_couleur[4], int x, int y, int h, int w, int mode);
int charger_image(char *nom, SDL_Renderer *rendu, int x, int y, int option);
int charger_partie_image(char *nom, SDL_Renderer *rendu, int x, int y, int w, int h, int w_image, int h_image, int x_image, int y_image, int option);
void demarrage(SDL_Renderer *rendu);
int menu_jouer_difficulte(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event);
int select_multi(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event);
int sous_menu_jouer(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event);
void menu(SDL_Window *window, SDL_Renderer *rendu);
int initialise_jeu();
#endif
