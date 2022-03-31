/**
 * \file classique.c
 * \brief Contient toutes les fonctions utiles au mode de jeu classique de battle ground (gestion de l'évolution de la
 * partie, implémentation des structures de jeu, etc..) \author Geoffrey Posé \version 3.2.4 \date 31/03/2022
 */

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "ajout_entites.h"
#include "animations.h"
#include "interactions.h"
//#include "interface.h"
#include "structures.h"
#include "vague.h"
#include "survivant.h"
//#include <assert.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#define V 5
#define x_def 100
#define y_def 470
#define taille_fenetre 1250

#define y_tir 475
#define x_tir 165

/**
 * \fn void gestion_environnement_classique(t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player, joueur *player2, SDL_Renderer *rendu)
 * \brief fonction qui sert à gérer l'environnement et ses interactions avec les entités ainsi que l'interaction des entités elles-mêmes. Une entité s'arrete lorsqu'elle se trouve face à un ennemi en face d'elle et l'attaque. Les autres qui suivent derrière s'arrêtent aussi. Il s'agit de paramétrer et de configurer les limites physiques de l'environnement ainsi que leur conditions.
 * \param t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player, SDL_Renderer *rendu
 */
void gestion_environnement_classique(t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player, joueur *player2, SDL_Renderer *rendu)
{ // fonction qui vérifie qu'un élément ne rentre pas en contact avec un autre
  vague_ennemie = deb_liste_vague(vague_ennemie);
  vague_joueur = deb_liste_vague(vague_joueur);
  if (vague_ennemie != NULL)
  {
    if (vague_ennemie->ent->x <= 400)
    {
      if (player->def != NULL && player->t == NULL)
      {
        if (!player->def->temps)
        {
          player->t = creer_tir(player->t, x_tir, y_tir);
          player->def->temps = 20;
        }
        else
          player->def->temps--;
      }
    }
    else if (player->def != NULL)
      player->def->temps = 0;
  }
  else if (player->def != NULL)
    player->def->temps = 0;

  if (vague_joueur != NULL)
  {
    if (vague_joueur->ent->x /*  >= taille_fenetre- 400 */)
    {
      if (player2->def != NULL && player2->t == NULL)
      {
        if (!player2->def->temps)
        {
          player2->t = creer_tir(player2->t, taille_fenetre - x_tir, y_tir);
          player2->def->temps = 20;
        }
        else
          player2->def->temps--;
      }
    }
    else if (player2->def != NULL)
      player2->def->temps = 0;
  }
  else if (player2->def != NULL)
    player2->def->temps = 0;
  gestion_ligne_entite(vague_ennemie, 1);
  gestion_ligne_entite(vague_joueur, 0);
  attaque_entites(vague_ennemie, vague_joueur, player);
  animation_attaque(rendu, vague_ennemie);
  animation_attaque(rendu, vague_joueur);
  animation_tir_gauche(rendu, player);

  animation_tir_gauche(rendu, player2);

  player->t = etat_tir(player->t); /*on met à jour le tir si besoin*/
  player->def = etat_defense(player->def);

  player2->t = etat_tir(player2->t); /*on met à jour le tir si besoin*/
  player2->def = etat_defense(player2->def);
}

/**
 * \fn int etat_partie_classique(t_wave *vague, joueur *player, joueur *player2)
 * \brief fonction qui sert à vérifier si la partie est finie ou si elle est toujours en cours (et si elle est finie si
 * le joueur1 a perdu ou le joueur2 a perdu, pour cela, le premier a 0 en point de vie a perdu) \param t_wave *vague, joueur *player \return int
 */
int etat_partie_classique(t_wave *vague, joueur *player, joueur *player2)
{ // retourne l'état de la partie (0 si elle est toujours en cours, 2 si le joueur a gagné, -1 si il a perdu)
  if (player != NULL && player2 != NULL)
  {
    if (player->pv < 0)
      return 1; // gagné
    else if (player2->pv < 0)
      return 2; // perdu
    else
      return 0;
  }
  return -1; // si on est pas rentré
}

/**
 * \fn int demarrer_classique(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event)
 * \brief cette fonction démarre le mode classique qui est finalement le mode 1 vs 1. C'est la fonction principale du mode jeu
 * classique et s'occupe de tout gérer (les évènements, l'argent et les unités de l'utilisateur; charger le niveau et
 * toutes les entités qui vont avec etc/..) \param SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event
 * \return int
 */
int demarrer_classique(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event)
{ // crée un ordinateur avec le nombre de vague liées au niveau.
  int indic;
  message msg;
  message_box(&msg, 0);
  /*   char level[100] = "data/modejeu/survivant/level1.txt";
    level[28] = lvl; */
  char bg[100] = "data/backgrounds/bg1classique.png";
  bg[19] = '1';
  /* t_wave *vague_ennemies = charger_niveau(level);
  if (vague_ennemies == NULL)
    printf("echec lors de la creation de vague\n");
 */
  t_wave *vague_joueur = NULL;
  t_wave *vague_ennemies = NULL;

  joueur *player = creer_joueur();
  joueur *player2 = creer_joueur();
  player2->camp = -1; // camp enemie

  player->argent = 10000;
  player2->argent = 10000;

  charger_image(bg, rendu, 0, 0, 1);
  int pause = 0;
  while (etat_partie_classique(vague_ennemies, player, player2) == 0)
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
          fin_partie(vague_ennemies);
          fin_partie(vague_joueur);
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
          creer_defense(player2, taille_fenetre - x_def, y_def, 15, &msg);
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
            fin_partie(vague_ennemies);
            fin_partie(vague_joueur);
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
    met_a_jour_img_argent(player2, rendu);

    afficher_survivant(rendu, player, pause);
    afficher_survivant(rendu, player2, pause);

    gestion_environnement_classique(vague_ennemies, vague_joueur, player, player2, rendu);
    if (!pause)
    {
      if (deroulement_vague(player2, vague_ennemies, rendu, 1) == -1)
        vague_ennemies = NULL;
      if (deroulement_vague(player, vague_joueur, rendu, 0) == -1)
        vague_joueur = NULL;
    }
    SDL_RenderPresent(rendu);
  }
  if (etat_partie_classique(vague_ennemies, player, player2) == 2) // le joueur2 a gagné
  {
    free(player);
    free(player2);
    fin_partie(vague_ennemies);
    fin_partie(vague_joueur);
    charger_image("data/inventaire/gagne.png", rendu, 400, 300, 1);
    SDL_Delay(1500);
    return 0;
  }
  else if (etat_partie_classique(vague_ennemies, player, player2) == 1) // le joueur1 a gagné
  {
    free(player);
    free(player2);
    fin_partie(vague_ennemies);
    fin_partie(vague_joueur);
    charger_image("data/inventaire/perd.png", rendu, 400, 300, 1);
    SDL_Delay(1500);
    return 0;
  }
  return 0;
}