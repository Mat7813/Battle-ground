/**
 * \file survivant.c
 * \brief Contient toutes les fonctions utiles au mode de jeu survivant de battle ground (gestion de l'évolution de la partie, implémentation des structures de jeu, etc..)
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
#include "animations.h"
#include "divers.h"
#include "structures.h"
#define V 5
#define y_entity 470
/**
 * \fn  t_wave* creer_vague()
 * \brief crée une variable de type t_wave (une vague).
 * \param rien
 * \return pointeur sur t_wave
 */
t_wave* creer_vague(){
   t_wave *vague=malloc(sizeof(t_wave));
   if(vague==NULL)return  NULL;
   vague->ent=malloc(sizeof(entite));
   vague->prec=NULL;
   return vague;
 }
 /**
  * \fn  t_wave *suivant_entite_survivant(t_wave *vague)
  * \brief place le pointeur passé en paramètre de la liste sur l'élément suivant
  * \param t_wave *vague
  * \return pointeur sur t_wave
  */
t_wave *suivant_entite_survivant(t_wave *vague){
    if(vague==NULL)return NULL;
    if(vague->suiv!=NULL)vague=vague->suiv;
    return vague;
  }
 /**
  * \fn  t_wave* precedent_entite_survivant(t_wave *vague)
  * \brief place le pointeur passé en paramètre de la liste sur l'élément précédent
  * \param t_wave *vague
  * \return pointeur sur t_wave (NULL si on est hors liste et l'élément précédent si il est différent de NULL)
  */
t_wave* precedent_entite_survivant(t_wave *vague){
    if(vague==NULL)return NULL;
    if(vague->prec!=NULL)vague=vague->prec;
    return vague;
  }

 /**
  * \fn  t_wave* fin_liste_survivant(t_wave  *vague)
  * \brief place le pointeur passé en paramètre à la fin de la liste il s'agit d'une boucle. tant qu'on est pas à la fin de la liste on continue à avancer dans la liste à l'aide la fonction suivant_entite_survivant
  * \param t_wave *vague
  * \return pointeur sur t_wave (NULL si on est hors liste et l'élément suivant si il est différent de NULL)
  */
t_wave* fin_liste_survivant(t_wave  *vague){
    if(vague==NULL)return NULL;
    if(vague->suiv==NULL)return vague;
    while(vague->suiv!=NULL){
      vague=suivant_entite_survivant(vague);
    }
    return vague;
  }
 /**
  * \fn  t_wave* deb_liste_survivant(t_wave *vague)
  * \brief place le pointeur passé en paramètre au début de la liste. il s'agit d'une boucle. tant qu'on est pas au début de la liste on continue à reculer dans la liste à l'aide la fonction precedent_entite_survivant
  * \param t_wave *vague
  * \return pointeur sur t_wave
  */
t_wave* deb_liste_survivant(t_wave *vague){
    if(vague==NULL)return NULL;
    if(vague->prec==NULL)return vague;
    while(vague->prec!=NULL){
      vague=precedent_entite_survivant(vague);
    }
    return vague;
  }

  /**
   * \fn int liste_vide_survivant(t_wave *vague)
   * \brief indique si la liste est vide ou pas au niveau survivant. Pour le savoir, on se place au début de la liste puis on regarde si le premier élément est null si c'est le cas, la liste est vide
   * \param wave *vague
   * \return 1 si hors_liste 0 sinon
   */
int liste_vide_survivant(t_wave *vague){
     vague=deb_liste_survivant(vague);
     return(vague==NULL);
   }
 /**
  * \fn  t_wave* ajouter_entite_survivant(t_wave *vague)
  * \brief ajoute une entité à la liste et met le pointeur passé en paramètre sur le nouvel élément. Pour ajouter un nouvel element on fait appel à la fonction creer_vague()
  * \param t_wave *vague
  * \return pointeur sur t_wave
  */
t_wave* ajouter_entite_survivant(t_wave *vague){
    t_wave *nouv=creer_vague();
    vague->suiv=nouv;
    nouv->prec=vague;
    vague=vague->suiv;
    vague->suiv=NULL;
    nouv=NULL;
    return vague;
  }
 /**
  * \fn t_wave* supprimer_entite_survivant(t_wave *vague)
  * \brief supprime l'entité au niveau du pointeur passé en paramètres. retourne un pointeur sur l'élément précédent si il ya un élement précédent, sinon le suivant, sinon retourne NULL
  * \param t_wave *vague
  * \return pointeur sur t_wave (sur l'élément précédent, le suivant ou NULL).
  */
t_wave* supprimer_entite_survivant(t_wave *vague){
      if(vague==NULL)return NULL;
      t_wave *temp;
      temp=deb_liste_survivant(vague);
      if(vague==temp){
        if(vague->suiv!=NULL){
          temp=vague;
          vague=vague->suiv;
          free(temp->ent);
          free(temp);
          temp=NULL;
          vague->prec=NULL;
          return vague;
        }
        else {
          free(temp->ent);
          free(temp);
          temp=NULL;
          vague=NULL;
          return NULL;
        }
      }
      else {
        if(vague->prec!=NULL&&vague->suiv!=NULL){
          temp=vague;
          vague=vague->prec;
          vague->suiv=temp->suiv;
          vague->suiv->prec=vague;
          free(temp->ent);
          free(temp);
          temp=NULL;
          return vague;
        }
        else if(vague->prec!=NULL) {
          temp=vague;
          vague=vague->prec;
          vague->suiv=NULL;
          free(temp->ent);
          free(temp);
          temp=NULL;
          return vague;
        }
        else {
          free(temp->ent);
          free(temp);
          vague=NULL;
          return NULL;
        }
      }
    }
  /**
   * \fn  t_wave* vider_liste_survivant(t_wave *vague)
   * \brief fonction qui sert à vider la liste.
   * \param t_wave *vague
   * \return pointeur sur t_wave
   */
t_wave* vider_liste_survivant(t_wave *vague){
       vague=fin_liste_survivant(vague);
       while(vague!=NULL){
         vague=supprimer_entite_survivant(vague);
       }
       return NULL;
   }
   /**
    * \fn t_wave* charger_niveau(char *nom, t_wave *vagues)
    * \brief fonction qui sert à charger un niveau en mode survivant, en allant chercher dans un fichier dont le nom est passé en paramètres les informations du niveau (pour chaque vagues le nombres d'entités, leur types, leur pv, le temps entre les vagues etc..).
    * \param char *nom, t_wave *vagues
    * \return pointeur sur t_wave qui aura été rempli par les informations contenu dans le fichier.
    */
// dans les fichiers level.txt on a les infos suivantes : numero de la vague/type entité/nombre entité/temps avant la prochaine vague(en s)
t_wave* charger_niveau(char *nom, t_wave *vagues){ //charge le niveau à partir d'un fichier txt
//  FILE *fichier=fopen(nom, "r");
//    fclose(fichier);
  int temps=0;
  vagues=creer_vague();
  if(vagues==NULL)return NULL;
    for(int i=0;i<10;i++){
      printf("adresse : %p\n", vagues);
    strcpy(vagues->ent->nom_fichier,"data/entities/mumma/mummy1.png");
    vagues->ent->pv=50;
    vagues->ent->montant=1;
    vagues->ent->x=950;
    vagues->ent->y_barre=450;
    vagues->ent->temps=temps;
    temps+=50;
    printf("%s\npv : %d\nmontant : %d\nx : %d\ntemps : %d\n\n",vagues->ent->nom_fichier, vagues->ent->pv, vagues->ent->montant, vagues->ent->x, vagues->ent->temps);
    if(i<10)vagues=ajouter_entite_survivant(vagues);
  }
  printf("adresse en sortie de for : %p\n", vagues);
  printf("%s\npv : %d\nmontant : %d\nx : %d\ntemps : %d\n\n",vagues->ent->nom_fichier, vagues->ent->pv, vagues->ent->montant, vagues->ent->x, vagues->ent->temps);
  vagues=deb_liste_survivant(vagues);
  vagues=suivant_entite_survivant(vagues);
  printf("adresse : %p\n", vagues);
  vagues=suivant_entite_survivant(vagues);
  printf("adresse : %p\n", vagues);
  vagues=suivant_entite_survivant(vagues);
  printf("adresse : %p\n", vagues);
  vagues=precedent_entite_survivant(vagues);
  printf("adresse : %p\n", vagues);
  vagues=precedent_entite_survivant(vagues);
  printf("adresse : %p\n", vagues);
  vagues=precedent_entite_survivant(vagues);
  printf("adresse : %p\n", vagues);
  vagues=deb_liste_survivant(vagues);
/*  int i=0;
  while(!feof(fichier)){
    fscanf(fichier, "%d/%d/%d/%d", &vagues[i].vague, &vagues[i].type_entite, &vagues[i].nb, &vagues[i].temps);
    i++;
  }
  for(i=0;i<V;i++){
  printf("%d/%d/%d/%d\n", vagues[i].vague, vagues[i].type_entite, vagues[i].nb, vagues[i].temps);
} */
  return vagues;
}

t_wave* creer_entite_joueur(t_wave *vagues){
  //FILE *fichier=fopen(nom, "r");
  //char nom_fichier[60];
  vagues=creer_vague();
    strcpy(vagues->ent->nom_fichier,"data/entities/voisn/voisn1.png");
    vagues->ent->pv=50;
    vagues->ent->montant=1;
    vagues->ent->x=200;
    vagues->ent->y_barre=450;
    vagues->ent->temps=30;
    vagues=ajouter_entite_survivant(vagues);
    strcpy(vagues->ent->nom_fichier,"data/entities/voisin/voisin1.png");
    vagues->ent->pv=50;
    vagues->ent->montant=1;
    vagues->ent->x=200;
    vagues->ent->y_barre=450;
    vagues->ent->temps=60;
    return vagues;
}
void afficher_status_entite(t_wave *vagues){
  printf("%s\npv : %d\nmontant : %d\nx : %d\ntemps : %d\n\n",vagues->ent->nom_fichier, vagues->ent->pv, vagues->ent->montant, vagues->ent->x, vagues->ent->temps);
}
/**
 * \fn void met_a_jour_images(t_wave *vague, SDL_Renderer *rendu)
 * \brief fonction qui sert à mettre automatiquement les images de l'entité à jour. pour qu'elle continue son animation soit en incrémentant le chiffre correspondant au numéro de l'image soit en le décrémentant et en changeant l'indice d'animation à chaque fois que nécéssaire
 * \param t_wave *vague, SDL_Renderer *rendu
 * \return rien
 */
void met_a_jour_images(t_wave *vagues, SDL_Renderer *rendu){
  if(vagues!=NULL){
    if(vagues->ent->nom_fichier[25]<57&&vagues->ent->montant){
      vagues->ent->nom_fichier[25]++;
      if(!fichier_existe(vagues->ent->nom_fichier))vagues->ent->nom_fichier[25]--;
    }
    else if(vagues->ent->nom_fichier[25]==57&&vagues->ent->montant){
      vagues->ent->nom_fichier[25]--;
      if(!fichier_existe(vagues->ent->nom_fichier))vagues->ent->nom_fichier[25]++;
      vagues->ent->montant=0;
    }
    else if(vagues->ent->nom_fichier[25]>49&&!vagues->ent->montant){
      vagues->ent->nom_fichier[25]--;
      if(!fichier_existe(vagues->ent->nom_fichier))vagues->ent->nom_fichier[25]++;
    }
    else if(vagues->ent->nom_fichier[25]==49&&!vagues->ent->montant){
      vagues->ent->nom_fichier[25]++;
      if(!fichier_existe(vagues->ent->nom_fichier))vagues->ent->nom_fichier[25]--;
      vagues->ent->montant=1;
    }
  }
}

int info_vagues(t_wave*vague, int nb, int deb, int fin, int vide){ //fonction donnant des info sur les vagues
  if(nb){
    int nb_entite=0;
    vague=deb_liste_survivant(vague);
    while(vague!=NULL&&vague->suiv!=NULL){
      nb_entite++;
      vague=suivant_entite_survivant(vague);
    }
    return nb_entite;
  }
  else if(deb){
    t_wave*temp=vague;
    vague=deb_liste_survivant(vague);
    if(vague==temp){
      temp=NULL;
      return 1;
    }
    else{
      temp=NULL;
      return 0;
    }
  }
  else if(fin){
    t_wave*temp=vague;
    vague=fin_liste_survivant(vague);
    if(vague==temp){
      temp=NULL;
      return 1;
    }
    else{
      temp=NULL;
      return 0;
    }
  }
  else if(vide){
    return(vague==NULL);
  }
}
/**
 * \fn void deroulement_vagues_ennemies(t_wave *vagues, SDL_Renderer *rendu);
 * \brief fonction qui sert à mettre automatiquement les images de l'entité à jour. pour qu'elle continue son animation soit en incrémentant le chiffre correspondant au numéro de l'image soit en le décrémentant et en changeant l'indice d'animation à chaque fois que nécéssaire
 * \param t_wave *vague, SDL_Renderer *rendu
 * \return rien
 */
void deroulement_vagues_ennemies(t_wave *vagues, SDL_Renderer *rendu){
  int code_contour_barre_vie[4]={0,0,0,255};
  int code_interieur_barre_vie[4]={255,165,0,255};
   vagues=deb_liste_survivant(vagues);
   if(vagues!=NULL){
   while(vagues->suiv!=NULL){
      if(!vagues->ent->temps&&vagues->ent->pv>0){
       charger_image(vagues->ent->nom_fichier, rendu, vagues->ent->x,y_entity,0);
       met_a_jour_images(vagues, rendu);
       dessiner_rectangle_vide(rendu, code_contour_barre_vie, vagues->ent->x+40, vagues->ent->y_barre, 8, 52, 0); /*met à jour la barre de vie*/
       dessiner_rectangle_plein(rendu, code_interieur_barre_vie, vagues->ent->x+41, vagues->ent->y_barre+1, 6, vagues->ent->pv, 0);
       vagues->ent->x-=2;
       if(vagues->ent->x<400)vagues->ent->pv--;
      }
      else {
        vagues->ent->temps--;
      }
      vagues=suivant_entite_survivant(vagues);
   }
  }
}

void deroulement_vagues_joueur(t_wave *vagues, SDL_Renderer *rendu){
  int code_contour_barre_vie[4]={0,0,0,255};
  int code_interieur_barre_vie[4]={255,165,0,255};
   vagues=deb_liste_survivant(vagues);
   if(vagues!=NULL){
   while(vagues->suiv!=NULL){
      if(!vagues->ent->temps&&vagues->ent->pv>0){
       charger_image(vagues->ent->nom_fichier, rendu,vagues->ent->x,y_entity,0);
       met_a_jour_images(vagues, rendu);
       dessiner_rectangle_vide(rendu, code_contour_barre_vie, vagues->ent->x+40, vagues->ent->y_barre, 8, 52, 0); /*met à jour la barre de vie*/
       dessiner_rectangle_plein(rendu, code_interieur_barre_vie, vagues->ent->x+41, vagues->ent->y_barre+1, 6, vagues->ent->pv, 0);
       vagues->ent->x+=2;
       if(vagues->ent->x>900)vagues->ent->pv--;
      }
      else {
        vagues->ent->temps--;
      }
      vagues=suivant_entite_survivant(vagues);
   }
  }
}

int fin_partie_survivant(t_wave *vagues, SDL_Renderer *rendu){
    vagues=vider_liste_survivant(vagues);
    return(vagues==NULL);
}

void creer_joueur(joueur *player){
  player=malloc(sizeof(joueur));
  player->nom=malloc(sizeof(char)*100);
  player->pv=500;
  player->argent=1000;
  strcpy(player->nom, "Lazare");
}

void ajouter_voisin(joueur *player, t_wave *vague){
  //if(player!=NULL&&vague!=NULL){
  //  if(player->argent>=100){
      vague=ajouter_entite_survivant(vague);
        strcpy(vague->ent->nom_fichier,"data/entities/voisn/voisn1.png");
        vague->ent->pv=50;
        vague->ent->montant=1;
        vague->ent->x=200;
        vague->ent->y_barre=450;
        vague->ent->temps=30;
  //  }
  //}
}

int etat_partie_survivant(t_wave *vagues, joueur *player){//retourne l'état de la partie (0 si elle est toujours en cours, 1 si le joueur a gagné, -1 si il a perdu)

}

int return_message(){ //message qui lorsqu'on clique sur la croix rouge est affiché pour éviter de tout perdre en pleine partie
  const SDL_MessageBoxButtonData buttons[] = {
      { /* .flags, .buttonid, .text */        0, 0, "NON" },
      { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OUI" },
      { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "ANNULER" },
  };
  const SDL_MessageBoxColorScheme colorScheme = {
      {
          { 255,   0,   0 },
          {   0, 255,   0 },
          { 255, 255,   0 },
          {   0,   0, 255 },
          { 255,   0, 255 }
      }
  };
  const SDL_MessageBoxData messageboxdata = {
      SDL_MESSAGEBOX_INFORMATION, /* .flags */
      NULL, /* .window */
      "Retour au menu", /* .title */
      "Etes-vous sûr de vouloir quitter ?\nLa partie ne sera pas sauvegardée.", /* .message */
      SDL_arraysize(buttons), /* .numbuttons */
      buttons, /* .buttons */
      &colorScheme /* .colorScheme */
  };
  int buttonid;
  if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
      SDL_Log("error displaying message box");
      return 1;
  }
  if (buttonid==1) {
      return -1;
  }else return 0;
}

int demarrer_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event){ //crée un ordinateur avec le nombre de vague liées au niveau.
    t_wave *vague_ennemies=charger_niveau("test.txt", vague_ennemies);
    if(vague_ennemies==NULL)printf("echec lors de la creation de vague\n");
    t_wave *vague_joueur=creer_entite_joueur(vague_joueur);
    //joueur *player=NULL;
  //  creer_joueur(player);
    printf("sortie de la fonction vague_ennemies\n");
    charger_image("data/backgrounds/bg1survie.png", rendu, 0,0,1);
    int pause=0;
    while(1){
      while(SDL_PollEvent(event)){ //on réécoute les évènements mais avec un pointeur sur event car en SDL on ne peut pas faire plusieurs listener d'évènements.
    //  if(etat_partie_survivant(vagues, &player)==1)return 1;//on verifie à chaque tour de boucle l'état de la partie
    //  if(etat_partie_survivant(vagues, &player)==-1)return 0;
      if(event->type==SDL_QUIT){ //lorsque l'utilisateur appuie sur la croix rouge de la fenetre
          if(quit_message()==-1){
            if(!fin_partie_survivant(vague_ennemies, rendu))printf("erreur libération de mémoire échouée\n");
            return -1; //on retourne -1
          }
      }
      if(event->window.event==SDL_WINDOWEVENT_RESIZED){
        SDL_SetWindowSize(window, 1250, 694);
      }
      if((event->motion.x>=620&event->motion.x<=670)&&(event->motion.y>=10&&event->motion.y<=50)){
          if(event->type==SDL_MOUSEBUTTONDOWN){
            if(pause)pause=0;
            else pause=1;
             afficher_survivant(vague_ennemies, rendu, pause);
          }
      }

        if((event->motion.x>=220&&event->motion.x<=280)&&(event->motion.y>=10&&event->motion.y<=60)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
        charger_image("data/inventaire/carreover.png", rendu, 220,10,1);
          if(event->type==SDL_MOUSEBUTTONDOWN);/*ajouter_voisin(player, vague_joueur);*/
        }
        else if((event->motion.x>=290&&event->motion.x<=350)&&(event->motion.y>=10&&event->motion.y<=60)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
        charger_image("data/inventaire/carreover.png", rendu,290,10,1);
        }
        else if((event->motion.x>=360&&event->motion.x<=420)&&(event->motion.y>=10&&event->motion.y<=60)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
        charger_image("data/inventaire/carreover.png", rendu,360,10,1);
        }
        else if((event->motion.x>=430&&event->motion.x<=500)&&(event->motion.y>=10&&event->motion.y<=60)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
        charger_image("data/inventaire/carreover.png", rendu,430,10,1);
        }
        else if((event->motion.x>=0&&event->motion.x<=100)&&(event->motion.y>=0&&event->motion.y<=30)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
        charger_image("data/inventaire/backover.png", rendu,0,10,1);
          if(event->type==SDL_MOUSEBUTTONDOWN){
            if(return_message()==-1){
              if(!fin_partie_survivant(vague_ennemies, rendu))printf("erreur libération de mémoire échouée\n");
                return 0;
            }
          }
        else{
          charger_image("data/inventaire/carre1.png", rendu, 220, 10, 0);
          charger_image("data/inventaire/carre.png", rendu, 290, 10, 0);
          charger_image("data/inventaire/carre.png", rendu, 360, 10, 0);
          charger_image("data/inventaire/carre.png", rendu, 430, 10, 0);
          charger_image("data/inventaire/back.png", rendu, 0, 10, 0);
        }
      }
   }
   if(!pause){
       charger_image("data/backgrounds/bg1survie.png", rendu,0,0,0);
       charger_image("data/inventaire/survivant.png", rendu, 740, 10, 0);
       charger_image("data/inventaire/piece1.png", rendu, 20, 40, 0);
       charger_image("data/inventaire/retoursurv.png", rendu, 60, 10, 0);
       charger_image("data/inventaire/carre1.png", rendu, 220, 10, 0);
       charger_image("data/inventaire/carre.png", rendu, 290, 10, 0);
       charger_image("data/inventaire/carre.png", rendu, 360, 10, 0);
       charger_image("data/inventaire/carre.png", rendu, 430, 10, 0);
       charger_image("data/inventaire/back.png", rendu, 0, 10, 0);
     }
   afficher_survivant(vague_ennemies, rendu,pause);
   if(!pause)deroulement_vagues_ennemies(vague_ennemies, rendu);
   if(!pause)deroulement_vagues_joueur(vague_joueur, rendu);
   SDL_RenderPresent(rendu);
 }
}
