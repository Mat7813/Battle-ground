#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define V 5
#define y_entity 470

typedef struct def{
	int type_def;
	char *nom_fichier;
	int degat;
}defense;

typedef struct joue{
	int argent;
	int pv;
	char nom[50];
}joueur;

typedef struct entity{
	int type_entite;
	int pv;
	int degat;
	int x;
	int y_barre;
	int temps; /*valeur qui correspond au nombre d'itérations de boucles à attendre avant qu'il commence à avancer*/
	char nom_fichier[100];
	int montant; /*indicateur permettant de savoir si les images sont en phases montantes ou ascendantes*/
}entite;

typedef struct wave{
 entite *ent;
 struct wave *suiv;
 struct wave *prec;
}t_wave;


typedef struct partc{
	entite *ent;
	struct partc *suiv;
	struct partc *prec;
}partie_class;

t_wave* creer_vague(){
   t_wave *vague=malloc(sizeof(t_wave));
   if(vague==NULL)return  NULL;
   vague->ent=malloc(sizeof(entite));
   vague->prec=NULL;
   vague->suiv=NULL;
   return vague;
 }

t_wave *suivant_entite_survivant(t_wave *vague){
    if(vague==NULL)return NULL;
    if(vague->suiv!=NULL)vague=vague->suiv;
    return vague;
  }

t_wave* precedent_entite_survivant(t_wave *vague){
    if(vague==NULL)return NULL;
    if(vague->prec!=NULL)vague=vague->prec;
    return vague;
  }

t_wave* fin_liste_survivant(t_wave  *vague){
    if(vague==NULL)return NULL;
    if(vague->suiv==NULL)return vague;
    while(vague->suiv!=NULL){
      vague=suivant_entite_survivant(vague);
    }
    return vague;
  }

t_wave* deb_liste_survivant(t_wave *vague){
    if(vague==NULL)return NULL;
    if(vague->prec==NULL)return vague;
    while(vague->prec!=NULL){
      vague=precedent_entite_survivant(vague);
    }
    return vague;
  }

  /**
   * \fn int liste_vide_survivant(t_wave *vague)
   * \brief indique si la liste est vide ou pas au niveau survivant. Pour le savoir, on se place au début de la liste puis on regarde si le premier élément est null si c'est le cas, la liste est vide
   * \param wave *vague
   * \return 1 si hors_liste 0 sinon
   */
int liste_vide_survivant(t_wave *vague){
     vague=deb_liste_survivant(vague);
     return(vague==NULL);
   }
 /**
  * \fn  t_wave* ajouter_entite_survivant(t_wave *vague)
  * \brief ajoute une entité à la liste et met le pointeur passé en paramètre sur le nouvel élément. Pour ajouter un nouvel element on fait appel à la fonction creer_vague()
  * \param t_wave *vague
  * \return pointeur sur t_wave
  */
t_wave* ajouter_entite_survivant(t_wave *vague){
    t_wave *nouv=creer_vague();
    vague->suiv=nouv;
    nouv->prec=vague;
    vague=vague->suiv;
    vague->suiv=NULL;
    nouv=NULL;
    return vague;
  }
 /**
  * \fn t_wave* supprimer_entite_survivant(t_wave *vague)
  * \brief supprime l'entité au niveau du pointeur passé en paramètres. retourne un pointeur sur l'élément précédent si il ya un élement précédent, sinon le suivant, sinon retourne NULL
  * \param t_wave *vague
  * \return pointeur sur t_wave (sur l'élément précédent, le suivant ou NULL).
  */
t_wave* supprimer_entite_survivant(t_wave *vague){
      if(vague==NULL)return NULL;
      t_wave *temp;
      temp=deb_liste_survivant(vague);
      if(vague==temp){
        if(vague->suiv!=NULL){
          temp=vague;
          vague=vague->suiv;
          free(temp->ent);
          free(temp);
          temp=NULL;
          vague->prec=NULL;
          return vague;
        }
        else {
          free(temp->ent);
          free(temp);
          temp=NULL;
          vague=NULL;
          return NULL;
        }
      }
      else {
        if(vague->prec!=NULL&&vague->suiv!=NULL){
          temp=vague;
          vague=vague->prec;
          vague->suiv=temp->suiv;
          vague->suiv->prec=vague;
          free(temp->ent);
          free(temp);
          temp=NULL;
          return vague;
        }
        else if(vague->prec!=NULL) {
          temp=vague;
          vague=vague->prec;
          vague->suiv=NULL;
          free(temp->ent);
          free(temp);
          temp=NULL;
          return vague;
        }
        else {
          free(temp->ent);
          free(temp);
          vague=NULL;
          return NULL;
        }
      }
    }
  /**
   * \fn  t_wave* vider_liste_survivant(t_wave *vague)
   * \brief fonction qui sert à vider la liste.
   * \param t_wave *vague
   * \return pointeur sur t_wave
   */
t_wave* vider_liste_survivant(t_wave *vague){
       vague=fin_liste_survivant(vague);
       while(vague!=NULL){
         vague=supprimer_entite_survivant(vague);
       }
       return NULL;
   }

  void afficher(t_wave *vagues){
     printf("%s\npv : %d\nmontant : %d\nx : %d\ntemps : %d\nadresse : %p\n",vagues->ent->nom_fichier, vagues->ent->pv, vagues->ent->montant, vagues->ent->x, vagues->ent->temps, vagues);
   }

t_wave* charger_niveau(char *nom, t_wave *vagues){ //charge le niveau à partir d'un fichier txt
//  FILE *fichier=fopen(nom, "r");
//    fclose(fichier);
  int temps=0;
  vagues=creer_vague();
  if(vagues==NULL)return NULL;
    for(int i=0;i<4;i++){
    strcpy(vagues->ent->nom_fichier,"data/entities/mumma/mummy1.png");
    vagues->ent->pv=50;
    vagues->ent->montant=i;
    vagues->ent->x=950;
    vagues->ent->y_barre=450;
    vagues->ent->temps=temps;
    temps+=50;
    afficher(vagues);
    if(i<3)vagues=ajouter_entite_survivant(vagues);
  }
  afficher(vagues);
  return vagues;
}


int main(){
  t_wave *vague=charger_niveau("char *nom", vague);
  printf("\n\n\n");
  printf("debut de la liste : \n");
  vague=deb_liste_survivant(vague);
  while(vague!=NULL){
    vague=supprimer_entite_survivant(vague);
    printf("%p\n", vague);
  }
  vague=supprimer_entite_survivant(vague);
  vague=suivant_entite_survivant(vague);
  printf("%p\n", vague);
  vague=precedent_entite_survivant(vague);
  printf("%p\n", vague);
  vague=fin_liste_survivant(vague);
  printf("%p\n", vague);
  vague=deb_liste_survivant(vague);
  printf("%p\n", vague);
}
