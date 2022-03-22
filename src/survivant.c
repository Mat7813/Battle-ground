/**
 * \file survivant.c
 * \brief Contient toutes les fonctions utiles au mode de jeu survivant de
 * battle ground (gestion de l'évolution de la partie, implémentation des
 * structures de jeu, etc..) \author Lazare Maclouf \version 1 \date 25/02/2022
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "animations.h"
#include "interactions.h"
#include "interface.h"
#include "structures.h"
#include "vagues.h"
#define V 5
#define y_entity 470
#define x_def 100
#define y_def 470
#define pv_joueur 200
#define argent_joueur 1000
/**
 * \fn t_wave* charger_niveau(char *nom)
 * \brief fonction qui sert à charger un niveau en mode survivant, en allant
 * chercher dans un fichier dont le nom est passé en paramètres les
 * informations du niveau (pour chaque vagues le nombres d'entités, leur types,
 * leur pv, le temps entre les vagues etc..). \param char *nom \return pointeur
 * sur t_wave qui aura été rempli par les informations contenu dans le fichier.
 */
t_wave *
charger_niveau(char *nom)
{ // charge le niveau à partir d'un fichier txt
  FILE *fichier = fopen(nom, "r");
  if (fichier == NULL)
    return NULL;
  int temps = 0;
  char nom_template[100];
  char nom_template_attaque[100];
  fscanf(fichier, "%s", nom_template);
  fscanf(fichier, "%s", nom_template_attaque);
  t_wave *vagues = creer_vague();
  if (vagues == NULL)
    return NULL;
  while (!feof(fichier))
  {
    strcpy(vagues->ent->nom_fichier, nom_template);
    strcpy(vagues->ent->nom_fichier_attaque, nom_template_attaque);
    printf("adresse : %p\n", vagues);
    fscanf(fichier, "%d/%d/%d/%d/%d/%d", &vagues->ent->pv,
           &vagues->ent->montant, &vagues->ent->x, &vagues->ent->x_barre,
           &vagues->ent->y_barre, &vagues->ent->degat);
    vagues->ent->temps = temps;
    vagues->ent->y = y_entity;
    vagues->ent->attaque = 1;
    temps += 50;
    printf("%s\npv : %d\nmontant : %d\nx : %d\ntemps : %d\n\n",
           vagues->ent->nom_fichier, vagues->ent->pv, vagues->ent->montant,
           vagues->ent->x, vagues->ent->temps);
    vagues = ajouter_entite_survivant(vagues);
  }
  printf("test\n");
  vagues = supprimer_entite_survivant(vagues);
  vagues = supprimer_entite_survivant(vagues);
  printf("adresse en sortie de for : %p\n", vagues);
  printf("%s\npv : %d\nmontant : %d\nx : %d\ntemps : %d\n\n",
         vagues->ent->nom_fichier, vagues->ent->pv, vagues->ent->montant,
         vagues->ent->x, vagues->ent->temps);
  fclose(fichier);
  return vagues;
}

void afficher_status_entite(t_wave *vagues)
{
  printf("%s\npv : %d\nmontant : %d\nx : %d\ntemps : %d\n\n",
         vagues->ent->nom_fichier, vagues->ent->pv, vagues->ent->montant,
         vagues->ent->x, vagues->ent->temps);
}
/**
 * \fn void met_a_jour_images(t_wave *vague, SDL_Renderer *rendu)
 * \brief fonction qui sert à mettre automatiquement les images de l'entité à
 * jour. pour qu'elle continue son animation soit en incrémentant le chiffre
 * correspondant au numéro de l'image soit en le décrémentant et en changeant
 * l'indice d'animation à chaque fois que nécéssaire \param t_wave *vague,
 * SDL_Renderer *rendu \return rien
 */
void met_a_jour_images(t_wave *vagues)
{
  if (vagues != NULL)
  {
    if (vagues->ent->montant == 2)
      return;
    else
    {
      if (vagues->ent->nom_fichier[25] < 57 && vagues->ent->montant)
      {
        vagues->ent->nom_fichier[25]++;
        if (!fichier_existe(vagues->ent->nom_fichier))
          vagues->ent->nom_fichier[25]--;
      }
      else if (vagues->ent->nom_fichier[25] == 57 && vagues->ent->montant)
      {
        vagues->ent->nom_fichier[25]--;
        if (!fichier_existe(vagues->ent->nom_fichier))
          vagues->ent->nom_fichier[25]++;
        vagues->ent->montant = 0;
      }
      else if (vagues->ent->nom_fichier[25] > 49 && !vagues->ent->montant)
      {
        vagues->ent->nom_fichier[25]--;
        if (!fichier_existe(vagues->ent->nom_fichier))
          vagues->ent->nom_fichier[25]++;
      }
      else if (vagues->ent->nom_fichier[25] == 49 && !vagues->ent->montant)
      {
        vagues->ent->nom_fichier[25]++;
        if (!fichier_existe(vagues->ent->nom_fichier))
          vagues->ent->nom_fichier[25]--;
        vagues->ent->montant = 1;
      }
    }
  }
}
/**
 * \fn void deroulement_vagues(t_wave *vagues, SDL_Renderer *rendu);
 * \brief fonction qui sert à mettre automatiquement les images de l'entité à
 * jour. pour qu'elle continue son animation soit en incrémentant le chiffre
 * correspondant au numéro de l'image soit en le décrémentant et en changeant
 * l'indice d'animation à chaque fois que nécéssaire. le parametre camp sert à
 * préciser le camp de la vague d'entités (1 pour l'ennemi 0 pour le joueur)
 * \param t_wave *vague, SDL_Renderer *rendu, int camp
 * \return rien
 */
int deroulement_vagues(joueur *player, t_wave *vagues, SDL_Renderer *rendu,
                       int camp)
{ /**/
  int code_contour_barre_vie[4] = {0, 0, 0, 255};
  int code_interieur_barre_vie[4] = {255, 165, 0, 255};
  vagues = deb_liste_survivant(vagues);
  if (vagues != NULL)
  {
    while (vagues->suiv != NULL)
    {
      if (!vagues->ent->temps && vagues->ent->pv > 0)
      {
        if (vagues->ent->attaque != 0)
          charger_image(vagues->ent->nom_fichier, rendu, vagues->ent->x,
                        vagues->ent->y, 0);
        met_a_jour_images(vagues);
        dessiner_rectangle_vide(rendu, code_contour_barre_vie,
                                vagues->ent->x_barre,
                                vagues->ent->y_barre, 8, 52,
                                0); /*met à jour la barre de vie*/
        dessiner_rectangle_plein(
            rendu, code_interieur_barre_vie, vagues->ent->x_barre + 1,
            vagues->ent->y_barre + 1, 6, vagues->ent->pv, 0);
        if (camp && vagues->ent->montant != 2)
        {
          vagues->ent->x -= 2;
          vagues->ent->x_barre -= 2;
        }
        else if (!camp && vagues->ent->montant != 2)
        {
          vagues->ent->x += 2;
          vagues->ent->x_barre += 2;
        }
      }
      else if (vagues->ent->temps > 0)
      {
        vagues->ent->temps--;
        vagues = suivant_entite_survivant(vagues);
      }
      if (vagues->ent->pv <= 0)
      {
        vagues = supprimer_entite_survivant(vagues);
        if (camp)
          player->argent += 130;
        if (vagues == NULL)
          return -1;
      }
      else if (vagues->ent->pv > 0 && !vagues->ent->temps)
        vagues = suivant_entite_survivant(vagues);
    }
  }
  if (vagues != NULL)
  { // dans le cas ou il ne reste plus qu'une entité dans
    // la liste ou on est à la fin
    if (!vagues->ent->temps && vagues->ent->pv > 0)
    {
      // printf("derniere adresse : %p\n", vagues);
      if (vagues->ent->attaque != 0)
        charger_image(vagues->ent->nom_fichier, rendu, vagues->ent->x,
                      vagues->ent->y, 0);
      met_a_jour_images(vagues);
      dessiner_rectangle_vide(rendu, code_contour_barre_vie,
                              vagues->ent->x_barre, vagues->ent->y_barre,
                              8, 52, 0); /*met à jour la barre de vie*/
      dessiner_rectangle_plein(
          rendu, code_interieur_barre_vie, vagues->ent->x_barre + 1,
          vagues->ent->y_barre + 1, 6, vagues->ent->pv, 0);
      if (camp && vagues->ent->montant != 2)
      {
        vagues->ent->x -= 2;
        vagues->ent->x_barre -= 2;
      }
      else if (!camp && vagues->ent->montant != 2)
      {
        vagues->ent->x += 2;
        vagues->ent->x_barre += 2;
      }
    }
    if (vagues->ent->temps > 0)
    {
      vagues->ent->temps--;
    }
    if (vagues->ent->pv <= 0)
    {
      vagues = supprimer_entite_survivant(vagues);
      if (camp)
        player->argent += 130;
      if (vagues == NULL)
        return -1;
    }
  }
  else
    return 1;
  return 0;
}

int fin_partie_survivant(t_wave *vagues)
{
  vagues = vider_liste_survivant(vagues);
  return (vagues == NULL);
}

joueur *
creer_joueur(joueur *player)
{
  player = malloc(sizeof(joueur));
  player->pv = pv_joueur;
  player->argent = argent_joueur;
  player->t = NULL;
  player->def = NULL;
  strcpy(player->nom, "Lazare");
  return player;
}

void message_box(message *msg, char nom_fic[100])
{
  if (nom_fic != 0)
  {
    msg->temps = 50;
    strcpy(msg->nom_fichier, nom_fic);
    msg->x = 200;
    msg->y = 200;
    printf("msg.temps=%d, msg.nom_fichier=%s\n", msg->temps,
           msg->nom_fichier);
  }
  else
  {
    printf("tps=0\n");
    msg->temps = 0;
  }
}

t_wave *
ajouter_voisin(joueur *player, t_wave *vague, message *msg)
{
  if (player != NULL)
  {
    if (player->argent >= 100)
    {
      vague = fin_liste_survivant(vague);
      if (vague == NULL)
      {
        t_wave *nouv = creer_vague();
        nouv->ent->temps = 0;
        strcpy(nouv->ent->nom_fichier,
               "data/entities/voisin/voisin1.png");
        strcpy(nouv->ent->nom_fichier_attaque,
               "data/entities/voisin/voisintir.png");
        nouv->ent->pv = 50;
        nouv->ent->montant = 1;
        nouv->ent->x = 110;
        nouv->ent->y = y_entity;
        nouv->ent->attaque = 1;
        nouv->ent->x_barre = 130;
        nouv->ent->y_barre = 450;
        nouv->ent->degat = 10;
        printf("nouv\n");
        player->argent -= 100;
        return nouv;
      }
      else
        vague = ajouter_entite_survivant(vague);
      if (vague->prec != NULL)
      {
        printf("différent de NULL !!!!\n");
        vague->ent->temps = 50 + vague->prec->ent->temps;
        printf("temps : %d\n", vague->ent->temps);
      }
      strcpy(vague->ent->nom_fichier, "data/entities/voisin/voisin1.png");
      strcpy(vague->ent->nom_fichier_attaque,
             "data/entities/voisin/voisintir.png");
      vague->ent->pv = 50;
      vague->ent->montant = 1;
      vague->ent->x = 110;
      vague->ent->y = y_entity;
      vague->ent->attaque = 1;
      vague->ent->x_barre = 130;
      vague->ent->y_barre = 450;
      vague->ent->degat = 10;
      printf("ancien\n");
      player->argent -= 100;
      return vague;
    }
    else
      message_box(msg, "data/inventaire/pasassez.png");
  }
  return vague;
}

int etat_partie_survivant(t_wave *vagues, joueur *player)
{ // retourne l'état de la partie (0 si elle est toujours
  // en cours, 2 si le joueur a gagné, -1 si il a perdu)
  if (player != NULL)
  {
    if (player->pv > 0)
    {
      if (vagues == NULL)
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

int return_message()
{ // message qui lorsqu'on clique sur la croix rouge est
  // affiché pour éviter de tout perdre en pleine partie
  const SDL_MessageBoxButtonData buttons[] = {
      {/* .flags, .buttonid, .text */ 0, 0, "NON"},
      {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OUI"},
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "ANNULER"},
  };
  const SDL_MessageBoxColorScheme colorScheme = {{{255, 0, 0},
                                                  {0, 255, 0},
                                                  {255, 255, 0},
                                                  {0, 0, 255},
                                                  {255, 0, 255}}};
  const SDL_MessageBoxData messageboxdata = {
      SDL_MESSAGEBOX_INFORMATION, /* .flags */
      NULL,                       /* .window */
      "Retour au menu",           /* .title */
      "Etes-vous sûr de vouloir quitter ?\nLa partie ne sera pas "
      "sauvegardée.",         /* .message */
      SDL_arraysize(buttons), /* .numbuttons */
      buttons,                /* .buttons */
      &colorScheme            /* .colorScheme */
  };
  int buttonid;
  if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
  {
    SDL_Log("error displaying message box");
    return 1;
  }
  if (buttonid == 1)
    return -1;
  else
    return 0;
}

int demarrer_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event,
                       char lvl)
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
  joueur *player = NULL;
  player = creer_joueur(player);
  printf("sortie de la fonction vague_ennemies\n");
  charger_image(bg, rendu, 0, 0, 1);
  int pause = 0;
  while (etat_partie_survivant(vague_ennemies, player) == 0)
  {
    while (SDL_PollEvent(event))
    { // on réécoute les évènements mais avec un
      // pointeur sur event car en SDL on ne peut
      // pas faire plusieurs listener d'évènements.
      //  if(etat_partie_survivant(vagues, &player)==1)return 1;//on
      //  verifie à chaque tour de boucle l'état de la partie
      //  if(etat_partie_survivant(vagues, &player)==-1)return 0;
      if (event->type == SDL_QUIT)
      { // lorsque l'utilisateur appuie sur la
        // croix rouge de la fenetre
        if (quit_message() == -1)
        {
          fin_partie_survivant(vague_ennemies);
          fin_partie_survivant(vague_joueur);
          return -1; // on retourne -1
        }
      }
      if (event->window.event == SDL_WINDOWEVENT_RESIZED)
        SDL_SetWindowSize(window, 1250, 694);
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
      { // pour les trois conditions qui suivent : si
        // l'utilisateur passe sa souris dans la zone d'un bouton
        // (jouer, paramètres ou quitter), on change le fond du
        // bouton en chargeant la version "over" de celui-ci
        indic = 1;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          vague_joueur = ajouter_voisin(
              player, vague_joueur,
              &msg); /*ajouter_voisin(player, vague_joueur);*/
      }
      else if ((event->motion.x >= 290 && event->motion.x <= 350) && (event->motion.y >= 10 && event->motion.y <= 60))
      { // pour les trois conditions qui suivent : si
        // l'utilisateur passe sa souris dans la zone d'un
        // bouton (jouer, paramètres ou quitter), on
        // change le fond du bouton en chargeant la
        // version "over" de celui-ci
        indic = 2;
      }
      else if ((event->motion.x >= 360 && event->motion.x <= 420) && (event->motion.y >= 10 && event->motion.y <= 60))
      { // pour les trois conditions qui suivent : si
        // l'utilisateur passe sa souris dans la zone d'un
        // bouton (jouer, paramètres ou quitter), on
        // change le fond du bouton en chargeant la
        // version "over" de celui-ci
        indic = 3;
      }
      else if ((event->motion.x >= 430 && event->motion.x <= 500) && (event->motion.y >= 10 && event->motion.y <= 60))
      { // pour les trois conditions qui suivent : si
        // l'utilisateur passe sa souris dans la zone d'un
        // bouton (jouer, paramètres ou quitter), on
        // change le fond du bouton en chargeant la
        // version "over" de celui-ci
        indic = 4;
        if (event->type == SDL_MOUSEBUTTONDOWN)
          creer_defense(player, x_def, y_def, 15, &msg);
      }
      else if ((event->motion.x >= 0 && event->motion.x <= 100) && (event->motion.y >= 0 && event->motion.y <= 30))
      { // pour les trois conditions qui suivent : si
        // l'utilisateur passe sa souris dans la zone d'un
        // bouton (jouer, paramètres ou quitter), on
        // change le fond du bouton en chargeant la
        // version "over" de celui-ci
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
        printf("temp>0\n");
        if (fichier_existe(msg.nom_fichier))
          charger_image(msg.nom_fichier, rendu, msg.x, msg.y, 0);
        else
          printf("fichier existe pas pour msg\n");
        msg.temps--;
      }
      else
        printf("temps==0\n");
    }
    if (msg.temps > 0)
    {
      printf("temp>0\n");
      if (fichier_existe(msg.nom_fichier))
        charger_image(msg.nom_fichier, rendu, msg.x, msg.y, 0);
      else
        printf("fichier existe pas pour msg\n");
      msg.temps--;
    }
    else
      printf("temps==0\n");
    if (!pause)
    {
      charger_image(bg, rendu, 0, 0, 0);
      charger_image("data/inventaire/backover.png", rendu, 0, 10, 0);
      charger_image("data/inventaire/carre1.png", rendu, 220, 10, 0);
      charger_image("data/inventaire/carre.png", rendu, 290, 10, 0);
      charger_image("data/inventaire/carre.png", rendu, 360, 10, 0);
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
        charger_image("data/inventaire/carre.png", rendu, 290, 10, 0);
      if (indic != 3)
        charger_image("data/inventaire/carre.png", rendu, 360, 10, 0);
      if (indic != 4)
        charger_image("data/inventaire/carre4.png", rendu, 430, 10, 0);
      if (indic != 5)
        charger_image("data/inventaire/back.png", rendu, 0, 10, 0);
      if (msg.temps > 0)
      {
        printf("temp>0\n");
        if (fichier_existe(msg.nom_fichier))
          charger_image(msg.nom_fichier, rendu, msg.x, msg.y, 0);
        else
          printf("fichier existe pas pour msg\n");
        msg.temps--;
      }
      else
        printf("temps==0\n");
    }
    afficher_survivant(rendu, player, pause);
    gestion_environnement(vague_ennemies, vague_joueur, player, rendu);
    if (!pause)
    {
      if (deroulement_vagues(player, vague_ennemies, rendu, 1) == -1)
        vague_ennemies = NULL;
      if (deroulement_vagues(player, vague_joueur, rendu, 0) == -1)
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
