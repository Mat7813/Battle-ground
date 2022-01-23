/**
 * \file interface.c
 * \brief Contient toutes les fonctions utiles à l'interface graphique principale du jeu (gestion des menus, fonction de chargement des images etc...)
 * \author Lazare Maclouf
 * \version 1
 * \date 22/01/2022
 */
#include "jeu.h"
#include "animations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define menu_x 350

/**
 * \fn int charger_image(char *nom, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int x, int y)
 * \brief  sert à charger une image avec tous les formats (grâce à SDL_image) sur le rendu et à présenter le rendu sur la fenetre (le format géré par défaut par la SDL est BMP)
 * \param char *nom, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int x, int y
 * \return -1 si un problème est survenu rien sinon
 */
int charger_image(char *nom, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int x, int y){ //cette fonction sert à charger une image avec tous les formats (grâce à SDL_image) sur le rendu et à présenter le rendu sur la fenetre (le format géré par défaut par la SDL est BMP)
  rect->x=x, rect->y=y;
  image = IMG_Load(nom); //on commence par charger dans le pointeur sur la surface l'image BMP
  texture = SDL_CreateTextureFromSurface(rendu, image); //on crée une texture à partir du rendu et de l'image
  if(image==NULL)return -1; //si l'image n'existe pas on retourne -1
  SDL_FreeSurface(image); //on libère dans tous les cas la surface car elle a été copiée dans la texture.
  if(texture==NULL)return -1; //si on arrive pas à créer de texture on retourne -1 aussi
  if(SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h)!=0)return -1; //on place la texture dans le rectangle qu'on a reçu en paramètre. si on y arrive pas on retourne -1
  if(SDL_RenderCopy(rendu, texture, NULL, rect)!=0)return -1; //on copie la texture dans le rendu
  SDL_RenderPresent(rendu); //enfin on affiche le rendu sur l'écran
}
/**
 * \fn void dessiner_rectangle_vide(SDL_Renderer *rendu, int code_couleur[4], int x, int y, int h, int w, int mode)
 * \brief dessine un rectangle vide
 * \param SDL_Renderer *rendu, int code_couleur[4], int x, int y, int h, int w, int mode
 * \return rien
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
 * \return rien
 */
int dessiner_rectangle_plein(SDL_Renderer *rendu, int code_couleur[4], int x, int y, int h, int w, int mode){
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
 * \fn int charger_image_option(char *nom, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int x, int y, int option)
 * \brief  sert à charger une image avec tous les formats (grâce à SDL_image) sur le rendu et à présenter le rendu sur la fenetre (le format géré par défaut par la SDL est BMP)
 * \param char *nom, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int x, int y
 * \return -1 si un problème est survenu rien sinon
 */
int charger_image_option(char *nom, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int x, int y, int option){ //cette fonction sert à charger une image avec tous les formats (grâce à SDL_image) sur le rendu et à présenter le rendu sur la fenetre (le format géré par défaut par la SDL est BMP)
  rect->x=x, rect->y=y;
  image = IMG_Load(nom); //on commence par charger dans le pointeur sur la surface l'image BMP
  texture = SDL_CreateTextureFromSurface(rendu, image); //on crée une texture à partir du rendu et de l'image
  if(image==NULL)return -1; //si l'image n'existe pas on retourne -1
  SDL_FreeSurface(image); //on libère dans tous les cas la surface car elle a été copiée dans la texture.
  if(texture==NULL)return -1; //si on arrive pas à créer de texture on retourne -1 aussi
  if(SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h)!=0)return -1; //on place la texture dans le rectangle qu'on a reçu en paramètre. si on y arrive pas on retourne -1
  if(SDL_RenderCopy(rendu, texture, NULL, rect)!=0)return -1; //on copie la texture dans le rendu
  if(option==1)SDL_RenderPresent(rendu); //on a l'option de présentation du rendu ou non pour éviter les beug d'affichage on superpose tout avant d'afficher
}
/**
 * \fn int charger_image_option(char *nom, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int x, int y, int option)
 * \brief  sert à charger une image avec tous les formats (grâce à SDL_image) sur le rendu et à présenter le rendu sur la fenetre (le format géré par défaut par la SDL est BMP)
 * \param char *nom, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int x, int y
 * \return -1 si un problème est survenu rien sinon
 */
void demarrage(SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect){
  for(int i=0;i<20;i++){
  SDL_Delay(50);
  charger_image("data/backgrounds/launcher.bmp", rendu, image, texture, rect,350,200);
  SDL_Delay(50);
  SDL_RenderClear(rendu);
  SDL_RenderPresent(rendu);
  charger_image("data/backgrounds/launcherover.bmp", rendu, image, texture, rect,350,200);
  }
  SDL_RenderClear(rendu);
  SDL_RenderPresent(rendu);
}

int menu_jouer_difficulte(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event, int mode){ //mode correspond au mode de jeu (1 pour classique et 2 pour survie)
  SDL_RenderClear(rendu);
  charger_image("data/backgrounds/bgmenu1.bmp", rendu, image, texture, rect,0,0);
  SDL_bool jouer=SDL_TRUE;
  while(jouer){
    while(SDL_PollEvent(event)){ //on réécoute les évènements mais avec un pointeur sur event car en SDL on ne peut pas faire plusieurs listener d'évènements.
    if(event->type==SDL_QUIT){ //lorsque l'utilisateur appuie sur la croix rouge de la fenetre
        return -1; //on retourne -1
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=520)&&(event->motion.y>=150&&event->motion.y<=200)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/facileover.png", rendu, image, texture, rect,menu_x,150);
      if(mode==1)if(jeu_classique(window, rendu, image, texture, rect, event, 1)==-1)return -1; //le 1 correspond au niveau de difficile facile, 2 à moyen et 3 à difficile
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=220&&event->motion.y<=270)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/moyenover.png", rendu, image, texture, rect,menu_x,220);
      if(mode==1)if(jeu_classique(window, rendu, image, texture, rect, event, 2)==-1)return -1;
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=290&&event->motion.y<=340)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/difficileover.png", rendu, image, texture, rect,menu_x,290);
      if(mode==1)if(jeu_classique(window, rendu, image, texture, rect, event, 3)==-1)return -1;
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=360&&event->motion.y<=410)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/retourover.png", rendu, image, texture, rect,menu_x,360);
      if(event->type==SDL_MOUSEBUTTONDOWN){
        charger_image("data/backgrounds/bgmenu1.bmp", rendu, image, texture, rect,0,0);
        jouer=SDL_FALSE;
      }
    }
    else {
      charger_image("data/menu/jouer/facile.png", rendu, image, texture, rect,menu_x,150);
      charger_image("data/menu/jouer/moyen.png", rendu, image, texture, rect,menu_x,220);
      charger_image("data/menu/jouer/difficile.png", rendu, image, texture, rect,menu_x,290);
      charger_image("data/menu/jouer/retour.png", rendu, image, texture, rect,menu_x,360);
    }
  }
}
}

int sous_menu_jouer(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event){
  SDL_RenderClear(rendu);
  charger_image("data/backgrounds/bgmenu1.bmp", rendu, image, texture, rect,0,0);
  SDL_bool jouer=SDL_TRUE;
  while(jouer){
    while(SDL_PollEvent(event)){ //on réécoute les évènements mais avec un pointeur sur event car en SDL on ne peut pas faire plusieurs listener d'évènements.
    if(event->type==SDL_QUIT){ //lorsque l'utilisateur appuie sur la croix rouge de la fenetre
        return -1; //on retourne -1
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=520)&&(event->motion.y>=150&&event->motion.y<=200)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/survieover.png", rendu, image, texture, rect,menu_x,150);
        if(event->type==SDL_MOUSEBUTTONDOWN){
           if(jeu_survivant(window, rendu, image, texture, rect, event)==-1)return -1; //si la fonction retourne -1 c'est que l'utilisateur a appuyé sur la croix rouge. on retourne donc -1
        }
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=250&&event->motion.y<=300)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/classiqueover.png", rendu, image, texture, rect,menu_x,250);
      if(event->type==SDL_MOUSEBUTTONDOWN){
         if(menu_jouer_difficulte(window, rendu, image, texture, rect, event, 1)==-1)return -1;
      }
    }
    else if((event->motion.x>=menu_x&&event->motion.x<=530)&&(event->motion.y>=350&&event->motion.y<=400)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
      charger_image("data/menu/jouer/retourover.png", rendu, image, texture, rect,menu_x,350);
      if(event->type==SDL_MOUSEBUTTONDOWN){
        charger_image("data/backgrounds/bgmenu1.bmp", rendu, image, texture, rect,0,0); //on recharge le décors pour effacer les boutons du menu actuel
        jouer=SDL_FALSE;
      }
    }
    else {
      charger_image("data/menu/jouer/survie.png", rendu, image, texture, rect,menu_x,150);
      charger_image("data/menu/jouer/classique.png", rendu, image, texture, rect,menu_x,250);
      charger_image("data/menu/jouer/retour.png", rendu, image, texture, rect,menu_x,350);
    }
  }
}
}
void sous_menu_parametres(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect){
  SDL_RenderClear(rendu);
  charger_image("data/backgrounds/bgmenu1.bmp", rendu, image, texture, rect,0,0);
}

void menu(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect){
    SDL_RenderClear(rendu); //on nettoie complètement le rendu à chque fois pour ne pas superposer tout
    charger_image("data/backgrounds/bgmenu1.bmp", rendu, image, texture, rect,0,0); //on charge le fond sur lequel on va charger le menu
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)printf("erreur de chargement video"); //on charge toutes les fonctionnalités de la sdl
    SDL_Event event; //on crée une variable de type event pour récupérer les actions de l'utilisateur
    SDL_bool programme = SDL_TRUE; //variable permet de garder l'écouteur dévènement actif
    while(programme){
      while(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT){ //lorsque l'utilisateur appuie sur la croix rouge de la fenetre
            programme = SDL_FALSE;
        }
          if((event.motion.x>=menu_x&&event.motion.x<=530)&&(event.motion.y>=150&&event.motion.y<=200)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
            charger_image("data/menu/jouerover.bmp", rendu, image, texture, rect,menu_x,150);
            if(event.type==SDL_MOUSEBUTTONDOWN){
              if(sous_menu_jouer(window, rendu, image, texture, rect, &event)==-1)programme = SDL_FALSE; //on quitte si la fonction retourne -1
            }
          }
          else if((event.motion.x>=menu_x&&event.motion.x<=730)&&(event.motion.y>=250&&event.motion.y<=300)){
            charger_image("data/menu/parametreover.bmp", rendu, image, texture, rect,menu_x,250);
          }
          else if((event.motion.x>=menu_x&&event.motion.x<=530)&&(event.motion.y>=350&&event.motion.y<=400)){
             charger_image("data/menu/quitterover.bmp", rendu, image, texture, rect,menu_x,350);
             if(event.type==SDL_MOUSEBUTTONDOWN){
               programme = SDL_FALSE;
             }
           }
           else if (event.window.event == SDL_WINDOWEVENT_RESIZED){ //pour éviter que tout soit dérangé lorsu'on redimmensionne la fenetre on recharge le décors principal et on redimensionne la fentre de la meme taille qu'au début (dans le menu principal l'utilisateur ne peut pas changer la taille de la fenetre)
             SDL_SetWindowSize(window, 1000, 564);
             charger_image("data/backgrounds/bgmenu1.bmp", rendu, image, texture, rect,0,0);
           }
        else { //lorsque l'utilisateur ne fait rien on recharge les boutons par défaut
          charger_image("data/menu/jouer.bmp", rendu, image, texture, rect,menu_x,150);
          charger_image("data/menu/parametres.bmp", rendu, image, texture, rect,menu_x,250);
          charger_image("data/menu/quitter.bmp", rendu, image, texture, rect,menu_x,350);
        }
      }
    }
}

int initialise_jeu(){ //fonction servant à initialiser completement le jeu en appelant les fonctions principales d'affichages qui elles-mêmes appeleront toutes les autres sous fonctions pour le jeu
  SDL_Window *window = NULL; //pointeur pour la fentre (ici on travaille uniquement avec des pointeurs pour que toutes les variables soient accessibles partout dans le code et modifiables par d'autres fonctions facilement)
  SDL_Renderer *rendu = NULL; //pointeur rendu
  SDL_Surface *image = NULL; //pointeur pour une surface qu'on pourra par la suite charger sur le rendu
  SDL_Texture *texture = NULL; //pointeur sur la texture qu'on va manipuler avec le rendu
  SDL_Rect rect = {0,0,840,720}; //un rectangle sur lequel on pourra coller la surface
  window = SDL_CreateWindow("Battle Ground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 564, SDL_WINDOW_RESIZABLE); //on crée une fenetre de type "window_resizable" car par la suite on pourra agrandir la fenêtre
  rendu = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); //on crée le rendu
  demarrage(rendu, image, texture, &rect); //fonction qui sert simplement à afficher un petit logo qui clignote lorsu'on lance le jeu
  menu(window, rendu, image, texture, &rect); //fonction principale qui charge le menu. en parametre on passe tous les pointeurs qu'on a créé dans la fonction.
  SDL_DestroyRenderer(rendu); //lorsque l'utilisateur quitte le jeu on détruit le rendu et la fenetre
  SDL_DestroyWindow(window);
  SDL_Quit(); //enfin on quitte la SDL.
  return 0;
}
//gcc test.c -o test -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
