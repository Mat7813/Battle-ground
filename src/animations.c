/**
 * \file animations.c
 * \brief Contient les fonctions pour gérer toutes les animations du jeu (complète le fichier interface.c). (Déplacement des entités, gestion des tirs des canons etc..).
 * \author Lazare Maclouf
 * \version 1
 * \date 25/01/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "interface.h"
#include "structures.h"
#define y_entity 470
#define limit_x 100

/**
* \fn void afficher_survivant(SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect)
* \brief fonction qui affiche le décors en mode survivant avec la barre de vie du joueur, son argent, et les menus
* \param wave_t * vague, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect
*/
void afficher_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int pause){
  int code_contour_barre_vie[4]={0,0,0,255};
  int code_interieur_barre_vie[4]={255,165,0,255};
  if(pause){
    dessiner_rectangle_plein(rendu, code_interieur_barre_vie, 620, 10, 50, 20, 0);
    dessiner_rectangle_plein(rendu, code_interieur_barre_vie, 650, 10, 50, 20, 0);
  }
  else{
  dessiner_rectangle_vide(rendu, code_contour_barre_vie, 10, 180, 202, 12, 0); /*barre de vie du joueur*/
  dessiner_rectangle_plein(rendu, code_interieur_barre_vie, 11, 181, 200, 10, 0);/*barre de vie du joueur*/
  dessiner_rectangle_plein(rendu, code_contour_barre_vie, 620, 10, 50, 20, 0);
  dessiner_rectangle_plein(rendu, code_contour_barre_vie, 650, 10, 50, 20, 0);
  }
}
/**
*\brief fonction qui affiche le décors en mode survivant avec la barre de vie du joueur, son argent, et les menus
*
*/
/*void afficher_classique(SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect){

}
*/
void animation(SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int x){
  int i=49, montant=1, j=9; //montant correspond au chiffre avant le .png pour faire varier l'image et faire bouger la momie
  char car[45]="data/entities/mumma/mummy1.png";
  while(j>0){
    x-=2;
    SDL_Delay(50);
    SDL_RenderClear(rendu);
    charger_image_option("data/backgrounds/bg1classique.png", rendu, image, texture, rect,0,0,0);
    if(x-80>=limit_x)charger_image_option(car, rendu, image, texture, rect,x-80,y_entity,0);
    if(x-160>=limit_x)charger_image_option(car, rendu, image, texture, rect,x-160,y_entity,0);
    if(x-240>=limit_x)charger_image_option(car, rendu, image, texture, rect,x-240,y_entity,0);
    if(x-330>=limit_x)charger_image_option(car, rendu, image, texture, rect,x-330,y_entity,0);
    if(x-440>=limit_x)charger_image_option(car, rendu, image, texture, rect,x-440,y_entity,0);
    if(x-550>=limit_x)charger_image_option(car, rendu, image, texture, rect,x-550,y_entity,0);
    if(x>=limit_x)charger_image_option(car, rendu, image, texture, rect,x,y_entity,0);
    SDL_RenderPresent(rendu);
    if(montant==1){
        if(car[25]<57)car[25]++; //57 correspon à 9. Quand on arrrive à 9 on redescend
        else montant=0;
    }
    else {
      return 0;
    }
    j--;
}
}
