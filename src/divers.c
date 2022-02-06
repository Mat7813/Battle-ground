#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int collision(int x, int x1){ //fonction qui vérifie qu'un élément ne rentre pas en contact avec un autre
  if(x!=x)return 0; //on retourne 0 si il n'y a pas de collision entre 2 objets/entités
  else return 1; //on retourne 1 si il y a collision
}

int fichier_existe(char *nom){
  FILE *fic=fopen(nom, "r");
  if(fic==NULL){
    return 0;
  }
  else {
    fclose(fic);
    return 1;
  }
}
