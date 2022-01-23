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
   vague->ent=malloc(sizeof(entite));
   printf("entré dans la fontcion crreer vague\n");
   return vague;
 }
 /**
  * \fn int hors_liste_survivant(wave *vague)
  * \brief indique si on est hors liste ou pas au niveau survivant
  * \param wave *vague
  * \return 1 si hors_liste 0 sinon
  */
 int hors_liste_survivant(t_wave *vague){
   return(vague==NULL);
 }
 /**
  * \fn  t_wave *suivant_entite_survivant(t_wave *vague)
  * \brief place le pointeur passé en paramètre de la liste sur l'élément suivant
  * \param t_wave *vague
  * \return pointeur sur t_wave
  */
  t_wave *suivant_entite_survivant(t_wave *vague){
    if(hors_liste_survivant(vague))return NULL;
    if(vague->suiv!=NULL)vague=vague->suiv;
    return vague;
  }
 /**
  * \fn  t_wave* creer_vague()
  * \brief place le pointeur passé en paramètre de la liste sur l'élément précédent
  * \param t_wave *vague
  * \return pointeur sur t_wave
  */
  t_wave* precedent_entite_survivant(t_wave *vague){
    if(hors_liste_survivant(vague))return NULL;
    if(vague->prec!=NULL)vague=vague->prec;
    return vague;
  }

 /**
  * \fn  t_wave* creer_vague()
  * \brief place le pointeur passé en paramètre à la fin de la liste
  * \param t_wave *vague
  * \return pointeur sur t_wave
  */
  t_wave* fin_liste_survivant(t_wave  *vague){
    if(hors_liste_survivant(vague))return NULL;
    if(vague->suiv==NULL)return vague;
    while(!hors_liste_survivant(vague->suiv)){
      vague=suivant_entite_survivant(vague);
    }
    return vague;
  }
 /**
  * \fn  t_wave* creer_vague()
  * \brief place le pointeur passé en paramètre au début de la liste.
  * \param t_wave *vague
  * \return pointeur sur t_wave
  */
  t_wave* deb_liste_survivant(t_wave *vague){
    if(hors_liste_survivant(vague))return NULL;
    if(vague->prec==NULL)return vague;
    while(!hors_liste_survivant(vague->prec)){
      vague=precedent_entite_survivant(vague);
    }
    return vague;
  }

  /**
   * \fn int hors_liste_survivant(wave *vague)
   * \brief indique si on est hors liste ou pas au niveau survivant
   * \param wave *vague
   * \return 1 si hors_liste 0 sinon
   */
   int liste_vide_survivant(t_wave *vague){
     vague=deb_liste_survivant(vague);
     return(vague==NULL);
   }
 /**
  * \fn  t_wave* creer_vague()
  * \brief ajoute une entité à la liste et met le pointeur passé en paramètre sur le nouvel élément
  * \param t_wave *vague
  * \return pointeur sur t_wave
  */
  t_wave* ajouter_entite_survivant(t_wave *vague){
    t_wave *nouv=creer_vague();
    vague->suiv=nouv;
    nouv->prec=vague;
    vague=vague->suiv;
    nouv=NULL;
    return vague;
  }
 /**
  * \fn  t_wave* creer_vague()
  * \brief supprime l'entité au niveau du pointeur passé en paramètres. retourne un pointeur sur l'élément précédent
  * \param t_wave *vague
  * \return pointeur sur t_wave
  */
  t_wave* supprimer_entite_survivant(t_wave *vague){
    if(vague==NULL)return NULL;
    t_wave *temp;
    temp=deb_liste_survivant(vague);
    if(vague==temp&&hors_liste_survivant(vague->suiv)){ //situation ou il est au début et à la fin
        free(temp);
        temp=NULL;
        return NULL;
    }
    else if(vague==temp&&!hors_liste_survivant(vague->suiv)){ //situation ou il est au début mais pas à la fin
        vague=vague->suiv;
        vague->prec=NULL;
        free(temp);
        temp=NULL;
    }
    else if(vague!=temp&&hors_liste_survivant(vague->suiv)){ //situation ou il est à la fin mais pas au début
        temp=vague;
        vague=vague->prec;
        vague->suiv=NULL;
        free(temp);
        temp=NULL;
    }
    else if(vague!=temp&&!hors_liste_survivant(vague->suiv)){ //situation ou il est ni à la fin ni au début
        temp=vague;
        vague=vague->prec;
        vague->suiv=temp->suiv;
        temp->suiv->prec=vague;
        free(temp);
        temp=NULL;
    }
    return vague;
  }
  /**
   * \fn  t_wave* creer_vague()
   * \brief supprime l'entité au niveau du pointeur passé en paramètres. retourne un pointeur sur l'élément précédent
   * \param t_wave *vague
   * \return pointeur sur t_wave
   */
t_wave* vider_liste_survivant(t_wave *vague){
       vague=fin_liste_survivant(vague);
       while(!liste_vide_survivant(vague)){
         vague=supprimer_entite_survivant(vague);
       }
       return NULL;
   }

 t_wave* hors_liste_classique(t_wave *vague){

 }

// dans les fichiers level.txt on a les infos suivantes : numero de la vague/type entité/nombre entité/temps avant la prochaine vague(en s)
t_wave* charger_niveau(char *nom, t_wave *vagues){ //charge le niveau à partir d'un fichier txt
  FILE *fichier=fopen(nom, "r");
  char car[45]="data/entities/mumma/mummy1.png";
  int pv=1;
  printf("%p\n", vagues);
  vagues=creer_vague();
  printf("%p\n", vagues);
    for(int i=0;i<10;i++){
    strcpy(vagues->ent->nom_fichier,"data/entities/mumma/mummy1.png");
    vagues->ent->pv=pv;
    vagues->ent->montant=1;
    vagues->ent->x=950;
    pv++;
    printf("%d\n", vagues->ent->pv);
    vagues=ajouter_entite_survivant(vagues);
  }
  vagues=deb_liste_survivant(vagues);
  return vagues;
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


 void deroulement_vagues(t_wave *vagues, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect){
   vagues=deb_liste_survivant(vagues);
   charger_image_option("data/backgrounds/bg1survie.png", rendu, image, texture, rect,0,0,0);
 //  if(vagues->ent->x==950){
     charger_image_option(vagues->ent->nom_fichier, rendu, image, texture, rect,vagues->ent->x,y_entity,0);
     if(vagues->ent->nom_fichier[25]<57&&vagues->ent->montant)vagues->ent->nom_fichier[25]++;
     else if(vagues->ent->nom_fichier[25]==57&&vagues->ent->montant){
       vagues->ent->nom_fichier[25]--;
       vagues->ent->montant=0;
     }
     else if(vagues->ent->nom_fichier[25]>49&&!vagues->ent->montant)vagues->ent->nom_fichier[25]--;

     else if(vagues->ent->nom_fichier[25]==49&&!vagues->ent->montant){
       vagues->ent->nom_fichier[25]++;;
       vagues->ent->montant=1;
     }
     vagues->ent->x-=2;
     SDL_RenderPresent(rendu);
     return;
 //  }
   /*else{
   while(!hors_liste(vagues->suiv)){

   }
 } */

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
    t_wave *vague=charger_niveau("test.txt", vague);
    printf("fin de la fonction test\n !");
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
      //animation(rendu, image, texture, rect, x,0);
      deroulement_vagues(vague, rendu, image, texture, rect);
      afficher_survivant(rendu, image, texture, rect);
   }
}
