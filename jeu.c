#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

int quit_message(){ //message qui lorsqu'on clique sur la croix rouge est affiché pour éviter de tout perdre en pleine partie
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

void inserer(char *c, char *chaine, int p){ //fonction qui insere le caractere c à la position p
  int i, j;
  for(i=p;chaine[i]!=0;i++); //on place i après le dernier caractère de la chaine
  for(j=i-1;j>=p;i--,j--){
    chaine[i]=chaine[j];
  }
  chaine[p]=(*c);
}

void supprimer(char *chaine, int p){ //fonction qui supprime le caractere c à la position p
  int i, j;
  for(i=p;chaine[i]!=0;i++){
    chaine[i]=chaine[i+1];
  }
}

void remplacer(char *c, char *chaine, int p){ //fonction qui remplace le caractere c à la position p
  int i, j;
  chaine[p]=(*c);
}


void animation(SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect){
  int x=950, i=49;
  char j='0';
  char car[45]="data/entities/mumma/mummy1.png";
  for(;x>200;x-=5){
    SDL_Delay(50);
    SDL_RenderClear(rendu);
    charger_image("data/backgrounds/bg1classique.png", rendu, image, texture, rect,0,0);
    charger_image(car, rendu, image, texture, rect,x,450);
    printf("%s\n", car);
    if(car[26]=='.')i++;
    if(i==57){
      i=49;
      inserer(&j, car, 26);
      j++;
      car[25]=i;
    }
    if(car[26]=='.'){
      car[25]=i;
    }
    else{
      if(i==49&&j<57){
        j++;
        car[25]=i;
        car[26]=j;
      }
      else if(i==49&&j==57){
        i++, j=48;
        car[25]=i;
        car[26]=j;
      }
      else if(i==50&&j==52){
        car[26]='.';
        supprimer(car, 27);
        i=49;
        car[25]=i;
      }
      else if(i==50&&j<52){
        j++;
        car[26]=j;
      }
    }
  }
}

int jeu_classique(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event, int difficulte){ //fonction qui démarre une partie
  SDL_SetWindowPosition(window,50,50);
  SDL_SetWindowSize(window, 1250, 694);
  charger_image("data/backgrounds/bg1classique.png", rendu, image, texture, rect,0,0);
  SDL_Delay(1000);
  animation(rendu, image, texture, rect);
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
//gcc main.c interface.o jeu.o -o jeu -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
