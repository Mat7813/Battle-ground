/**
 * \file animations.c
 * \brief Contient les fonctions pour gérer toutes les animations du jeu (complète le fichier interface.c). (Déplacement des entités, gestion des tirs des canons etc..) Il s'agit des animations communes.
 * \author Lazare Maclouf
 * \version 1
 * \date 25/01/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "interface.h"
#include "structures.h"
#include "vague.h"
#define y_entity 470
#define limit_x 100

/**
 * \fn void afficher_survivant(SDL_Renderer *rendu, joueur *player, int pause)
 * \brief fonction qui affiche le décors en mode survivant avec la barre de vie du joueur, son argent, et les menus
 * \param SDL_Renderer *rendu, joueur *player, int pause
 */
void afficher_survivant(SDL_Renderer *rendu, joueur *player, int pause)
{
  int code_contour_barre_vie[4] = {0, 0, 0, 255};
  int code_interieur_barre_vie[4] = {255, 165, 0, 255};
  dessiner_rectangle_vide(rendu, code_contour_barre_vie, 10, 180, 202, 12, 0); /*barre de vie du joueur*/     /*barre de vie du joueur*/
  dessiner_rectangle_plein(rendu, code_interieur_barre_vie, 11, 181 + (200 - player->pv), player->pv, 10, 0); /*barre de vie du joueur, l'abcisse est proportionnelle au nombre de pv du joueur*/
  if (pause)
  {
    dessiner_rectangle_plein(rendu, code_interieur_barre_vie, 620, 10, 50, 20, 0);
    dessiner_rectangle_plein(rendu, code_interieur_barre_vie, 650, 10, 50, 20, 0);
  }
  else
  {
    dessiner_rectangle_plein(rendu, code_contour_barre_vie, 620, 10, 50, 20, 0);
    dessiner_rectangle_plein(rendu, code_contour_barre_vie, 650, 10, 50, 20, 0);
  }
  if (player->create)
  {
    int code_interieur_creation[4] = {255, 0, 0, 255};
    dessiner_rectangle_vide(rendu, code_contour_barre_vie, 220, 100, 12, 272, 0);
    dessiner_rectangle_plein(rendu, code_interieur_creation, 221, 101, 10, player->x_create, 0);
  }
}
/**
 * \fn void animation_tir_gauche(SDL_Renderer *rendu, joueur *player)
 * \brief fonction qui effectue l'animation d'un tir provenant de gauche jusqu'à sa cible
 * \param wave_t * vague, SDL_Renderer *rendu
 */
void animation_tir_gauche(SDL_Renderer *rendu, joueur *player)
{
  if (player->def != NULL)
  {
    charger_image(player->def->nom_fichier, rendu, player->def->x, player->def->y, 0);
    if (player->t != NULL)
    {
      charger_image(player->t->nom_fichier, rendu, player->t->x, player->t->y, 0);
      player->t->x += 15;
    }
  }
}
/**
 * \fn void animation_attaque(SDL_Renderer *rendu, t_wave *vague)
 * \brief fonction qui met anime l'attaque de certaines entités
 * \param SDL_Renderer *rendu, t_wave *vague
 */
void animation_attaque(SDL_Renderer *rendu, t_wave *vague)
{
  if (vague != NULL)
  {
    if (!vague->ent->attaque || vague->ent->attaque == 20 || vague->ent->attaque == 19 || vague->ent->attaque == 18)
      charger_image(vague->ent->nom_fichier_attaque, rendu, vague->ent->x, vague->ent->y, 0);
    else
      return;
  }
}