/**
 * \file interactions.c
 * \brief Contient des fonctions variées utilisées potentiellement par les 2 modes de jeu. des fonctions telles que la gestion de l'environnement(les collisions).
 * \author Lazare Maclouf
 * \version 1
 * \date 08/02/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "structures.h"
#include "animations.h"
#include "survivant.h"
#define y_tir 475
#define x_tir 165
#define ATTACK_DEF -1
/**
 * \fn void attaque_entites(t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player)
 * \brief fonction qui sert à gérer les attaques des entités entre elles (les dégats qu'elles se causent lorsqu'elles s'affrontent)
 * \param t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player

 */
void attaque_entites(t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player)
{
  vague_ennemie = deb_liste_survivant(vague_ennemie);
  vague_joueur = deb_liste_survivant(vague_joueur);
  if (vague_ennemie != NULL && vague_joueur != NULL)
  {
    if (vague_ennemie->ent->x <= vague_joueur->ent->x + 60)
    {
      vague_ennemie->ent->montant = 2;
      vague_joueur->ent->montant = 2;
      if (!vague_ennemie->ent->attaque)
      {
        vague_joueur->ent->pv -= vague_ennemie->ent->degat;
        vague_ennemie->ent->attaque = 15;
      }
      else
        vague_ennemie->ent->attaque--;
    }
    if (vague_ennemie->ent->x <= vague_joueur->ent->x + 60 && vague_joueur->ent->type == 2)
    {
      vague_joueur->ent->montant = 2;
      vague_ennemie->ent->montant = 2;
      if (!vague_joueur->ent->attaque)
      {
        vague_ennemie->ent->pv -= vague_joueur->ent->degat;
        vague_joueur->ent->attaque = 20;
      }
      else
        vague_joueur->ent->attaque--;
      // if(vague_ennemie->ent->montant==2)vague_ennemie->ent->montant=1;
    }
    else if (vague_ennemie->ent->x <= vague_joueur->ent->x + 520 && vague_joueur->ent->type == 1)
    {
      vague_joueur->ent->montant = 2;
      if (vague_ennemie->ent->x > vague_joueur->ent->x + 60)
        vague_ennemie->ent->montant = 1;
      if (!vague_joueur->ent->attaque)
      {
        vague_ennemie->ent->pv -= vague_joueur->ent->degat;
        vague_joueur->ent->attaque = 20;
      }
      else
        vague_joueur->ent->attaque--;
      // if(vague_ennemie->ent->montant==2)vague_ennemie->ent->montant=1;
    }
    else
    {
      vague_joueur->ent->attaque = 1;
      vague_ennemie->ent->attaque = 1;
      if (vague_ennemie->ent->montant == 2)
        vague_ennemie->ent->montant = 1;
      if (vague_joueur->ent->montant == 2)
        vague_joueur->ent->montant = 1;
    }
  }
  else if (vague_ennemie != NULL || vague_joueur != NULL)
  {
    if (vague_ennemie != NULL)
      if (vague_ennemie->ent->montant == 2)
        vague_ennemie->ent->montant = 1;
    if (vague_joueur != NULL)
      if (vague_joueur->ent->montant == 2)
        vague_joueur->ent->montant = 1;
  }
  if (vague_ennemie != NULL)
  {
    if (vague_ennemie->ent->x <= 105)
    {
      vague_ennemie->ent->montant = 2;
      if (!vague_ennemie->ent->attaque)
      {
        player->pv -= vague_ennemie->ent->degat;
        vague_ennemie->ent->attaque = 20;
      }
      else
        vague_ennemie->ent->attaque--;
    }
    else if (vague_ennemie->ent->attaque <= 20 && vague_ennemie->ent->attaque >= 18)
      vague_ennemie->ent->attaque = 3;
    if (player->def != NULL)
    {
      if (player->t != NULL)
      {
        if (vague_ennemie->ent->x <= player->t->x)
        {
          vague_ennemie->ent->pv -= player->def->degat;
          player->t->indice_vie = 0;
        }
      }
    }
  }
  if (vague_joueur != NULL)
  {
    if (vague_joueur->ent->x >= 990)
    {
      vague_joueur->ent->montant = 2;
    }
  }
}
/**
 * \fn tir *t creer_tir(tir *t, int x, int y)
 * \brief Sert à créer un tir en allouant la mémoire nécéssaire et en initialisant ses attributs avec les valeurs passées en paramètres.
 * \param tir *t, int x, int y
 * \return tir *t
 */
tir *creer_tir(tir *t, int x, int y)
{
  t = malloc(sizeof(tir));
  strcpy(t->nom_fichier, "data/entities/projectiles/tir1.png");
  t->indice_vie = 1;
  t->x = x;
  t->y = y;
  return t;
}
/**
 * \fn void creer_defense(joueur *p, int x, int y, int degat, message *msg)
 * \brief Sert à créer une défense en allouant la mémoire nécéssaire et en initialisant ses attributs avec les valeurs passées en paramètres.
 * \param joueur *p, int x, int y, int degat, message *msg
 */
void creer_defense(joueur *p, int x, int y, int degat, message *msg)
{
  if (p != NULL)
  {
    if (p->def == NULL)
    {
      if (p->argent >= 2000)
      {
        p->def = malloc(sizeof(defense));
        strcpy(p->def->nom_fichier, "data/inventaire/mitraillette.png");
        p->def->degat = degat;
        p->def->indice_vie = 1;
        p->def->temps = 0;
        p->def->x = x;
        p->def->y = y;
        p->argent -= 2000;
      }
      else
        message_box(msg, "data/inventaire/pasassez.png");
    }
    else
      message_box(msg, "data/inventaire/defense.png");
  }
}

/**
 * \fn tir *t etat_tir(tir *t)
 * \brief Sert à mettre à jour un tir. Si il a été en contact avec une entité et lui a fait des dégats (son indice_vie sera à 0). Il sera donc détruit et la fonction retournera NULL.
 * \param tir *t
 * \return tir *t
 */
tir *etat_tir(tir *t)
{
  if (t != NULL)
  {
    if (!t->indice_vie)
    {
      free(t);
      return NULL;
    }
    else
      return t;
  }
  return NULL;
}
/**
 * \fn defense *etat_defense(defense *def)
 * \brief Sert à mettre à jour une défense.
 * \param defense *def
 * \return defense *def
 */
defense *etat_defense(defense *def)
{
  if (def != NULL)
  {
    if (!def->indice_vie)
    {
      free(def);
      return NULL;
    }
    else
      return def;
  }
  return NULL;
}

/**
 * \fn gestion_ligne_entite(t_wave *vague, int camp)
 * \brief Sert à la gestion des listes chaînées d'entités. Si la première entité de la file s'arrête à cause d'un obstacle les autres derrières suivront et s'arrêteront elles aussi
 * \param t_wave *vague, int camp
 */
void gestion_ligne_entite(t_wave *vague, int camp)
{
  vague = deb_liste_survivant(vague);
  if (vague != NULL)
  {
    while (vague->suiv != NULL)
    {
      if (camp)
      {
        if (vague->suiv->ent->x <= vague->ent->x + 80)
          vague->suiv->ent->montant = 2;
        else if (vague->suiv->ent->montant == 2)
          vague->suiv->ent->montant = 1;
        vague = suivant_entite_survivant(vague);
      }
      else
      {
        if (vague->suiv->ent->x >= vague->ent->x - 90)
          vague->suiv->ent->montant = 2;
        else if (vague->suiv->ent->montant == 2)
          vague->suiv->ent->montant = 1;
        vague = suivant_entite_survivant(vague);
      }
    }
    if (vague != NULL && vague->prec != NULL)
    {
      if (camp)
      {
        if (vague->ent->x <= vague->prec->ent->x + 80)
          vague->ent->montant = 2;
        else if (vague->ent->montant == 2)
          vague->ent->montant = 1;
      }
      else
      {
        if (vague->ent->x >= vague->prec->ent->x - 90)
          vague->ent->montant = 2;
        else if (vague->ent->montant == 2)
          vague->ent->montant = 1;
      }
    }
  }
}
/**
 * \fn void gestion_environnement(t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player, SDL_Renderer *rendu)
 * \brief fonction qui sert à gérer l'environnement et ses interactions avec les entités ainsi que l'interaction des entités elles-mêmes. Une entité s'arrete lorsqu'elle se trouve face à un ennemi en face d'elle et l'attaque. Les autres qui suivent derrière s'arrêtent aussi. Il s'agit de paramétrer et de configurer les limites physiques de l'environnement ainsi que leur conditions.
 * \param t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player, SDL_Renderer *rendu
 */
void gestion_environnement(t_wave *vague_ennemie, t_wave *vague_joueur, joueur *player, SDL_Renderer *rendu)
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
  gestion_ligne_entite(vague_ennemie, 1);
  gestion_ligne_entite(vague_joueur, 0);
  attaque_entites(vague_ennemie, vague_joueur, player);
  animation_attaque(rendu, vague_ennemie);
  animation_attaque(rendu, vague_joueur);
  animation_tir_gauche(rendu, player);
  player->t = etat_tir(player->t); /*on met à jour le tir si besoin*/
  player->def = etat_defense(player->def);
}

/**
 * \fn int fichier_existe(char *nom)
 * \brief fonction qui sert à verifier l'existance d'un fichier dont le nom est passé en paramètre en tentant de l'ouvrir en mode lecture.
 * \param char *nom
 * \return int (0 si il n'existe pas et 1 si il existe)
 */
int fichier_existe(char *nom)
{
  FILE *fic = fopen(nom, "r");
  if (fic == NULL)
  {
    return 0;
  }
  else
  {
    fclose(fic);
    return 1;
  }
}
