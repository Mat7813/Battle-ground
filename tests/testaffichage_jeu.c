#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#define menu_x 350

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

int charger_image(char *nom, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, int x, int y){ //cette fonction sert à charger une image avec tous les formats (grâce à SDL_image) sur le rendu et à présenter le rendu sur la fenetre (le format géré par défaut par la SDL est BMP)
  rect->x=x, rect->y=y;
  image = IMG_Load(nom); //on commence par charger dans le pointeur sur la surface l'image BMP
  texture = SDL_CreateTextureFromSurface(rendu, image); //on crée une texture à partir du rendu et de l'image
  if(image==NULL)return -1; //si l'image n'existe pas on retourne -1
  SDL_FreeSurface(image); //on libère dans tous les cas la surface car elle a été copiée dans la texture.
  if(texture==NULL)return -1; //si on arrive pas à créer de texture on retourne -1 aussi
  if(SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h)!=0)return -1; //on place la texture dans le rectangle qu'on a reçu en paramètre. si on y arrive pas on retourne -1
  if(SDL_RenderCopy(rendu, texture, NULL, rect)!=0)return -1; //on copie la texture dans le rendu
 //enfin on affiche le rendu sur l'écran
}

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

void afficher_surv(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect){
  int code_contour_barre_vie[4]={0,0,0,255};
  int code_interieur_barre_vie[4]={255,165,0,255};
  dessiner_rectangle_vide(rendu, code_contour_barre_vie, 10, 180, 202, 12, 0);
  dessiner_rectangle_plein(rendu, code_interieur_barre_vie, 11, 181, 200, 10, 0);
  charger_image("carre1.png", rendu, image, texture, rect, 220, 10);
  charger_image("survivant.png", rendu, image, texture, rect, 740, 10);
  charger_image("piece1.png", rendu, image, texture, rect, 20, 40);
  charger_image("carre.png", rendu, image, texture, rect, 290, 10);
  charger_image("carre.png", rendu, image, texture, rect, 360, 10);
  charger_image("carre.png", rendu, image, texture, rect, 430, 10);
  charger_image("back.png", rendu, image, texture, rect, 0, 10);
  charger_image("retoursurv.png", rendu, image, texture, rect, 60, 10);
}


void menu(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect){
    int code_contour_barre_vie[4]={0,0,0,255};
    SDL_RenderClear(rendu); //on nettoie complètement le rendu à chque fois pour ne pas superposer tout
    charger_image("bg1survie.png", rendu, image, texture, rect,0,0); //on charge le fond sur lequel on va charger le menu
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)printf("erreur de chargement video"); //on charge toutes les fonctionnalités de la sdl
    SDL_Event event; //on crée une variable de type event pour récupérer les actions de l'utilisateur
    SDL_bool programme = SDL_TRUE; //variable permet de garder l'écouteur dévènement actif
    while(programme){
      while(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT){ //lorsque l'utilisateur appuie sur la croix rouge de la fenetre
            programme = SDL_FALSE;
        }
        else if((event.motion.x>=0&&event.motion.x<=100)&&(event.motion.y>=0&&event.motion.y<=30)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
          charger_image("backover.png", rendu, image, texture, rect,0,10);
          SDL_RenderPresent(rendu);
          if(event.type==SDL_MOUSEBUTTONDOWN){
            quit_message();
          }
        }
        else if((event.motion.x>=220&&event.motion.x<=280)&&(event.motion.y>=10&&event.motion.y<=60)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
          charger_image("carreover.png", rendu, image, texture, rect,220,10);
          SDL_RenderPresent(rendu);
        }
        else if((event.motion.x>=290&&event.motion.x<=350)&&(event.motion.y>=10&&event.motion.y<=60)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
          charger_image("carreover.png", rendu, image, texture, rect,290,10);
          SDL_RenderPresent(rendu);
        }
        else if((event.motion.x>=360&&event.motion.x<=420)&&(event.motion.y>=10&&event.motion.y<=60)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
          charger_image("carreover.png", rendu, image, texture, rect,360,10);
          SDL_RenderPresent(rendu);
        }
        else if((event.motion.x>=430&&event.motion.x<=500)&&(event.motion.y>=10&&event.motion.y<=60)){ //pour les trois conditions qui suivent : si l'utilisateur passe sa souris dans la zone d'un bouton (jouer, paramètres ou quitter), on change le fond du bouton en chargeant la version "over" de celui-ci
          charger_image("carreover.png", rendu, image, texture, rect,430,10);
          SDL_RenderPresent(rendu);
        }
           else if (event.window.event == SDL_WINDOWEVENT_RESIZED){ //pour éviter que tout soit dérangé lorsu'on redimmensionne la fenetre on recharge le décors principal et on redimensionne la fentre de la meme taille qu'au début (dans le menu principal l'utilisateur ne peut pas changer la taille de la fenetre)
             charger_image("bg1survie.png", rendu, image, texture, rect,0,0);
           }
        else { //lorsque l'utilisateur ne fait rien on recharge les boutons par défaut
          charger_image("bg1survie.png", rendu, image, texture, rect,0,0);
          afficher_surv(window, rendu, image, texture,rect);
            SDL_RenderPresent(rendu);
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
  window = SDL_CreateWindow("Battle Ground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1250, 694, SDL_WINDOW_RESIZABLE); //on crée une fenetre de type "window_resizable" car par la suite on pourra agrandir la fenêtre
  rendu = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); //on crée le rendu
  menu(window, rendu, image, texture, &rect); //fonction principale qui charge le menu. en parametre on passe tous les pointeurs qu'on a créé dans la fonction.
  SDL_DestroyRenderer(rendu); //lorsque l'utilisateur quitte le jeu on détruit le rendu et la fenetre
  SDL_DestroyWindow(window);
  SDL_Quit(); //enfin on quitte la SDL.
  return 0;
}

int main(int argc, char *argv[]){
  initialise_jeu();
}
//gcc test.c -o test -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
