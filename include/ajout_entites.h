#ifndef __AJOUT_ENTITES_H_
#define __AJOUT_ENTITES_H_
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "vague.h"

t_wave *ajouter_voisin(joueur *player, t_wave *vague, message *msg);
t_wave *ajouter_bandit(joueur *player, t_wave *vague, message *msg);
t_wave *ajouter_fighter(joueur *player, t_wave *vague, message *msg);

#endif
