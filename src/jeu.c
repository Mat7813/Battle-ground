/**
 * \file jeu.c
 * \brief Contient les fonctions principales qui lancent les 2 modes de jeu (survvivant et classique) avec quelques autres fonctions diverses.
 * \author Lazare Maclouf
 * \version 1
 * \date 25/01/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "survivant.h"
#include "vague.h"
#include "interface.h"
#include "classique.h"
#define NB_niv_survivant 3

/**
 * \fn int jeu_classique(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event, int difficulte)
 * \brief lance une partie du jeu en mode classique (le mode 1vs1) (gère tout l'affichage, les évènements etc...)
 * \param SDL_Window *window, SDL_Renderer *rendu, int difficulte
 * \return -1, 0 ou 1
 */
int jeu_classique(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event)
{ // fonction qui démarre une partie
  SDL_SetWindowPosition(window, 50, 50);
  SDL_SetWindowSize(window, 1250, 694);
  charger_image("data/backgrounds/bg1classique.png", rendu, 0, 0, 1);
  SDL_bool jouer = SDL_TRUE;
  int result = 1;
  while (jouer)
  {
    while (SDL_PollEvent(event))
    {                              // on réécoute les évènements mais avec un pointeur sur event car en SDL on ne peut pas faire plusieurs listener d'évènements.
      if (event->type == SDL_QUIT) // lorsque l'utilisateur appuie sur la croix rouge de la fenetre
        if (quit_message() == -1)
          return -1; // on retourne -1

      if (event->key.keysym.sym == SDLK_q)
        return -1;

      else if (event->window.event == SDL_WINDOWEVENT_RESIZED)
        SDL_SetWindowSize(window, 1250, 694);

        result = demarrer_classique(window, rendu, event);
        SDL_SetWindowPosition(window, 50, 50);
        SDL_SetWindowSize(window, 1000, 564);
        SDL_RenderClear(rendu);
      return  result;
    }
  }
  return 0;
}
/**
 * \fn int jeu_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event)
 * \brief lance une partie du jeu en mode survivant (gère tout l'affichage, les évènements etc...)
 * \param SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event
 * \return -1, 0 ou 1
 */
int jeu_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Event *event)
{ // fonction qui démarre une partie
  SDL_SetWindowPosition(window, 50, 50);
  SDL_SetWindowSize(window, 1250, 694);
  char niveau = '1';
  int result; // on appelle la fonction démarrer_survivant et en fonction de ce qu'elle retourne on aura différents traitements
  for (int i = 0; i < NB_niv_survivant; i++)
  {
    result = demarrer_survivant(window, rendu, event, niveau);
    niveau++;
    if (result == 0 || result == -1)
      break;
  }
  SDL_SetWindowPosition(window, 50, 50);
  SDL_SetWindowSize(window, 1000, 564); /*on redimensionne la fenêtre comme elle était au départ*/
  return result;
}
// gcc main.c interface.o jeu.o -o jeu -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
