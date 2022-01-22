/**
 * \file entites.c
 * \brief Contient toutes les fonctions pour gérer les structures des entités alliées et ennemies.
 * \author Lazare Maclouf
 * \version 1
 * \date 30/01/2022
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * \fn int hors_liste_survivant(wave *vague)
 * \brief indique si on est hors liste ou pas au niveau survivant
 * \param wave *vague
 * \return 1 si hors_liste 0 sinon
 */

 typedef struct entity{
 	int type_entite;
 	int pv;
 	int degat;
 	int x;
 	char *nom_fichier;
 }entite;

 typedef struct wave{
 	entite *ent;
 	struct wave *suiv;
 	struct wave *prec;
}t_wave;


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

void main(){
  t_wave *test=creer_vague();
  test->ent->pv=1;
  printf("%d, %p\n", test->ent->pv, test);
  test=ajouter_entite_survivant(test);
  test->ent->pv=2;
  printf("%d, %p\n", test->ent->pv, test);
  test=ajouter_entite_survivant(test);
  test->ent->pv=3;
  printf("%d, %p\n", test->ent->pv, test);
  test=supprimer_entite_survivant(test);
  test=supprimer_entite_survivant(test);
  test=vider_liste_survivant(test);
  printf("%p\n", test);
  test=precedent_entite_survivant(test);
  test=supprimer_entite_survivant(test);
  test=fin_liste_survivant(test);
  printf("%p\n", test);
  test=deb_liste_survivant(test);
  printf("%p\n", test);
}
