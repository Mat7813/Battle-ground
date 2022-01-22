/**
 * \file survivant.c
 * \brief Contient toutes les fonctions utiles au mode de jeu survivant de battle ground (gestion de l'évolution de la partie, implémentation des structures de jeu, etc..)
 * \author Lazare Maclouf
 * \version 1
 * \date 25/01/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "structures.h"
#define V 5
// dans les fichiers level.txt on a les infos suivantes : numero de la vague/type entité/nombre entité/temps avant la prochaine vague(en s)

void charger_niveau(char *nom, t_wave *vagues){ //charge le niveau à partir d'un fichier txt
  FILE *fichier=fopen(nom, "r");
/*  int i=0;
  while(!feof(fichier)){
    fscanf(fichier, "%d/%d/%d/%d", &vagues[i].vague, &vagues[i].type_entite, &vagues[i].nb, &vagues[i].temps);
    i++;
  }
  for(i=0;i<V;i++){
  printf("%d/%d/%d/%d\n", vagues[i].vague, vagues[i].type_entite, vagues[i].nb, vagues[i].temps);
} */
  fclose(fichier);
}

void charger_joueur(joueur *player){
  player->pv=500;
  player->argent=1000;
  printf("entrer votre nom : ");
  scanf("%s", player->nom);
}

int etat_partie_survivant(t_wave *vagues, joueur *player){//retourne l'état de la partie (0 si elle est toujours en cours, 1 si le joueur a gagné, -1 si il a perdu)

}

int demarrer_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event){ //crée un ordinateur avec le nombre de vague liées au niveau.
    charger_image("data/backgrounds/bg1survie.png", rendu, image, texture, rect,0,0);
    //charger_joueur(&player);
    int x=950;
    //charger_niveau("data/modejeu/level1.txt", vagues);
    while(1){
      x-=18;
      while(SDL_PollEvent(event)){ //on réécoute les évènements mais avec un pointeur sur event car en SDL on ne peut pas faire plusieurs listener d'évènements.
    //  if(etat_partie_survivant(vagues, &player)==1)return 1;//on verifie à chaque tour de boucle l'état de la partie
    //  if(etat_partie_survivant(vagues, &player)==-1)return 0;
      if(event->type==SDL_QUIT){ //lorsque l'utilisateur appuie sur la croix rouge de la fenetre
          if(quit_message()==-1)return -1; //on retourne -1
      }
      else if(event->window.event==SDL_WINDOWEVENT_RESIZED){
        SDL_SetWindowSize(window, 1250, 694);
      }

      }
      animation(rendu, image, texture, rect, x,0);
      afficher_survivant(rendu, image, texture, rect);
   }
}
