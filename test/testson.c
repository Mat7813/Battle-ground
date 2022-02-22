#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_mixer.h>

Mix_Chunk* mainMenuMusic;

void loadMainMenuSounds(){
    mainMenuMusic = NULL;
    mainMenuMusic = Mix_LoadWAV("music.wav");
		if(mainMenuMusic!=NULL)printf("musique existe !\n");
		else printf("musique existe pas !\n");
		    printf("Mix_LoadWAV: %s\n", Mix_GetError());
}

void startMainMenuSounds(){
        Mix_PlayChannel(5, mainMenuMusic, -1);
        Mix_Volume(5, 30);
}

int main(int argc, char *argv[]){
	SDL_Window *window = NULL; //pointeur pour la fentre (ici on travaille uniquement avec des pointeurs pour que toutes les variables soient accessibles partout dans le code et modifiables par d'autres fonctions facilement)
	SDL_Renderer *rendu = NULL; //pointeur rendu
	window = SDL_CreateWindow("Battle Ground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 564, SDL_WINDOW_RESIZABLE); //on crée une fenetre de type "window_resizable" car par la suite on pourra agrandir la fenêtre
	rendu = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); //on crée le rendu
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_OpenAudio();
	loadMainMenuSounds();
	startMainMenuSounds();
	while(1);
	SDL_DestroyRenderer(rendu); //lorsque l'utilisateur quitte le jeu on détruit le rendu et la fenetre
	SDL_DestroyWindow(window);
	SDL_Quit(); //enfin on quitte la SDL.
	return 0;
	printf("test\n");
	return 0;
}
