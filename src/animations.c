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
#define y_entity 470
#define limit_x 100

/**
* \fn void afficher_survivant(SDL_Renderer *rendu)
* \brief fonction qui affiche le décors en mode survivant avec la barre de vie du joueur, son argent, et les menus
* \param wave_t * vague, SDL_Renderer *rendu
*/
void afficher_survivant(SDL_Window *window, SDL_Renderer *rendu,int pause){
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
