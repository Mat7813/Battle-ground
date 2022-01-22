#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int quit_message();
void inserer(char *c, char *chaine, int p);
void supprimer(char *chaine, int p);
void remplacer(char *c, char *chaine, int p)
int jeu_classique(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event, int difficulte);
int jeu_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event);
