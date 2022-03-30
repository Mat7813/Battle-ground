/**
 * \file interface.c
 * \brief Contient toutes les fonctions utiles à l'interface graphique principale du jeu (gestion des menus, fonction de chargement des images etc...)
 * \author Lazare Maclouf
 * \version 1
 * \date 22/01/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "audio.h"
#include "jeu.h"
#include "structures.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

//pthread_t audio; /*thread pour la gestion de l'audio*/

#define menu_x 350
/**
 * \fn void convert_argent(joueur *p)
 * \brief Fonction qui sert à savoir quels chiffres composent le budget du joueur pour les afficher à l'écran (pour 1000 par exemple on aura 1.png, 0.png, 0.png, 0.png)
 * \param joueur *p
 */
void convert_argent(joueur *p){
  if(p!=NULL){
      for(int j=0;j<15;j++){
        for(int f=0;f<22;f++)p->argent_img[j][f]=0;
      }
    int nb=p->argent;
    int nb2=nb;
    int puiss=1;
    int i;
    for(i=0;nb2>10;i++){
      nb=nb2;
    for(puiss=1;nb>=10;){
      nb/=10;
      puiss*=10;
    }
    switch(nb){
    case 0:strcpy(p->argent_img[i], "data/inventaire/0.png");break;
    case 1:strcpy(p->argent_img[i], "data/inventaire/1.png");break;
    case 2:strcpy(p->argent_img[i], "data/inventaire/2.png");break;
    case 3:strcpy(p->argent_img[i], "data/inventaire/3.png");break;
    case 4:strcpy(p->argent_img[i], "data/inventaire/4.png");break;
    case 5:strcpy(p->argent_img[i], "data/inventaire/5.png");break;
    case 6:strcpy(p->argent_img[i], "data/inventaire/6.png");break;
    case 7:strcpy(p->argent_img[i], "data/inventaire/7.png");break;
    case 8:strcpy(p->argent_img[i], "data/inventaire/8.png");break;
    case 9:strcpy(p->argent_img[i], "data/inventaire/9.png");break;
    default:break;
    }
    nb*=puiss;
    nb2-=nb;
    }
    if(nb2==0){
      if(nb>=10){
        while(nb>=10){
          strcpy(p->argent_img[i], "data/inventaire/0.png");
          i++;
          nb/=10;
        }
        return;
      }
    }
    switch(nb2){
    case 0:strcpy(p->argent_img[i], "data/inventaire/0.png");break;
    case 1:strcpy(p->argent_img[i], "data/inventaire/1.png");break;
    case 2:strcpy(p->argent_img[i], "data/inventaire/2.png");break;
    case 3:strcpy(p->argent_img[i], "data/inventaire/3.png");break;
    case 4:strcpy(p->argent_img[i], "data/inventaire/4.png");break;
    case 5:strcpy(p->argent_img[i], "data/inventaire/5.png");break;
    case 6:strcpy(p->argent_img[i], "data/inventaire/6.png");break;
    case 7:strcpy(p->argent_img[i], "data/inventaire/7.png");break;
    case 8:strcpy(p->argent_img[i], "data/inventaire/8.png");break;
    case 9:strcpy(p->argent_img[i], "data/inventaire/9.png");break;
    default:break;
    }
  }
}
/**
 * \fn int quit_message()
 * \brief affiche un message qui demande si on veut quitter la partie
 * \param void
 * \return -1 si l'utilisateur clique sur oui, 1 sinon
 */
int quit_message(void){
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
      "Quitter le jeu", /* .title */
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
/**
 * \fn void dessiner_rectangle_vide(SDL_Renderer *rendu, int code_couleur[4], int x, int y, int h, int w, int mode)
 * \brief dessine un rectangle vide
 * \param SDL_Renderer *rendu, int code_couleur[4], int x, int y, int h, int w, int mode
 */
void dessiner_rectangle_vide(SDL_Renderer *rendu, int code_couleur[4], int x, int y, int h, int w, int mode){
  SDL_SetRenderDrawColor(rendu, code_couleur[0], code_couleur[1], code_couleur[2], code_couleur[3]);
  SDL_Rect rect;
  rect.x=x;
  rect.y=y;
  rect.h=h;
  rect.w=w;
  SDL_RenderDrawRect(rendu, &rect);
  if(mode)SDL_RenderPresent(rendu); // si le mode choisi est 1 on présente le rendu à l'écran
}
/**
 * \fn void dessiner_rectangle_plein(SDL_Renderer *rendu, int code_couleur[4], int x, int y, int h, int w, int mode)
 * \brief dessine un rectangle plein
 * \param SDL_Renderer *rendu, int code_couleur[4], int x, int y, int h, int w, int mode
 */
void dessiner_rectangle_plein(SDL_Renderer *rendu, int code_couleur[4], int x, int y, int h, int w, int mode){
  SDL_SetRenderDrawColor(rendu, code_couleur[0], code_couleur[1], code_couleur[2], code_couleur[3]);
  SDL_Rect rect;
  /*affectation des valeurs entrées en paramètre pour les dimensions du rectangle*/
  rect.x=x;
  rect.y=y;
  rect.h=h;
  rect.w=w;
  /*on dessine le rectangle sur le rendu*/
  SDL_RenderFillRect(rendu, &rect);
  /*on affiche le rendu à l'écran si le mode choisi est égal à 1*/
  if(mode)SDL_RenderPresent(rendu); // si le mode choisi est 1 on présente le rendu à l'écran
}
/**
 * \fn int charger_image(char *nom, SDL_Renderer *rendu, int x, int y, int option)
 * \brief  sert à charger une image avec tous les formats (grâce à SDL_image) sur le rendu et à présenter le rendu sur la fenetre (le format géré par défaut par la SDL est BMP)
 * \param char *nom, SDL_Renderer *rendu, int x, int y, int option
 * \return -1 si un problème est survenu rien sinon
 */
int charger_image(char *nom, SDL_Renderer *rendu, int x, int y, int option){ //cette fonction sert à charger une image avec tous les formats (grâce à SDL_image) sur le rendu et à présenter le rendu sur la fenetre (le format géré par défaut par la SDL est BMP)
  SDL_Surface *image = NULL; //pointeur pour une surface qu'on pourra par la suite charger sur le rendu
  SDL_Texture *texture = NULL; //pointeur sur la texture qu'on va manipuler avec le rendu
  SDL_Rect rect; //un rectangle sur lequel on pourra coller la surface
  rect.x=x, rect.y=y;
  image = IMG_Load(nom); //on commence par charger dans le pointeur sur la surface l'image BMP
  texture = SDL_CreateTextureFromSurface(rendu, image); //on crée une texture à partir du rendu et de l'image
  if(image==NULL)return -1; //si l'image n'existe pas on retourne -1
  SDL_FreeSurface(image); //on libère dans tous les cas la surface car elle a été copiée dans la texture.
  if(texture==NULL)return -1; //si on arrive pas à créer de texture on retourne -1 aussi
  if(SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h)!=0)return -1; //on place la texture dans le rectangle qu'on a reçu en paramètre. si on y arrive pas on retourne -1
  if(SDL_RenderCopy(rendu, texture, NULL, &rect)!=0)return -1; //on copie la texture dans le rendu
  if(option==1)SDL_RenderPresent(rendu); //on a l'option de présentation du rendu ou non pour éviter les beug d'affichage on superpose tout avant d'afficher
  SDL_DestroyTexture(texture);
  texture=NULL, image=NULL;
  return 0;
}
/**
 * \fn int charger_partie_image(char *nom, SDL_Renderer *rendu, int x, int y, int w, int h, int w_image, int h_image, int x_image, int y_image, int option)
 * \brief  sert à charger un morceau d'une image (la taille de la figure à rogner, sa position et autres passés en paramètre) avec tous les formats (grâce à SDL_image) sur le rendu et à présenter le rendu sur la fenetre (le format géré par défaut par la SDL est BMP)
 * \param char *nom, SDL_Renderer *rendu, int x, int y, int w, int h, int w_image, int h_image, int x_image, int y_image, int option
 * \return -1 si un problème est survenu rien sinon
 */
int charger_partie_image(char *nom, SDL_Renderer *rendu, int x, int y, int w, int h, int w_image, int h_image, int x_image, int y_image, int option){ //cette fonction sert à charger une image avec tous les formats (grâce à SDL_image) sur le rendu et à présenter le rendu sur la fenetre (le format géré par défaut par la SDL est BMP)
  SDL_Surface *image = NULL; //pointeur pour une surface qu'on pourra par la suite charger sur le rendu
  SDL_Texture *texture = NULL; //pointeur sur la texture qu'on va manipuler avec le rendu
  SDL_Rect rect; //un rectangle sur lequel on pourra coller la surface
  rect.x=x, rect.y=y, rect.w=w, rect.h=h; //coordonnées et tailles de l'image à afficher
  SDL_Rect taille;
  taille.w=w_image, taille.h=h_image, taille.x=x_image, taille.y=y_image; //curseur de sélection pour l'image à afficher
  image = IMG_Load(nom); //on commence par charger dans le pointeur sur la surface l'image BMP
  texture = SDL_CreateTextureFromSurface(rendu, image); //on crée une texture à partir du rendu et de l'image
  if(image==NULL)return -1; //si l'image n'existe pas on retourne -1
  SDL_FreeSurface(image); //on libère dans tous les cas la surface car elle a été copiée dans la texture.
  if(texture==NULL)return -1; //si on arrive pas à créer de texture on retourne -1 aussi
  if(SDL_QueryTexture(texture, NULL, NULL, NULL, NULL)!=0)return -1; //on place la texture dans le rectangle qu'on a reçu en paramètre. si on y arrive pas on retourne -1
  if(SDL_RenderCopy(rendu, texture, &taille, &rect)!=0)return -1; //on copie la texture dans le rendu
  if(option==1)SDL_RenderPresent(rendu); //on a l'option de présentation du rendu ou non pour éviter les beug d'affichage on superpose tout avant d'afficher
  SDL_DestroyTexture(texture);
  return 0;
}
/**
 * \fn void demarrage(SDL_Renderer *rendu)
 * \brief Fonction servant d'introduction au jeu en faisant une animation à l'écran
 * \param SDL_Renderer *rendu
 */
void demarrage(SDL_Renderer *rendu){
  for(int i=0;i<20;i++){
  SDL_Delay(50);
  charger_image("data/backgrounds/launcher.bmp", rendu,350,200,1);
  SDL_Delay(50);
  SDL_RenderClear(rendu);
  SDL_RenderPresent(rendu);
  charger_image("data/backgrounds/launcherover.bmp", rendu,350,200,1);
  }
  SDL_RenderClear(rendu);
  SDL_RenderPresent(rendu);
}
/**
 * \fn int menu_jouer_difficulte(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, int mode)
 * \brief fonction servant à sélectionner la difficulté pour une partie en mode classique
 * \param SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, int mode
 * \return -1 ou 0
 */
int menu_jouer_difficulte(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, int mode){ //mode correspond au mode de jeu (1 pour classique et 2 pour survie)
  SDL_RenderClear(rendu);
  charger_image("data/backgrounds/bgmenu1.bmp", rendu,0,0,1);
  SDL_bool jouer=SDL_TRUE;
  while(jouer){

    while(SDL_PollEvent(event)){ //on réécoute les évènements mais avec un pointeur sur event car en SDL on ne peut pas faire plusieurs listener d'évènements.
    if(event->type==SDL_QUIT){ //lorsque l'utilisateur appuie sur la croix rouge de la fenetre
        return -1; //on retourne -1
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=520)&&(event->motion.y>=150&&event->motion.y<=200)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/facileover.png", rendu,menu_x,150, 1);
      if(mode==1)if(jeu_classique(window, rendu, event, 1)==-1)return -1; //le 1 correspond au niveau de difficile facile, 2 à moyen et 3 à difficile
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=220&&event->motion.y<=270)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/moyenover.png", rendu,menu_x,220, 1);
      if(mode==1)if(jeu_classique(window, rendu, event, 2)==-1)return -1;
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=290&&event->motion.y<=340)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/difficileover.png", rendu,menu_x,290, 1);
      if(mode==1)if(jeu_classique(window, rendu, event, 3)==-1)return -1;
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=360&&event->motion.y<=410)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/retourover.png", rendu,menu_x,360,1);
      if(event->type==SDL_MOUSEBUTTONDOWN){
        charger_image("data/backgrounds/bgmenu1.bmp", rendu,0,0,1);
        jouer=SDL_FALSE;
      }
    }
    else {
      charger_image("data/menu/jouer/facile.png", rendu,menu_x,150,1);
      charger_image("data/menu/jouer/moyen.png", rendu,menu_x,220,1);
      charger_image("data/menu/jouer/difficile.png", rendu,menu_x,290,1);
      charger_image("data/menu/jouer/retour.png", rendu,menu_x,360,1);
    }
  }
}
return 0;
}
/**
 * \fn int select_multi(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event)
 * \brief fonction servant à afficher la sélection de l'hote ou du client.
 * \param SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event
 * \return -1 ou 0
 */
int select_multi(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event){
  SDL_RenderClear(rendu);
  charger_image("data/backgrounds/bgmenu1.bmp", rendu,0,0,1);
  SDL_bool jouer=SDL_TRUE;
  while(jouer){
    while(SDL_PollEvent(event)){ //on réécoute les évènements mais avec un pointeur sur event car en SDL on ne peut pas faire plusieurs listener d'évènements.
    if(event->type==SDL_QUIT){ //lorsque l'utilisateur appuie sur la croix rouge de la fenetre
        return -1; //on retourne -1
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=200&&event->motion.y<=260)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/hoteover.png", rendu,menu_x,200,1);
        if(event->type==SDL_MOUSEBUTTONDOWN){
           if(jeu_survivant(window, rendu,event)==-1)return -1; //si la fonction retourne -1 c'est que l'utilisateur a appuyé sur la croix rouge. on retourne donc -1
           else charger_image("data/backgrounds/bgmenu1.bmp", rendu,0,0,1);
        }
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=285&&event->motion.y<=345)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/invitover.png", rendu,menu_x,285,1);
        if(event->type==SDL_MOUSEBUTTONDOWN){
           if(jeu_survivant(window, rendu,event)==-1)return -1; //si la fonction retourne -1 c'est que l'utilisateur a appuyé sur la croix rouge. on retourne donc -1
           else charger_image("data/backgrounds/bgmenu1.bmp", rendu,0,0,1);
        }
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=375&&event->motion.y<=425)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/retourover.png", rendu,menu_x,375,1);
      if(event->type==SDL_MOUSEBUTTONDOWN){
        charger_image("data/backgrounds/bgmenu1.bmp", rendu,0,0,1); //on recharge le décors pour effacer les boutons du menu actuel
        jouer=SDL_FALSE;
      }
    }
    else {
      charger_image("data/menu/hote.png", rendu,menu_x,200,1);
      charger_image("data/menu/invit.png", rendu,menu_x,285,1);
      charger_image("data/menu/jouer/retour.png", rendu,menu_x,375,1);
    }
  }
}
return 0;
}


/**
 * \fn int sous_menu_jouer(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event)
 * \brief fonction servant à afficher les options de jeu et à charger les autres fonctions en conséquence (mode classique, mode suvivant ou mode multi-joueur).
 * \param SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event
 * \return -1 ou 0
 */
int sous_menu_jouer(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event){
  SDL_RenderClear(rendu);
  charger_image("data/backgrounds/bgmenu1.bmp", rendu,0,0,1);
  SDL_bool jouer=SDL_TRUE;
  while(jouer){
    while(SDL_PollEvent(event)){ //on réécoute les évènements mais avec un pointeur sur event car en SDL on ne peut pas faire plusieurs listener d'évènements.
    if(event->type==SDL_QUIT){ //lorsque l'utilisateur appuie sur la croix rouge de la fenetre
        return -1; //on retourne -1
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=150&&event->motion.y<=200)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/survieover.png", rendu,menu_x,150,1);
        if(event->type==SDL_MOUSEBUTTONDOWN){
           if(jeu_survivant(window, rendu,event)==-1)return -1; //si la fonction retourne -1 c'est que l'utilisateur a appuyé sur la croix rouge. on retourne donc -1
           else charger_image("data/backgrounds/bgmenu1.bmp", rendu,0,0,1);
        }
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=225&&event->motion.y<=275)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/classiqueover.png", rendu,menu_x,225,1);
      if(event->type==SDL_MOUSEBUTTONDOWN){
         if(menu_jouer_difficulte(window, rendu, event, 1)==-1)return -1;
      }
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=300&&event->motion.y<=350)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/multiover.png", rendu,menu_x,300,1);
      if(event->type==SDL_MOUSEBUTTONDOWN){
         if(select_multi(window, rendu, event)==-1)return -1;//changer menu_jouer et rediriger vers page réseau avec sélection host client
      }
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=375&&event->motion.y<=425)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/retourover.png", rendu,menu_x,375,1);
      if(event->type==SDL_MOUSEBUTTONDOWN){
        charger_image("data/backgrounds/bgmenu1.bmp", rendu,0,0,1); //on recharge le décors pour effacer les boutons du menu actuel
        jouer=SDL_FALSE;
      }
    }
    else {
      charger_image("data/menu/jouer/survie.png", rendu,menu_x,150,1);
      charger_image("data/menu/jouer/classique.png", rendu,menu_x,225,1);
      charger_image("data/menu/jouer/multi.png", rendu,menu_x,300,1);
      charger_image("data/menu/jouer/retour.png", rendu,menu_x,375,1);
    }
  }
}
return 0;
}

/**
 * \fn void menu(SDL_Window *window, SDL_Renderer *rendu)
 * \brief fonction servant à afficher le menu principal du jeu avec ses différentes options (jouer, paramètres, quitter) et à agir en fonction du choix de l'utilisateur.
 * \param SDL_Window *window, SDL_Renderer *rendu
 */
void menu(SDL_Window *window, SDL_Renderer *rendu){
    SDL_RenderClear(rendu); //on nettoie complètement le rendu à chque fois pour ne pas superposer tout
    charger_image("data/backgrounds/bgmenu1.png", rendu,0,0,1); //on charge le fond sur lequel on va charger le menu
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)printf("erreur de chargement video"); //on charge toutes les fonctionnalités de la sdl
    SDL_Event event; //on crée une variable de type event pour récupérer les actions de l'utilisateur
    SDL_bool programme = SDL_TRUE; //variable permet de garder l'écouteur dévènement actif
    while(programme){
      while(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT){ //lorsque l'utilisateur appuie sur la croix rouge de la fenetre
            programme = SDL_FALSE;
        }
          if((event.motion.x>=menu_x&&event.motion.x<=530)&&(event.motion.y>=150&&event.motion.y<=200)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
            charger_image("data/menu/jouerover.png", rendu,menu_x,150,1);
            if(event.type==SDL_MOUSEBUTTONDOWN){
              if(sous_menu_jouer(window, rendu, &event)==-1)programme = SDL_FALSE; //on quitte si la fonction retourne -1
            }
          }
          else if((event.motion.x>=menu_x&&event.motion.x<=730)&&(event.motion.y>=250&&event.motion.y<=300)){
            charger_image("data/menu/parametreover.png", rendu, menu_x,250,1);
              if(event.type==SDL_MOUSEBUTTONDOWN){
                if(sous_menu_jouer(window, rendu, &event)==-1)programme = SDL_FALSE; //on quitte si la fonction retourne -1
            }
          }
          else if((event.motion.x>=menu_x&&event.motion.x<=530)&&(event.motion.y>=350&&event.motion.y<=400)){
             charger_image("data/menu/quitterover.png", rendu,menu_x,350,1);
             if(event.type==SDL_MOUSEBUTTONDOWN){
               programme = SDL_FALSE;
             }
           }
           else if (event.window.event == SDL_WINDOWEVENT_RESIZED){ //pour éviter que tout soit dérangé lorsu'on redimmensionne la fenetre on recharge le décors principal et on redimensionne la fentre de la meme taille qu'au début (dans le menu principal l'utilisateur ne peut pas changer la taille de la fenetre)
             SDL_SetWindowSize(window, 1000, 564);
             charger_image("data/backgrounds/bgmenu1.png", rendu,0,0,1);
           }
        else { //lorsque l'utilisateur ne fait rien on recharge les boutons par défaut
          charger_image("data/menu/jouer.png", rendu,menu_x,150,1);
          charger_image("data/menu/parametres.png", rendu,menu_x,250,1);
          charger_image("data/menu/quitter.png", rendu,menu_x,350,1);
        }
      }
    }
}

/**
 * \fn int initialise_jeu()
 * \brief fonction principale du jeu. Elle est chargée de la Création et du lancement de la fenêtre du jeu, du rendu ainsi que de l'appel des autres fonctions pour jouer. Enfin, elle s'occupe de détruire le rendu, la fenêtre et de quitter la sdl une fois sorti des fonction de jeu (juste avant de quitter le programme)
 * \param void
 * \return 0
 */
int initialise_jeu(){ //fonction servant à initialiser completement le jeu en appelant les fonctions principales d'affichages qui elles-mêmes appeleront toutes les autres sous fonctions pour le jeu
  SDL_Window *window = NULL; //pointeur pour la fentre (ici on travaille uniquement avec des pointeurs pour que toutes les variables soient accessibles partout dans le code et modifiables par d'autres fonctions facilement)
  SDL_Renderer *rendu = NULL; //pointeur rendu
  window = SDL_CreateWindow("Battle Ground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 564, SDL_WINDOW_RESIZABLE); //on crée une fenetre de type "window_resizable" car par la suite on pourra agrandir la fenêtre
  rendu = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); //on crée le rendu
  demarrage(rendu); //fonction qui sert simplement à afficher un petit logo qui clignote lorsu'on lance le jeu
  //int th1=pthread_create(&audio, NULL, audio_initialise, NULL);
  //pthread_detach(audio);
  menu(window, rendu); //fonction principale qui charge le menu. en parametre on passe tous les pointeurs qu'on a créé dans la fonction.
 // pthread_cancel(audio);
  SDL_DestroyRenderer(rendu); //lorsque l'utilisateur quitte le jeu on détruit le rendu et la fenetre
  SDL_DestroyWindow(window);
  SDL_Quit(); //enfin on quitte la SDL.
  return 0;
}
//gcc test.c -o test -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
