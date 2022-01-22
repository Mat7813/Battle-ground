/**
 * \file entites.c
 * \brief Contient toutes les fonctions pour gérer les structures des entités alliées et ennemies.
 * \author Lazare Maclouf
 * \version 1
 * \date 30/01/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "structures.h"
/**
 * \fn  t_wave* creer_vague()
 * \brief crée une variable de type t_wave (une vague).
 * \param rien
 * \return pointeur sur t_wave
 */
 t_wave* creer_vague(){
   t_wave *vague=malloc(sizeof(t_wave));
   vague->ent=malloc(sizeof(entite));
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
