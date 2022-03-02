/**
 * \file vagues.c
 * \brief Contient toutes les fonctions relatives à la gestion et à la manipulation des vagues d'entités
 * \author Lazare Maclouf
 * \version 1
 * \date 27/02/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/interface.h"
#include "../include/structures_vagues.h"

/**
 * \fn  t_wave* creer_vague()
 * \brief crée une variable de type t_wave (une vague).
 * \param rien
 * \return pointeur sur t_wave
 */
t_wave *creer_vague()
{
  t_wave *vague = malloc(sizeof(t_wave));
  if (vague == NULL)
    return NULL;
  vague->ent = malloc(sizeof(entite));
  vague->prec = NULL;
  vague->suiv = NULL;
  return vague;
}
/**
 * \fn  t_wave *suivant_entite_survivant(t_wave *vague)
 * \brief place le pointeur passé en paramètre de la liste sur l'élément suivant
 * \param t_wave *vague
 * \return pointeur sur t_wave
 */
t_wave *suivant_entite_survivant(t_wave *vague)
{
  if (vague == NULL)
    return NULL;
  else if (vague->suiv != NULL)
    vague = vague->suiv;
  return vague;
}
/**
 * \fn  t_wave* precedent_entite_survivant(t_wave *vague)
 * \brief place le pointeur passé en paramètre de la liste sur l'élément précédent
 * \param t_wave *vague
 * \return pointeur sur t_wave (NULL si on est hors liste et l'élément précédent si il est différent de NULL)
 */
t_wave *precedent_entite_survivant(t_wave *vague)
{
  if (vague == NULL)
    return NULL;
  else if (vague->prec != NULL)
    vague = vague->prec;
  return vague;
}

/**
 * \fn  t_wave* fin_liste_survivant(t_wave  *vague)
 * \brief place le pointeur passé en paramètre à la fin de la liste il s'agit d'une boucle. tant qu'on est pas à la fin de la liste on continue à avancer dans la liste à l'aide la fonction suivant_entite_survivant
 * \param t_wave *vague
 * \return pointeur sur t_wave (NULL si on est hors liste et l'élément suivant si il est différent de NULL)
 */
t_wave *fin_liste_survivant(t_wave *vague)
{
  if (vague == NULL)
    return NULL;
  else if (vague->suiv == NULL)
    return vague;
  while (vague->suiv != NULL)
  {
    vague = suivant_entite_survivant(vague);
  }
  return vague;
}
/**
 * \fn  t_wave* deb_liste_survivant(t_wave *vague)
 * \brief place le pointeur passé en paramètre au début de la liste. il s'agit d'une boucle. tant qu'on est pas au début de la liste on continue à reculer dans la liste à l'aide la fonction precedent_entite_survivant
 * \param t_wave *vague
 * \return pointeur sur t_wave
 */
t_wave *deb_liste_survivant(t_wave *vague)
{
  if (vague == NULL)
    return NULL;
  else if (vague->prec == NULL)
    return vague;
  while (vague->prec != NULL)
  {
    vague = precedent_entite_survivant(vague);
  }
  return vague;
}

/**
 * \fn int liste_vide_survivant(t_wave *vague)
 * \brief indique si la liste est vide ou pas au niveau survivant. Pour le savoir, on se place au début de la liste puis on regarde si le premier élément est null si c'est le cas, la liste est vide
 * \param wave *vague
 * \return 1 si hors_liste 0 sinon
 */
int liste_vide_survivant(t_wave *vague)
{
  vague = deb_liste_survivant(vague);
  return (vague == NULL);
}
/**
 * \fn  t_wave* ajouter_entite_survivant(t_wave *vague)
 * \brief ajoute une entité à la liste et met le pointeur passé en paramètre sur le nouvel élément. Pour ajouter un nouvel element on fait appel à la fonction creer_vague()
 * \param t_wave *vague
 * \return pointeur sur t_wave
 */
t_wave *ajouter_entite_survivant(t_wave *vague)
{
  t_wave *nouv = creer_vague();
  vague->suiv = nouv;
  nouv->prec = vague;
  vague = vague->suiv;
  vague->suiv = NULL;
  nouv = NULL;
  return vague;
}
/**
 * \fn t_wave* supprimer_entite_survivant(t_wave *vague)
 * \brief supprime l'entité au niveau du pointeur passé en paramètres. retourne un pointeur sur l'élément précédent si il ya un élement précédent, sinon le suivant, sinon retourne NULL
 * \param t_wave *vague
 * \return pointeur sur t_wave (sur l'élément précédent, le suivant ou NULL).
 */
t_wave *supprimer_entite_survivant(t_wave *vague)
{
  if (vague == NULL)
    return NULL;
  t_wave *temp;
  temp = deb_liste_survivant(vague);
  if (vague == temp)
  {
    if (vague->suiv != NULL)
    {
      temp = vague;
      vague = vague->suiv;
      free(temp->ent);
      free(temp);
      temp = NULL;
      vague->prec = NULL;
      return vague;
    }
    else
    {
      free(temp->ent);
      free(temp);
      temp = NULL;
      vague = NULL;
      return NULL;
    }
  }
  else
  {
    if (vague->prec != NULL && vague->suiv != NULL)
    {
      temp = vague;
      vague = vague->prec;
      vague->suiv = temp->suiv;
      vague->suiv->prec = vague;
      free(temp->ent);
      free(temp);
      temp = NULL;
      return vague;
    }
    else if (vague->prec != NULL)
    {
      temp = vague;
      vague = vague->prec;
      vague->suiv = NULL;
      free(temp->ent);
      free(temp);
      temp = NULL;
      return vague;
    }
    else
    {
      free(temp->ent);
      free(temp);
      vague = NULL;
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
t_wave *vider_liste_survivant(t_wave *vague)
{
  vague = fin_liste_survivant(vague);
  while (vague != NULL)
  {
    vague = supprimer_entite_survivant(vague);
  }
  return NULL;
}