/**
 * \file ajout_entites.c
 * \brief Contient toutes les fonctions qui servent à ajouter des entités (tous les types d'entités)
 * \author Lazare Maclouf
 * \version 2
 * \date 30/03/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "interface.h"
#include "vague.h"
#include "survivant.h"

#define Y_ENTITY 470
#define TAILLE_FENETRE 1250

/**
 * \fn t_wave *ajouter_voisin(joueur *player, t_wave *vague, message *msg)
 * \brief fonction qui crée une entité voisin et renvoie le pointeur sur celle-ci
 * \param joueur *player, t_wave *vague, message *msg
 * \return t_wave *
 */
t_wave *ajouter_voisin(joueur *player, t_wave *vague, message *msg)
{
  if (player != NULL)
  {
    if (player->argent >= 1200)
    {
      vague = fin_liste_survivant(vague);
      if (vague == NULL)
      {
        t_wave *nouv = creer_vague();
        nouv->ent->temps = 50;
        strcpy(nouv->ent->nom_fichier, "data/entities/voisn/voisn1.png");
        strcpy(nouv->ent->nom_fichier_attaque, "data/entities/voisn/voisintir.png");
        if (player->camp > 0)
        {
          nouv->ent->x_barre = 130;
          nouv->ent->x = 110;
        }
        else if (player->camp < 0)
        {
          nouv->ent->x_barre = TAILLE_FENETRE - 130;
          nouv->ent->x = TAILLE_FENETRE - 110;
        }
        nouv->ent->pv = 50;
        nouv->ent->montant = 1;
        nouv->ent->type = 1;
        nouv->ent->y = Y_ENTITY;
        nouv->ent->attaque = 1;
        nouv->ent->y_barre = 450;
        nouv->ent->degat = 20;
        nouv->ent->met_a_jour = met_a_jour_images_separees;
        nouv->ent->charger_img = charger_img_separees;
        nouv->ent->w = 0;
        nouv->ent->h = 0;
        nouv->ent->x_image = 0;
        nouv->ent->y_image = 0;
        nouv->ent->w_image = 0;
        nouv->ent->h_image = 0;
        nouv->ent->nom_fichier_attaque[0] = 0;
        player->argent -= 1200;
        player->create = 1;
        return nouv;
      }
      else
        vague = ajouter_entite_survivant(vague);
      if (vague->prec != NULL)
      {
        vague->ent->temps = 50 + vague->prec->ent->temps;
      }
      strcpy(vague->ent->nom_fichier, "data/entities/voisn/voisn1.png");
      strcpy(vague->ent->nom_fichier_attaque, "data/entities/voisn/voisintir.png");
      if (player->camp > 0)
      {
        vague->ent->x_barre = 130;
        vague->ent->x = 110;
      }
      else if (player->camp < 0)
      {
        vague->ent->x_barre = TAILLE_FENETRE - 130;
        vague->ent->x = TAILLE_FENETRE - 110;
      }
      vague->ent->pv = 50;
      vague->ent->montant = 1;
      vague->ent->y = Y_ENTITY;
      vague->ent->attaque = 1;
      vague->ent->type = 1;
      vague->ent->y_barre = 450;
      vague->ent->degat = 20;
      vague->ent->met_a_jour = met_a_jour_images_separees;
      vague->ent->charger_img = charger_img_separees;
      vague->ent->w = 0;
      vague->ent->h = 0;
      vague->ent->x_image = 0;
      vague->ent->y_image = 0;
      vague->ent->w_image = 0;
      vague->ent->h_image = 0;
      vague->ent->nb_pos = 0;
      vague->ent->nb_pos_attaque = 0;
      vague->ent->nom_fichier_attaque[0] = 0;
      player->argent -= 1200;
      player->create = 1;
      return vague;
    }
    else
      message_box(msg, "data/inventaire/pasassez.png");
  }
  return vague;
}

/**
 * \fn t_wave *ajouter_bandit(joueur *player, t_wave *vague, message *msg)
 * \brief fonction qui crée une entité bandit et renvoie le pointeur sur celle-ci
 * \param joueur *player, t_wave *vague, message *msg
 * \return t_wave *
 */
t_wave *ajouter_bandit(joueur *player, t_wave *vague, message *msg)
{
  if (player != NULL)
  {
    if (player->argent >= 150)
    {
      vague = fin_liste_survivant(vague);
      if (vague == NULL)
      {
        t_wave *nouv = creer_vague();
        nouv->ent->temps = 50;
        strcpy(nouv->ent->nom_fichier, "data/entities/bandit/bandit.png");
        strcpy(nouv->ent->nom_fichier_attaque, "NULL");
        nouv->ent->pv = 50;
        nouv->ent->montant = 1;
        nouv->ent->y = Y_ENTITY;
        nouv->ent->attaque = 1;
        if (player->camp > 0)
        {
          nouv->ent->x_barre = 160;
          nouv->ent->x = 110;
          nouv->ent->charger_img = charger_img_sprite;
        }
        else if (player->camp < 0)
        {
          nouv->ent->x_barre = TAILLE_FENETRE - 160 + 70;
          nouv->ent->x = TAILLE_FENETRE - 110;
          nouv->ent->charger_img = charger_img_sprite_reverse;
        }
        nouv->ent->y_barre = 450;
        nouv->ent->degat = 10;
        nouv->ent->met_a_jour = met_a_jour_images_sprite;
        nouv->ent->w = 135;
        nouv->ent->h = 135;
        nouv->ent->type = 2;
        nouv->ent->w_image = 79;
        nouv->ent->h_image = 79;
        nouv->ent->x_image = 0;
        nouv->ent->y_image = 0;
        nouv->ent->nb_pos = 3;
        nouv->ent->nb_pos_attaque = 3;
        nouv->ent->nom_fichier_attaque[0] = 0;
        player->argent -= 150;
        player->create = 1;
        return nouv;
      }
      else
        vague = ajouter_entite_survivant(vague);
      if (vague->prec != NULL)
      {
        vague->ent->temps = 50 + vague->prec->ent->temps;
      }
      strcpy(vague->ent->nom_fichier, "data/entities/bandit/bandit.png");
      strcpy(vague->ent->nom_fichier_attaque, "NULL");
      if (player->camp > 0)
      {
        vague->ent->x_barre = 160;
        vague->ent->x = 110;
        vague->ent->charger_img = charger_img_sprite;
      }
      else if (player->camp < 0)
      {
        vague->ent->x_barre = TAILLE_FENETRE - 160 + 70;
        vague->ent->x = TAILLE_FENETRE - 110;
        vague->ent->charger_img = charger_img_sprite_reverse;
      }
      vague->ent->pv = 50;
      vague->ent->montant = 1;
      vague->ent->y = Y_ENTITY;
      vague->ent->attaque = 1;
      vague->ent->y_barre = 450;
      vague->ent->degat = 10;
      vague->ent->met_a_jour = met_a_jour_images_sprite;
      vague->ent->w = 135;
      vague->ent->h = 135;
      vague->ent->w_image = 79;
      vague->ent->h_image = 79;
      vague->ent->x_image = 0;
      vague->ent->y_image = 0;
      vague->ent->type = 2;
      vague->ent->nb_pos = 3;
      vague->ent->nb_pos_attaque = 3;
      vague->ent->nom_fichier_attaque[0] = 0;
      player->argent -= 150;
      player->create = 1;
      return vague;
    }
    else
      message_box(msg, "data/inventaire/pasassez.png");
  }
  return vague;
}

/**
 * \fn t_wave *ajouter_fighter(joueur *player, t_wave *vague, message *msg)
 * \brief fonction qui crée une entité fighter et renvoie le pointeur sur celle-ci
 * \param joueur *player, t_wave *vague, message *msg
 * \return t_wave *
 */
t_wave *ajouter_fighter(joueur *player, t_wave *vague, message *msg)
{
  if (player != NULL)
  {
    if (player->argent >= 500)
    {
      vague = fin_liste_survivant(vague);
      if (vague == NULL)
      {
        t_wave *nouv = creer_vague();
        nouv->ent->temps = 50;
        strcpy(nouv->ent->nom_fichier, "data/entities/fighter/fighter.png");
        strcpy(nouv->ent->nom_fichier_attaque, "NULL");
        if (player->camp > 0)
        {
          nouv->ent->x_barre = 130;
          nouv->ent->x = 110;
          nouv->ent->charger_img = charger_img_sprite;
        }
        else if (player->camp < 0)
        {
          nouv->ent->x_barre = TAILLE_FENETRE - 110 + 50;
          nouv->ent->x = TAILLE_FENETRE - 110;
          nouv->ent->charger_img = charger_img_sprite_reverse;
        }
        nouv->ent->pv = 50;
        nouv->ent->montant = 1;
        nouv->ent->y = Y_ENTITY;
        nouv->ent->attaque = 1;
        nouv->ent->y_barre = 450;
        nouv->ent->degat = 25;
        nouv->ent->met_a_jour = met_a_jour_images_sprite;
        nouv->ent->w = 135;
        nouv->ent->h = 135;
        nouv->ent->type = 2;
        nouv->ent->w_image = 140;
        nouv->ent->h_image = 115;
        nouv->ent->x_image = 0;
        nouv->ent->y_image = 0;
        nouv->ent->nb_pos = 15;
        nouv->ent->nb_pos_attaque = 6;
        nouv->ent->nom_fichier_attaque[0] = 0;
        player->argent -= 500;
        player->create = 1;
        return nouv;
      }
      else
        vague = ajouter_entite_survivant(vague);
      if (vague->prec != NULL)
      {
        vague->ent->temps = 50 + vague->prec->ent->temps;
      }
      strcpy(vague->ent->nom_fichier, "data/entities/fighter/fighter.png");
      strcpy(vague->ent->nom_fichier_attaque, "NULL");
      vague->ent->met_a_jour = met_a_jour_images_sprite;
      if (player->camp > 0)
      {
        vague->ent->x_barre = 130;
        vague->ent->x = 110;
        vague->ent->charger_img = charger_img_sprite;
      }
      else if (player->camp < 0)
      {
        vague->ent->x_barre = TAILLE_FENETRE - 110 + 50;
        vague->ent->x = TAILLE_FENETRE - 110;
        vague->ent->charger_img = charger_img_sprite_reverse;
      }
      vague->ent->pv = 50;
      vague->ent->montant = 1;
      vague->ent->y = Y_ENTITY;
      vague->ent->attaque = 1;
      vague->ent->y_barre = 450;
      vague->ent->degat = 25;
      vague->ent->met_a_jour = met_a_jour_images_sprite;
      vague->ent->w = 135;
      vague->ent->h = 135;
      vague->ent->w_image = 140;
      vague->ent->h_image = 115;
      vague->ent->x_image = 0;
      vague->ent->y_image = 0;
      vague->ent->type = 2;
      vague->ent->nb_pos = 15;
      vague->ent->nb_pos_attaque = 6;
      vague->ent->nom_fichier_attaque[0] = 0;
      player->argent -= 500;
      player->create = 1;
      return vague;
    }
    else
      message_box(msg, "data/inventaire/pasassez.png");
  }
  return vague;
}
