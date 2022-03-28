/**
 * \file main.c
 * \brief contient le main qui initialise le jeu
 * \version 1
 * \date 22/01/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "interface.h"

/**
 * \fn int main(int argc, char **argv)
 * \brief fonction qui sert à lancer le jeu en faisant appel à la fonction initialise_jeu
 * \param int argc, char **argv
 * \return 0
 */
int main(int argc, char **argv){
    initialise_jeu();
    return 0;
}
