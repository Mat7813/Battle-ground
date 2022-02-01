/**
 * \file jeu.c
 * \brief Contient les fonctions principales qui lancent les 2 modes de jeu (survvivant et classique) avec quelques autres fonctions diverses.
 * \author Lazare Maclouf
 * \version 1
 * \date 25/01/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "structures.h"

/**
 * \fn int quit_message()
 * \brief affiche un message qui demande si on veut quitter la partie
 * \param rien
 * \return -1 si l'utilisateur clique sur oui, 1 sinon
 */
int quit_message(){
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
 * \fn int jeu_classique(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event, int difficulte)
 * \brief lance une partie du jeu en mode classique (gère tout l'affichage, les évènements etc...)
 * \param SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event, int difficulte
 * \return -1 si l'utilisateur clique sur la fenetre
 */
int jeu_classique(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event, int difficulte){ //fonction qui démarre une partie
  SDL_SetWindowPosition(window,50,50);
  SDL_SetWindowSize(window, 1250, 694);
  charger_image("data/backgrounds/bg1classique.png", rendu, image, texture, rect,0,0);
  SDL_Delay(1000);
  animation(rendu, image, texture, rect, 950);
  SDL_bool jouer=SDL_TRUE;
  while(jouer){
    while(SDL_PollEvent(event)){ //on réécoute les évènements mais avec un pointeur sur event car en SDL on ne peut pas faire plusieurs listener d'évènements.
    if(event->type==SDL_QUIT){ //lorsque l'utilisateur appuie sur la croix rouge de la fenetre
        if(quit_message()==-1)return -1; //on retourne -1
    }
    else if(event->window.event==SDL_WINDOWEVENT_RESIZED){
      SDL_SetWindowSize(window, 1250, 694);
    }
  }
 }
}
/**
 * \fn int jeu_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event, int difficulte)
 * \brief lance une partie du jeu en mode survivant (gère tout l'affichage, les évènements etc...)
 * \param SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event
 * \return -1 si l'utilisateur clique sur la fenetre
 */
int jeu_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event){ //fonction qui démarre une partie
  SDL_SetWindowPosition(window,50,50);
  SDL_SetWindowSize(window, 1250, 694);
  SDL_Delay(1000);
  int result=demarrer_survivant(window, rendu, image, texture, rect, event); //on appelle la fonction démarrer_survivant et en fonction de ce qu'elle retourne on aura différents traitements
  if(result==-1)return -1;
  else if(result==0)printf("Vous avez perdu !\n");
  else if(result==1)printf("Vous avez gagné !\n");
  SDL_SetWindowPosition(window,50,50);
  SDL_SetWindowSize(window, 1000, 564); /*on redimensionne la fenêtre comme elle était au départ*/
}
//gcc main.c interface.o jeu.o -o jeu -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
