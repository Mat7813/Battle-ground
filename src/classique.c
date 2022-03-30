/**
 * \file survivant.c
 * \brief Contient toutes les fonctions utiles au mode de jeu survivant de battle ground (gestion de l'évolution de la
 * partie, implémentation des structures de jeu, etc..) \author Lazare Maclouf \version 1 \date 25/02/2022
 */

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "ajout_entites.h"
#include "animations.h"
#include "interactions.h"
#include "interface.h"
#include "structures.h"
#include "vague.h"
#include "survivant.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define V 5
#define y_entity 470
#define x_def 100
#define y_def 470
#define pv_joueur 200
#define argent_joueur 1000
#define taille_fenetre 1250

/**
 * \fn void deroulement_vague(joueur *player, t_wave *vague, SDL_Renderer *rendu, int camp)
 * \brief fonction qui sert à mettre automatiquement les images des entités à jour ainsi que d'autres champs (points de
 * vie, position etc...). \param t_wave *vague, SDL_Renderer *rendu, int camp \return rien
 */
int deroulement_vague_classique(joueur *player, t_wave *vague, SDL_Renderer *rendu, int camp)
{
  int code_contour_barre_vie[4] = {0, 0, 0, 255};
  int code_interieur_barre_vie[4] = {255, 165, 0, 255};
  vague = deb_liste_survivant(vague);
  if (vague != NULL)
  {
    while (vague->suiv != NULL)
    {
      if (!vague->ent->temps && vague->ent->pv > 0)
      {
        if (vague->ent->attaque != 0)
          vague->ent->charger_img(vague->ent, rendu);
        vague->ent->met_a_jour(vague->ent);
        dessiner_rectangle_vide(rendu, code_contour_barre_vie, vague->ent->x_barre, vague->ent->y_barre, 8, 52,
                                0); /*met à jour la barre de vie*/
        dessiner_rectangle_plein(rendu, code_interieur_barre_vie, vague->ent->x_barre + 1,
                                 vague->ent->y_barre + 1, 6, vague->ent->pv, 0);
        if (camp && vague->ent->montant != 2)
        {
          vague->ent->x -= 2;
          vague->ent->x_barre -= 2;
        }
        else if (!camp && vague->ent->montant != 2)
        {
          vague->ent->x += 2;
          vague->ent->x_barre += 2;
        }
      }
      else if (vague->ent->temps > 0)
      {
        vague->ent->temps--;
        if (deb_liste_survivant(vague) == vague && !camp)
        {
          player->create = 1;
          if (vague->ent->temps <= 50)
            player->x_create += 5;
          else if (vague->ent->temps <= 0)
          {
            player->create = 0;
            player->x_create = 0;
          }
        }
        else if (fin_liste_survivant(vague))
        {
          if (vague->prec != NULL)
          {
            if (vague->prec->ent->temps == 0 && !camp)
            {
              player->create = 1;
              if (vague->ent->temps <= 50)
                if (player->x_create <= 265)
                  player->x_create += 5;
              if (vague->ent->temps <= 0)
              {
                player->create = 0;
                player->x_create = 0;
              }
            }
          }
          else if (vague->ent->temps <= 50)
            if (player->x_create <= 265)
              player->x_create += 5;
        }
        else if (vague->suiv != NULL && vague->prec != NULL)
        {
          if (vague->suiv->ent->temps == 0 && vague->prec->ent->temps > 0 && !camp)
          {
            player->create = 1;
            if (vague->ent->temps <= 50)
              if (player->x_create <= 265)
                player->x_create += 5;
            if (vague->ent->temps <= 0)
            {
              player->create = 0;
              player->x_create = 0;
            }
          }
        }
        else
          player->create = 0;
        vague = suivant_entite_survivant(vague);
      }
      if (vague->ent->pv <= 0)
      {
        vague = supprimer_entite_survivant(vague);
        if (camp)
          player->argent += 250;
        if (vague == NULL)
          return -1;
      }
      else if (vague->ent->pv > 0 && !vague->ent->temps)
        vague = suivant_entite_survivant(vague);
    }
  }
  if (vague != NULL)
  { // dans le cas ou il ne reste plus qu'une entité dans la liste ou on est à la fin
    if (!vague->ent->temps && vague->ent->pv > 0)
    {
      if (vague->ent->attaque != 0)
        vague->ent->charger_img(vague->ent, rendu);
      vague->ent->met_a_jour(vague->ent);
      dessiner_rectangle_vide(rendu, code_contour_barre_vie, vague->ent->x_barre, vague->ent->y_barre, 8, 52,
                              0); /*met à jour la barre de vie*/
      dessiner_rectangle_plein(rendu, code_interieur_barre_vie, vague->ent->x_barre + 1, vague->ent->y_barre + 1,
                               6, vague->ent->pv, 0);
      if (camp && vague->ent->montant != 2)
      {
        vague->ent->x -= 2;
        vague->ent->x_barre -= 2;
      }
      else if (!camp && vague->ent->montant != 2)
      {
        vague->ent->x += 2;
        vague->ent->x_barre += 2;
      }
      if (!camp)
      {
        player->create = 0;
        player->x_create = 0;
      }
    }
    if (vague->ent->temps > 0)
    {
      vague->ent->temps--;
      if (deb_liste_survivant(vague) == vague && !camp)
      {
        player->create = 1;
        if (vague->ent->temps <= 50)
          if (player->x_create <= 265)
            player->x_create += 5;
        if (vague->ent->temps <= 0)
        {
          player->create = 0;
          player->x_create = 0;
        }
      }
      else if (fin_liste_survivant(vague))
      {
        if (vague->prec != NULL)
          if (vague->prec->ent->temps == 0 && !camp)
          {
            player->create = 1;
            if (vague->ent->temps <= 50)
              if (player->x_create <= 265)
                player->x_create += 5;
            if (vague->ent->temps <= 0)
            {
              player->create = 0;
              player->x_create = 0;
            }
          }
        if (vague->ent->temps <= 50)
          player->x_create += 5;
      }
      if (vague->suiv != NULL && vague->prec != NULL)
      {
        if (vague->suiv->ent->temps == 0 && vague->prec->ent->temps > 0 && !camp)
        {
          player->create = 1;
          if (vague->ent->temps <= 50)
            if (player->x_create <= 265)
              player->x_create += 5;
          if (vague->ent->temps <= 0)
          {
            player->create = 0;
            player->x_create = 0;
          }
        }
      }
      else
        player->create = 0;
    }
    if (vague->ent->pv <= 0)
    {
      vague = supprimer_entite_survivant(vague);
      if (camp)
        player->argent += 250;
      if (vague == NULL)
        return -1;
      if (!camp)
        player->create = 0;
    }
  }
  return 1;
}

/**
 * \fn fin_partie_survivant(t_wave *vague)
 * \brief fonction qui sert à vider une liste chainée d'entité. c'est-à-dire supprimer toutes les entités qui la compose
 * et ainsi libérer la mémoire. \param t_wave *vague \return int
 */
int fin_partie_classique(t_wave *vague)
{
  vague = vider_liste_survivant(vague);
  return (vague == NULL);
}

/**
 * \fn int etat_partie_survivant(t_wave *vague, joueur *player)
 * \brief fonction qui sert à vérifier si la partie est finie ou si elle est toujours en cours (et si elle est finie si
 * le joueur a gagné ou perdu) \param t_wave *vague, joueur *player \return int
 */
int etat_partie_classique(t_wave *vague, joueur *player)
{ // retourne l'état de la partie (0 si elle est toujours en cours, 2 si le joueur a gagné, -1 si il a perdu)
  if (player != NULL)
  {
    if (player->pv > 0)
    {
      /* if (vague == NULL)
      {
        printf("gagné\n");
        return 2;
      } */
      return 0;
    }
    else
      return -1;
  }
  return 1; // si on est pas rentré
}

/**
 * \fn int demarrer_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, char lvl)
 * \brief Comme son nom l'indique, cette fonction démarre le mode survivant. C'est la fonction principale du mode jeu
 * survivant et s'occupe de tout gérer (les évènements, l'argent et les unités de l'utilisateur; charger le niveau et
 * toutes les entités qui vont avec etc/..) \param SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, char lvl
 * \return int
 */
int demarrer_classique(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, char lvl)
{ // crée un ordinateur avec le nombre de vague liées au niveau.
  int indic;
  message msg;
  message_box(&msg, 0);
  char level[100] = "data/modejeu/survivant/level1.txt";
  level[28] = lvl;
  char bg[100] = "data/backgrounds/bg1classique.png";
  bg[19] = lvl;
  /* t_wave *vague_ennemies = charger_niveau(level);
  if (vague_ennemies == NULL)
    printf("echec lors de la creation de vague\n");
 */
  t_wave *vague_joueur = NULL;
  t_wave *vague_ennemies = NULL;

  joueur *player = creer_joueur();
  joueur *player2 = creer_joueur();

  player->argent = 10000;
  player2->argent = 10000;

  charger_image(bg, rendu, 0, 0, 1);
  int pause = 0;
  while (etat_partie_classique(vague_ennemies, player) == 0)
  {
    while (SDL_PollEvent(event))
    { // on réécoute les évènements mais avec un pointeur sur event car en SDL on ne peut pas faire plusieurs
      // listener d'évènements.
      //  if(etat_partie_survivant(vague, &player)==1)return 1;//on verifie à chaque tour de boucle l'état de la
      //  partie if(etat_partie_survivant(vague, &player)==-1)return 0;
      if (event->type == SDL_QUIT)
      { // lorsque l'utilisateur appuie sur la croix rouge de la fenetre
        if (quit_message() == -1)
        {
          fin_partie_classique(vague_ennemies);
          fin_partie_classique(vague_joueur);
          return -1;
        }
      }
      if (event->window.event == SDL_WINDOWEVENT_RESIZED)
        SDL_SetWindowSize(window, 1250, 694);
      if (compter_elem(vague_ennemies) >= 20)
        message_box(&msg, "data/inventaire/derniere.png");

      if ((event->motion.x >= 620 && event->motion.x <= 670) && (event->motion.y >= 10 && event->motion.y <= 50))
      {
        if (event->type == SDL_MOUSEBUTTONDOWN)
        {
          if (pause)
            pause = 0;
          else
            pause = 1;
          afficher_survivant(rendu, player, pause);
        }
      }

      if ((event->motion.x >= 220 && event->motion.x <= 280) && (event->motion.y >= 10 && event->motion.y <= 60))
      { // pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton
        // (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
        indic = 1;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          vague_joueur = ajouter_voisin(player, vague_joueur, &msg); /*ajouter_voisin(player, vague_joueur);*/
      }
      else if ((event->motion.x >= 290 && event->motion.x <= 350) &&
               (event->motion.y >= 10 && event->motion.y <= 60))
      {
        indic = 2;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          vague_joueur = ajouter_fighter(player, vague_joueur, &msg);
      }
      else if ((event->motion.x >= 360 && event->motion.x <= 420) &&
               (event->motion.y >= 10 && event->motion.y <= 60))
      {
        indic = 3;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          vague_joueur = ajouter_bandit(player, vague_joueur, &msg);
      }
      else if ((event->motion.x >= 430 && event->motion.x <= 500) &&
               (event->motion.y >= 10 && event->motion.y <= 60))
      {
        indic = 4;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          creer_defense(player, x_def, y_def, 15, &msg);
      }

      // inverse:
      else if ((event->motion.x <= taille_fenetre - 220 && event->motion.x >= taille_fenetre - 280) &&
               (event->motion.y >= 10 && event->motion.y <= 60))
      {
        indic = 6;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          vague_ennemies = ajouter_voisin(player2, vague_ennemies, &msg);
      }
      else if ((event->motion.x <= taille_fenetre - 290 && event->motion.x >= taille_fenetre - 350) &&
               (event->motion.y >= 10 && event->motion.y <= 60))
      {
        indic = 7;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          vague_ennemies = ajouter_fighter(player2, vague_ennemies, &msg);
      }
      else if ((event->motion.x <= taille_fenetre - 360 && event->motion.x >= taille_fenetre - 420) &&
               (event->motion.y >= 10 && event->motion.y <= 60))
      {
        indic = 8;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          vague_ennemies = ajouter_bandit(player2, vague_ennemies, &msg);
      }
      else if ((event->motion.x <= taille_fenetre - 430 && event->motion.x >= taille_fenetre - 500) &&
               (event->motion.y >= 10 && event->motion.y <= 60))
      {
        indic = 9;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          creer_defense(player2, taille_fenetre - x_def, taille_fenetre - y_def, 15, &msg);
      }

      else if ((event->motion.x >= 0 && event->motion.x <= 100) &&
               (event->motion.y >= 0 && event->motion.y <= 30))
      { // pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton
        // (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
        indic = 5;
        if (event->type == SDL_MOUSEBUTTONDOWN)
        {
          if (return_message() == -1)
          {
            fin_partie_survivant(vague_ennemies);
            fin_partie_survivant(vague_joueur);
            return 0;
          }
        }
      }

      else
        indic = 0;
      if (msg.temps > 0)
      {
        if (fichier_existe(msg.nom_fichier))
          charger_image(msg.nom_fichier, rendu, msg.x, msg.y, 0);
        msg.temps--;
      }
    }
    if (msg.temps > 0)
    {
      if (fichier_existe(msg.nom_fichier))
        charger_image(msg.nom_fichier, rendu, msg.x, msg.y, 0);
      msg.temps--;
    }
    if (!pause)
    {
      charger_image(bg, rendu, 0, 0, 0);
      charger_image("data/inventaire/backover.png", rendu, 0, 10, 0);
      charger_image("data/inventaire/carre1.png", rendu, 220, 10, 0);
      charger_image("data/inventaire/carre2.png", rendu, 290, 10, 0);
      charger_image("data/inventaire/carre3.png", rendu, 360, 10, 0);
      charger_image("data/inventaire/carre4.png", rendu, 430, 10, 0);
      charger_image("data/inventaire/carreover.png", rendu, 220, 10, 0);
      charger_image("data/inventaire/carreover.png", rendu, 290, 10, 0);
      charger_image("data/inventaire/carreover.png", rendu, 360, 10, 0);
      charger_image("data/inventaire/carreover.png", rendu, 430, 10, 0);
      // charger_image("data/inventaire/survivant.png", rendu, 740, 10, 0);
      charger_image("data/inventaire/piece1.png", rendu, 20, 40, 0);
      charger_image("data/inventaire/retoursurv.png", rendu, 60, 10, 0);
      if (indic != 1)
        charger_image("data/inventaire/carre1.png", rendu, 220, 10, 0);
      if (indic != 2)
        charger_image("data/inventaire/carre2.png", rendu, 290, 10, 0);
      if (indic != 3)
        charger_image("data/inventaire/carre3.png", rendu, 360, 10, 0);
      if (indic != 4)
        charger_image("data/inventaire/carre4.png", rendu, 430, 10, 0);
      if (indic != 5)
        charger_image("data/inventaire/back.png", rendu, 0, 10, 0);
      if (msg.temps > 0)
      {
        if (fichier_existe(msg.nom_fichier))
          charger_image(msg.nom_fichier, rendu, msg.x, msg.y, 0);
        msg.temps--;
      }
      // inverse
      // charger_image("data/inventaire/backover.png", rendu, taille_fenetre-0, 10, 0);
      // charger_image("data/inventaire/survivant.png", rendu, taille_fenetre-740, 10, 0);
      // charger_image("data/inventaire/retoursurv.png", rendu, taille_fenetre-60, 10, 0);
      charger_image("data/inventaire/carre1.png", rendu, taille_fenetre - 60 - 220, 10, 0); // 60 est la longueur du carre
      charger_image("data/inventaire/carre2.png", rendu, taille_fenetre - 60 - 290, 10, 0);
      charger_image("data/inventaire/carre3.png", rendu, taille_fenetre - 60 - 360, 10, 0);
      charger_image("data/inventaire/carre4.png", rendu, taille_fenetre - 60 - 430, 10, 0);
      charger_image("data/inventaire/carreover.png", rendu, taille_fenetre - 60 - 220, 10, 0);
      charger_image("data/inventaire/carreover.png", rendu, taille_fenetre - 60 - 290, 10, 0);
      charger_image("data/inventaire/carreover.png", rendu, taille_fenetre - 60 - 360, 10, 0);
      charger_image("data/inventaire/carreover.png", rendu, taille_fenetre - 60 - 430, 10, 0);
      charger_image("data/inventaire/piece1.png", rendu, taille_fenetre - 60 - 20, 40, 0);
      if (indic != 6)
        charger_image("data/inventaire/carre1.png", rendu, taille_fenetre - 60 - 220, 10, 0);
      if (indic != 7)
        charger_image("data/inventaire/carre2.png", rendu, taille_fenetre - 60 - 290, 10, 0);
      if (indic != 8)
        charger_image("data/inventaire/carre3.png", rendu, taille_fenetre - 60 - 360, 10, 0);
      if (indic != 9)
        charger_image("data/inventaire/carre4.png", rendu, taille_fenetre - 60 - 430, 10, 0);
    }

    met_a_jour_img_argent(player, rendu);
    afficher_survivant(rendu, player, pause);
    gestion_environnement(vague_ennemies, vague_joueur, player, rendu);
    if (!pause)
    {
      if (deroulement_vague(player2, vague_ennemies, rendu, 1) == -1)
        vague_ennemies = NULL;
      if (deroulement_vague(player, vague_joueur, rendu, 0) == -1)
        vague_joueur = NULL;
    }
    SDL_RenderPresent(rendu);
  }
  if (etat_partie_survivant(vague_ennemies, player) == 2)
  {
    free(player);
    fin_partie_survivant(vague_ennemies);
    fin_partie_survivant(vague_joueur);
    charger_image("data/inventaire/gagne.png", rendu, 400, 300, 1);
    SDL_Delay(1500);
    return 1;
  }
  else if (etat_partie_survivant(vague_ennemies, player) == -1)
  {
    free(player);
    fin_partie_survivant(vague_ennemies);
    fin_partie_survivant(vague_joueur);
    charger_image("data/inventaire/perd.png", rendu, 400, 300, 1);
    SDL_Delay(1500);
    return 0;
  }
  return 0;
}