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

/**
 * \fn t_wave* charger_niveau(char *nom)
 * \brief fonction qui sert à charger un niveau en mode survivant, en allant chercher dans un fichier dont le nom est
 * passé en paramètres les informations du niveau (pour chaque vague le nombres d'entités, leur types, leur pv, le temps
 * entre les vague etc..). \param char *nom \return t_wave * (pointeur sur t_wave qui aura été rempli par les
 * informations contenu dans le fichier.)
 */
t_wave *charger_niveau(char *nom)
{ // charge le niveau à partir d'un fichier txt
  FILE *fichier = fopen(nom, "r");
  if (fichier == NULL)
    return NULL;
  int temps = 0;
  char nom_template[100];
  char nom_template_attaque[100];
  fscanf(fichier, "%s", nom_template);
  fscanf(fichier, "%s", nom_template_attaque);
  t_wave *vague = creer_vague();
  if (vague == NULL)
    return NULL;
  while (!feof(fichier))
  {
    fscanf(fichier, "%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d", &vague->ent->pv, &vague->ent->montant,
           &vague->ent->x, &vague->ent->x_barre, &vague->ent->y_barre, &vague->ent->degat, &vague->ent->w,
           &vague->ent->h, &vague->ent->x_image, &vague->ent->y_image, &vague->ent->w_image, &vague->ent->h_image,
           &vague->ent->nb_pos, &vague->ent->nb_pos_attaque);
    strcpy(vague->ent->nom_fichier, nom_template);
    strcpy(vague->ent->nom_fichier_attaque, nom_template_attaque);
    if (!vague->ent->pv)
    { /*si pv==0 alors cela veut dire qu'on ajoute du temps d'attente entre la prochaine vague*/
      temps += 600;
      vague->ent->temps = temps;
      vague->ent->pv = 50; /*on remet pv à 50 (par défaut)*/
    }
    else
      vague->ent->temps = temps;
    vague->ent->y = y_entity;
    vague->ent->attaque = 1;
    if (vague->ent->w_image != 0)
    {
      vague->ent->met_a_jour = met_a_jour_images_sprite;
      vague->ent->charger_img = charger_img_sprite;
      vague->ent->nom_fichier_attaque[0] =
          0; /*servira à réguler l'animation pour les entités ayant ce fichier à NULL*/
    }
    else
    {
      vague->ent->met_a_jour = met_a_jour_images_separees;
      vague->ent->charger_img = charger_img_separees;
    }
    temps += 50;
    vague = ajouter_entite_survivant(vague);
  }
  vague = supprimer_entite_survivant(vague);
  vague = supprimer_entite_survivant(vague);
  fclose(fichier);
  return vague;
}

/**
 * \fn void deroulement_vague(joueur *player, t_wave *vague, SDL_Renderer *rendu, int camp)
 * \brief fonction qui sert à mettre automatiquement les images des entités à jour ainsi que d'autres champs (points de
 * vie, position etc...). \param t_wave *vague, SDL_Renderer *rendu, int camp \return rien
 */
int deroulement_vague(joueur *player, t_wave *vague, SDL_Renderer *rendu, int camp)
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
    if (!vague->ent->temps && vague->ent->pv > 0)  //metre tout à jour
    {
      if (vague->ent->attaque != 0)
        vague->ent->charger_img(vague->ent, rendu);
      vague->ent->met_a_jour(vague->ent);
      dessiner_rectangle_vide(rendu, code_contour_barre_vie, vague->ent->x_barre, vague->ent->y_barre, 8, 52,
                              0); /*met à jour la barre de vie*/
      dessiner_rectangle_plein(rendu, code_interieur_barre_vie, vague->ent->x_barre + 1, vague->ent->y_barre + 1,
                               6, vague->ent->pv, 0);
      if (camp && vague->ent->montant != 2) //joueur2
      {
        vague->ent->x -= 2;
        vague->ent->x_barre -= 2;
      }
      else if (!camp && vague->ent->montant != 2) //joueur1
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
    if (vague->ent->temps > 0) //attendre le temps pour continuer
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

    if (vague->ent->pv <= 0) //quand l'entité n'a plus de vie
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
int fin_partie_survivant(t_wave *vague)
{
  vague = vider_liste_survivant(vague);
  return (vague == NULL);
}

/**
 * \fn joueur *creer_joueur()
 * \brief fonction qui sert à créer une variable de type joueur pour la partie.
 * \param void
 * \return joueur *
 */
joueur *creer_joueur()
{
  joueur *player = malloc(sizeof(joueur));
  player->pv = pv_joueur;
  player->argent = argent_joueur;
  player->t = NULL;
  player->def = NULL;
  player->create = 0;
  player->x_create = 1;
  strcpy(player->nom, "Lazare");
  return player;
}

/**
 * \fn void message_box(message *msg, char nom_fic[100])
 * \brief fonction qui sert à créer une variable de msg.
 * \param message *msg, char nom_fic[100]
 */
void message_box(message *msg, char nom_fic[100])
{
  if (nom_fic != 0)
  {
    msg->temps = 50;
    strcpy(msg->nom_fichier, nom_fic);
    msg->x = 200;
    msg->y = 200;
  }
  else
  {
    msg->temps = 0;
  }
}

/**
 * \fn int etat_partie_survivant(t_wave *vague, joueur *player)
 * \brief fonction qui sert à vérifier si la partie est finie ou si elle est toujours en cours (et si elle est finie si
 * le joueur a gagné ou perdu) \param t_wave *vague, joueur *player \return int
 */
int etat_partie_survivant(t_wave *vague, joueur *player)
{ // retourne l'état de la partie (0 si elle est toujours en cours, 2 si le joueur a gagné, -1 si il a perdu)
  if (player != NULL)
  {
    if (player->pv > 0)
    {
      if (vague == NULL)
      {
        printf("gagné\n");
        return 2;
      }
      return 0;
    }
    else
      return -1;
  }
  return 1; // si on est pas rentré
}

/**
 * \fn int return_message()
 * \brief fonction qui sert à afficher un message de prévention lorsque l'utilisateur veut quitter une partie lancée et
 * en fonction du retour de ce dernier (oui, non ou annuler) retourner une valeur entière \param void \return int
 */
int return_message()
{ // message qui lorsqu'on clique sur la croix rouge est affiché pour éviter de tout perdre en pleine partie
  const SDL_MessageBoxButtonData buttons[] = {
      {/* .flags, .buttonid, .text */ 0, 0, "NON"},
      {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OUI"},
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "ANNULER"},
  };
  const SDL_MessageBoxColorScheme colorScheme = {
      {{255, 0, 0}, {0, 255, 0}, {255, 255, 0}, {0, 0, 255}, {255, 0, 255}}};
  const SDL_MessageBoxData messageboxdata = {
      SDL_MESSAGEBOX_INFORMATION,                                               /* .flags */
      NULL,                                                                     /* .window */
      "Retour au menu",                                                         /* .title */
      "Etes-vous sûr de vouloir quitter ?\nLa partie ne sera pas sauvegardée.", /* .message */
      SDL_arraysize(buttons),                                                   /* .numbuttons */
      buttons,                                                                  /* .buttons */
      &colorScheme                                                              /* .colorScheme */
  };
  int buttonid;
  if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
  {
    SDL_Log("error displaying message box");
    return 1;
  }
  if (buttonid == 1)
  {
    return -1;
  }
  else
    return 0;
}
/**
 * \fn int demarrer_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, char lvl)
 * \brief Comme son nom l'indique, cette fonction démarre le mode survivant. C'est la fonction principale du mode jeu
 * survivant et s'occupe de tout gérer (les évènements, l'argent et les unités de l'utilisateur; charger le niveau et
 * toutes les entités qui vont avec etc/..) \param SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, char lvl
 * \return int
 */
int demarrer_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, char lvl)
{ // crée un ordinateur avec le nombre de vague liées au niveau.
  int indic;
  message msg;
  message_box(&msg, 0);
  char level[100] = "data/modejeu/survivant/level1.txt";
  level[28] = lvl;
  char bg[100] = "data/backgrounds/bg1survie.png";
  bg[19] = lvl;
  t_wave *vague_ennemies = charger_niveau(level);
  if (vague_ennemies == NULL)
    printf("echec lors de la creation de vague\n");
  t_wave *vague_joueur = NULL;
  joueur *player = creer_joueur();
  charger_image(bg, rendu, 0, 0, 1);
  int pause = 0;
  while (etat_partie_survivant(vague_ennemies, player) == 0)
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
          fin_partie_survivant(vague_ennemies);
          fin_partie_survivant(vague_joueur);
          return -1; // on retourne -1
        }
      }
      if (event->window.event == SDL_WINDOWEVENT_RESIZED)
      {
        SDL_SetWindowSize(window, 1250, 694);
      }
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
      { // pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton
        // (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
        indic = 2;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          vague_joueur = ajouter_fighter(player, vague_joueur, &msg);
      }
      else if ((event->motion.x >= 360 && event->motion.x <= 420) &&
               (event->motion.y >= 10 && event->motion.y <= 60))
      { // pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton
        // (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
        if (event->type == SDL_MOUSEBUTTONDOWN)
          vague_joueur = ajouter_bandit(player, vague_joueur, &msg);
        indic = 3;
      }
      else if ((event->motion.x >= 430 && event->motion.x <= 500) &&
               (event->motion.y >= 10 && event->motion.y <= 60))
      { // pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton
        // (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
        indic = 4;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          creer_defense(player, x_def, y_def, 15, &msg);
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
      charger_image("data/inventaire/survivant.png", rendu, 740, 10, 0);
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
    }
    met_a_jour_img_argent(player, rendu);
    afficher_survivant(rendu, player, pause);
    gestion_environnement(vague_ennemies, vague_joueur, player, rendu);
    if (!pause)
    {
      if (deroulement_vague(player, vague_ennemies, rendu, 1) == -1)
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