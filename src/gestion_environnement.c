#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int collision(int x, int x1){ //fonction qui vérifie qu'un élément ne rentre pas en contact avec un autre
  if(x!=x)return 0; //on retourne 0 si il n'y a pas de collision entre 2 objets/entités
  else return 1; //on retourne 1 si il y a collision
}
