#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
//gcc test.c -o test -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
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
}

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
}
void anim_pirate(SDL_Renderer *rendu){
    int x=300;
    int x_image=0;
    int y_image=0;
    int ind=0;
    int tour=0;
    for(;x<1000;x+=2, tour++){
    SDL_RenderClear(rendu);
  charger_image("bg1.png", rendu,0,0,0);
  charger_partie_image("bandit1.png", rendu,x,500,110,110,83,83,x_image,y_image,1);
  SDL_Delay(50);
  printf("%d\n", tour);
    if(x_image+83>249){
      x_image=0;
      if(ind){
        y_image=79;
        ind=0;
      }
      else {
        y_image=0;
        ind=1;
      }
    }
    else x_image+=83;
  }
}

void anim_fighter(SDL_Renderer *rendu){
    int x=300;
    int x_image=0;
    int ind=1;
    int tour=0;
    int x_var=55;
    for(;x<1000;x+=2, tour++){
    SDL_RenderClear(rendu);
  charger_image("bg1.png", rendu,0,0,0);
  charger_partie_image("fighter.png", rendu,x,500,x_var,140,x_var,140,x_image,145,1);
  SDL_Delay(50);
  printf("%d\n", tour);
    x_image+=x_var;
    if(x_image+x_var>1200)x_image=0;
}
}

void anim_goblin(SDL_Renderer *rendu){
    int x=300;
    int x_image=0;
    int ind=1;
    int tour=0;
    for(;x<1000;x+=2, tour++){
    SDL_RenderClear(rendu);
  charger_image("bg1.png", rendu,0,0,0);
  charger_partie_image("bandit1.png", rendu,x,500,110,110,83,83,x_image,0,1);
  SDL_Delay(20);
  printf("%d\n", tour);
  if(ind==0){
    if(x_image-83<0)ind=1;
    else {
      x_image-=83;
    }
  }
  else if(ind==1){
    x_image+=83;
    if(x_image+83>249)ind=0;
  }
}
}

void anim_squeleton(SDL_Renderer *rendu){
    int x=300;
    int x_image=0;
    int ind=1;
    int tour=0;
    for(;x<1000;x+=2, tour++){
    SDL_RenderClear(rendu);
  charger_image("bg1.png", rendu,0,0,0);
  charger_partie_image("bandit1.png", rendu,x,500,110,110,83,83,x_image,145,1);
  SDL_Delay(20);
  if(ind==0){
    if(x_image-75<0)ind=1;
    else {
      x_image-=75;
    }
  }
  else if(ind==1){
    x_image+=75;
    if(x_image+75>1200)ind=0;
  }
}
}

int main(int argc, char **argv){
  SDL_Window *window = NULL; //pointeur pour la fentre (ici on travaille uniquement avec des pointeurs pour que toutes les variables soient accessibles partout dans le code et modifiables par d'autres fonctions facilement)
  SDL_Renderer *rendu = NULL; //pointeur rendu
  window = SDL_CreateWindow("Battle Ground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1250, 694, SDL_WINDOW_RESIZABLE); //on crée une fenetre de type "window_resizable" car par la suite on pourra agrandir la fenêtre
  rendu = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE); //on crée le rendu
  anim_pirate(rendu);
  SDL_DestroyRenderer(rendu); //lorsque l'utilisateur quitte le jeu on détruit le rendu et la fenetre
  SDL_DestroyWindow(window);
  SDL_Quit(); //enfin on quitte la SDL.
}
