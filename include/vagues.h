#ifndef __VAGUES_H_
#define __VAGUES_H_
#include <stdio.h>
#include "../include/structures_vagues.h"
 t_wave* creer_vague();
 int hors_liste_survivant(t_wave *vague);
 t_wave *suivant_entite_survivant(t_wave *vague);
 t_wave* precedent_entite_survivant(t_wave *vague);
 t_wave* fin_liste_survivant(t_wave  *vague);
 t_wave* deb_liste_survivant(t_wave *vague);
 int liste_vide_survivant(t_wave *vague);
 t_wave* ajouter_entite_survivant(t_wave *vague);
 t_wave* supprimer_entite_survivant(t_wave *vague);
 t_wave* vider_liste_survivant(t_wave *vague);
#endif
