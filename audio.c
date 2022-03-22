#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define AUDIO_PATH "/info/etu/l2info/s194173/projet/Battle-ground/bin/data/sounds/"

void print_init_flags(int flags)
{
#define PFLAG(a) if(flags&MIX_INIT_##a) printf(#a " ")
        PFLAG(FLAC);
        PFLAG(MOD);
        PFLAG(MP3);
        PFLAG(OGG);
        if(!flags)
                printf("None");
        printf("\n");
}

int main(int argc, char *argv[])
{
   int continuer = 1;
   //SDL_Init(SDL_INIT_VIDEO);
   SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO);
   int volume=SDL_MIX_MAXVOLUME;
   int initted=Mix_Init(0);
   printf("Before Mix_Init SDL_mixer supported: ");
   print_init_flags(initted);
        initted=Mix_Init(~0);
        printf("After  Mix_Init SDL_mixer supported: ");
        print_init_flags(initted);
        Mix_Quit();

    SDL_Window *window = NULL; 
    SDL_Renderer *rendu = NULL;                                                                                                 
    window = SDL_CreateWindow("Battle Ground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 564, SDL_WINDOW_RESIZABLE); 
    rendu = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);                          
   SDL_Event event;
   //SDL_WM_SetCaption("SDL_Mixer", NULL);
   //SDL_Flip(ecran);
   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
   Mix_Music *musique; //Création du pointeur de type Mix_Music
   //Mix_Chunk *musique = NULL;
   char music_file[200];
   sprintf(music_file, "%s%s", AUDIO_PATH, "title_theme.mp3");
   fprintf(stderr, "Loading music %s\n", music_file);
   musique = Mix_LoadMUS(music_file); //Chargement de la musique
   
   Mix_MusicType type=Mix_GetMusicType(musique);
   printf("Music type: %s\n",
                                type==MUS_NONE?"MUS_NONE":
                                type==MUS_CMD?"MUS_CMD":
                                type==MUS_WAV?"MUS_WAV":
                                /*type==MUS_MOD_MODPLUG?"MUS_MOD_MODPLUG":*/
                                type==MUS_MOD?"MUS_MOD":
                                type==MUS_MID?"MUS_MID":
                                type==MUS_OGG?"MUS_OGG":
                                type==MUS_MP3?"MUS_MP3":
                                /*type==MUS_MP3_MAD?"MUS_MP3_MAD":*/
                                type==MUS_FLAC?"MUS_FLAC":
                                "Unknown");
   
   Mix_PlayMusic(musique, 1); //Jouer infiniment la musique
   Mix_VolumeMusic(volume);
   while(continuer)
   {
      SDL_PollEvent(&event);
      switch(event.type)
      {
         case SDL_QUIT:
            continuer = 0;
            break;
      }
   }
   Mix_FreeMusic(musique); //Libération de la musique
   Mix_CloseAudio(); //Fermeture de l'API
   SDL_Quit();
   return EXIT_SUCCESS;
}
