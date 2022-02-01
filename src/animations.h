#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "structures.h"

void animation(SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int x);
void afficher_survivant(t_wave * vague, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int pause);
