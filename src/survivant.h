#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
void charger_niveau(char *nom, wave *vagues);
void charger_joueur(joueur *player);
int etat_partie_survivant(wave *vagues, joueur *player);
int demarrer_survivant(SDL_Window *window, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect, SDL_Event *event);
void deroulement_vagues_ennemies(t_wave *vagues, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect);
void deroulement_vagues_joueur(t_wave *vagues, SDL_Renderer *rendu, SDL_Surface *image,  SDL_Texture *texture, SDL_Rect *rect);
t_wave* creer_entite_joueur(t_wave *vagues);
int info_vagues(t_wave*vague, int nb, int deb, int fin, int vide);
