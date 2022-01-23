/**
 * \file entites.c
 * \brief Contient toutes les fonctions pour gérer les structures des entités alliées et ennemies.
 * \author Lazare Maclouf
 * \version 1
 * \date 30/01/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define y_entity 470
#include "structures.h"
/**
 * \fn int hors_liste_survivant(wave *vague)
 * \brief indique si on est hors liste ou pas au niveau survivant
 * \param wave *vague
 * \return 1 si hors_liste 0 sinon
 */

t_wave* creer_vague(){
  t_wave *vague=malloc(sizeof(t_wave));
  vague->ent=malloc(sizeof(entite));
  return vague;
}

int hors_liste_survivant(t_wave *vague){
  return(vague==NULL);
}

t_wave *suivant_entite_survivant(t_wave *vague){
  if(hors_liste_survivant(vague))return NULL;
  if(vague->suiv!=NULL)vague=vague->suiv;
  return vague;
}

t_wave* precedent_entite_survivant(t_wave *vague){
  if(hors_liste_survivant(vague))return NULL;
  if(vague->prec!=NULL)vague=vague->prec;
  return vague;
}

t_wave* fin_liste_survivant(t_wave  *vague){
  if(hors_liste_survivant(vague))return NULL;
  if(vague->suiv==NULL)return vague;
  while(!hors_liste_survivant(vague->suiv)){
    vague=suivant_entite_survivant(vague);
  }
  return vague;
}

t_wave* deb_liste_survivant(t_wave *vague){
  if(hors_liste_survivant(vague))return NULL;
  if(vague->prec==NULL)return vague;
  while(!hors_liste_survivant(vague->prec)){
    vague=precedent_entite_survivant(vague);
  }
  return vague;
}

t_wave* ajouter_entite_survivant(t_wave *vague){
  t_wave *nouv=creer_vague();
  vague->suiv=nouv;
  nouv->prec=vague;
  vague=vague->suiv;
  nouv=NULL;
  return vague;
}

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

t_wave* hors_liste_classique(t_wave *vague){

}
int liste_vide_survivant(t_wave *vague){
  vague=deb_liste_survivant(vague);
  return(vague==NULL);
}
t_wave* vider_liste_survivant(t_wave *vague){
    vague=fin_liste_survivant(vague);
    while(!liste_vide_survivant(vague)){
      vague=supprimer_entite_survivant(vague);
    }
    return NULL;
}

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

void main(){
  int i=10;
  t_wave *test=charger_niveau("test", test);
  test=deb_liste_survivant(test);
  printf("%d\n", test->ent->pv);
  while(!hors_liste_survivant(test->suiv)){
    test=suivant_entite_survivant(test);
    printf("%d\n", test->ent->pv);
    i--;
  }
}
