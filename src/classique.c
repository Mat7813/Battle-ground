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

#define y_tir 475
#define x_tir 165



/**
 * \fn void gestion_environnement(t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player, SDL_Renderer *rendu)
 * \brief fonction qui sert à gérer l'environnement et ses interactions avec les entités ainsi que l'interaction des entités elles-mêmes. Une entité s'arrete lorsqu'elle se trouve face à un ennemi en face d'elle et l'attaque. Les autres qui suivent derrière s'arrêtent aussi. Il s'agit de paramétrer et de configurer les limites physiques de l'environnement ainsi que leur conditions.
 * \param t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player, SDL_Renderer *rendu
 */
void gestion_environnement_classique(t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player, joueur *player2, SDL_Renderer *rendu)
{ // fonction qui vérifie qu'un élément ne rentre pas en contact avec un autre
  vague_ennemie = deb_liste_survivant(vague_ennemie);
  vague_joueur = deb_liste_survivant(vague_joueur);
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
    if (vague_joueur->ent->x/*  >= taille_fenetre- 400 */)
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
 * \fn void afficher_survivant(SDL_Renderer *rendu, joueur *player, int pause)
 * \brief fonction qui affiche le décors en mode survivant avec la barre de vie du joueur, son argent, et les menus
 * \param SDL_Renderer *rendu, joueur *player, int pause
 */
void afficher_survivant_classique(SDL_Renderer *rendu, joueur *player, int pause)
{
  int code_contour_barre_vie[4] = {0, 0, 0, 255};
  int code_interieur_barre_vie[4] = {255, 165, 0, 255};
  dessiner_rectangle_vide(rendu, code_contour_barre_vie, taille_fenetre - 10, 180, 202, 12, 0); /*barre de vie du joueur*/     /*barre de vie du joueur*/
  dessiner_rectangle_plein(rendu, code_interieur_barre_vie, taille_fenetre - 11, 181 + (200 - player->pv), player->pv, 10, 0); /*barre de vie du joueur, l'abcisse est proportionnelle au nombre de pv du joueur*/
  if (pause)
  {
    dessiner_rectangle_plein(rendu, code_interieur_barre_vie, taille_fenetre - 620, 10, 50, 20, 0);
    dessiner_rectangle_plein(rendu, code_interieur_barre_vie, taille_fenetre - 650, 10, 50, 20, 0);
  }
  else
  {
    dessiner_rectangle_plein(rendu, code_contour_barre_vie,  taille_fenetre - 620, 10, 50, 20, 0);
    dessiner_rectangle_plein(rendu, code_contour_barre_vie, taille_fenetre - 650, 10, 50, 20, 0);
  }
  if (player->create)
  {
    int code_interieur_creation[4] = {255, 0, 0, 255};
    dessiner_rectangle_vide(rendu, code_contour_barre_vie, taille_fenetre - 220, 100, 12, 272, 0);
    dessiner_rectangle_plein(rendu, code_interieur_creation, taille_fenetre - 221, 101, 10, player->x_create, 0);
  }
}


/**
 * \fn t_wave *ajouter_voisin(joueur *player, t_wave *vague, message *msg)
 * \brief fonction qui crée une entité voisin et renvoie le pointeur sur celle-ci
 * \param joueur *player, t_wave *vague, message *msg
 * \return t_wave *
 */
t_wave *ajouter_voisin_classique(joueur *player, t_wave *vague, message *msg, int cmp)
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
        nouv->ent->pv = 50;
        nouv->ent->montant = 1;
        nouv->ent->type = 1;
        nouv->ent->x = taille_fenetre - 110;
        nouv->ent->y = y_entity;
        nouv->ent->attaque = 1;
        nouv->ent->x_barre = taille_fenetre - 130;
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
        player->argent -= 1200;
        player->create = 1;
        return nouv;
      }
      else
        vague = ajouter_entite_survivant(vague);
      if (vague->prec != NULL)
        vague->ent->temps = 50 + vague->prec->ent->temps;
      strcpy(vague->ent->nom_fichier, "data/entities/voisn/voisn1.png");
      strcpy(vague->ent->nom_fichier_attaque, "data/entities/voisn/voisintir.png");
      vague->ent->pv = 50;
      vague->ent->montant = 1;
      vague->ent->x = taille_fenetre - 110;
      vague->ent->y = y_entity;
      vague->ent->attaque = 1;
      vague->ent->type = 1;
      vague->ent->x_barre = taille_fenetre - 130;
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
      player->argent -= 1200;
      player->create = 1;
      return vague;
    }
    else
      message_box(msg, "data/inventaire/pasassez.png");
  }
  return vague;
}

t_wave *ajouter_bandit_classique(joueur *player, t_wave *vague, message *msg)
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
        nouv->ent->x = taille_fenetre - 110;
        nouv->ent->y = y_entity;
        nouv->ent->attaque = 1;
        nouv->ent->x_barre = taille_fenetre - 130;
        nouv->ent->y_barre = 450;
        nouv->ent->degat = 10;
        nouv->ent->met_a_jour = met_a_jour_images_sprite;
        nouv->ent->charger_img = charger_img_sprite;
        nouv->ent->w = 135;
        nouv->ent->h = 135;
        nouv->ent->type = 2;
        nouv->ent->w_image = 79;
        nouv->ent->h_image = 79;
        nouv->ent->x_image = 0;
        nouv->ent->y_image = 0;
        nouv->ent->nb_pos = 3;
        nouv->ent->nb_pos_attaque = 3;
        player->argent -= 150;
        player->create = 1;
        return nouv;
      }
      else
        vague = ajouter_entite_survivant(vague);
      if (vague->prec != NULL)
        vague->ent->temps = 50 + vague->prec->ent->temps;
      strcpy(vague->ent->nom_fichier, "data/entities/bandit/bandit.png");
      strcpy(vague->ent->nom_fichier_attaque, "NULL");
      vague->ent->pv = 50;
      vague->ent->montant = 1;
      vague->ent->x = taille_fenetre -110;
      vague->ent->y = y_entity;
      vague->ent->attaque = 1;
      vague->ent->x_barre = taille_fenetre - 130;
      vague->ent->y_barre = 450;
      vague->ent->degat = 10;
      vague->ent->met_a_jour = met_a_jour_images_sprite;
      vague->ent->charger_img = charger_img_sprite;
      vague->ent->w = 135;
      vague->ent->h = 135;
      vague->ent->w_image = 79;
      vague->ent->h_image = 79;
      vague->ent->x_image = 0;
      vague->ent->y_image = 0;
      vague->ent->type = 2;
      vague->ent->nb_pos = 3;
      vague->ent->nb_pos_attaque = 3;
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
int etat_partie_classique(t_wave *vague, joueur *player, joueur *player2)
{ // retourne l'état de la partie (0 si elle est toujours en cours, 2 si le joueur a gagné, -1 si il a perdu)
  if (player != NULL && player2 != NULL)
  {
    if (player->pv < 0)
        return 2; //gagné
    else if (player2->pv < 0)
      return -1; //perdu
    else
      return 0;
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
          vague_ennemies = ajouter_voisin_classique(player2, vague_ennemies, &msg, 1);
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
          vague_ennemies = ajouter_bandit_classique(player2, vague_ennemies, &msg);
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
    met_a_jour_img_argent(player2, rendu);


    afficher_survivant(rendu, player, pause);
    afficher_survivant_classique(rendu, player2, pause);

    gestion_environnement_classique(vague_ennemies, vague_joueur, player, player2, rendu);
    if (!pause)
    {
      if (deroulement_vague_classique(player2, vague_ennemies, rendu, 1) == -1)
        vague_ennemies = NULL;
      if (deroulement_vague_classique(player, vague_joueur, rendu, 0) == -1)
        vague_joueur = NULL;
    }
    SDL_RenderPresent(rendu);
  }
  if (etat_partie_classique(vague_ennemies, player, player2) == 2)
  {
    free(player);
    free(player2);
    fin_partie_survivant(vague_ennemies);
    fin_partie_survivant(vague_joueur);
    charger_image("data/inventaire/gagne.png", rendu, 400, 300, 1);
    SDL_Delay(1500);
    return 1;
  }
  else if (etat_partie_classique(vague_ennemies, player, player2) == -1)
  {
    free(player);
    free(player2);
    fin_partie_survivant(vague_ennemies);
    fin_partie_survivant(vague_joueur);
    charger_image("data/inventaire/perd.png", rendu, 400, 300, 1);
    SDL_Delay(1500);
    return 0;
  }
  return 0;
}