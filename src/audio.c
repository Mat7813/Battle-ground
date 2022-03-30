/**
 * \file ajout_entites.c
 * \brief Contient les fonctions pour l'audio du jeu (la musique principale qui est jouée en boucle)
 * \author Matthieu Brière, Lazare Maclouf
 * \version 1
 * \date 25/03/2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
//#include "SDL2/SDL_mixer.h"

#define AUDIO_PATH "data/sounds/"

/**
 * \fn void print_init_flags(int flags)
 * \brief fonction qui affiche le type de fichier audio (mp3, wav, ogg etc...)
 * \param int flags
 */
/*
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
} */

/**
 * \fn void* audio_initialise(void *v)
 * \brief fonction qui lance la musique à l'aide de la librairie SDL_mixer
 * \param void *v
 * \return void *
 */
/*
void* audio_initialise(void *v)
{
   srand(time(NULL));
   int nb=rand();
   SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO);
   int volume=SDL_MIX_MAXVOLUME;
   int initted=Mix_Init(0);
   printf("Before Mix_Init SDL_mixer supported: ");
   print_init_flags(initted);
        initted=Mix_Init(~0);
        printf("After  Mix_Init SDL_mixer supported: ");
        print_init_flags(initted);
        Mix_Quit();
   //SDL_WM_SetCaption("SDL_Mixer", NULL);
   //SDL_Flip(ecran);
   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
   Mix_Music *musique; //Création du pointeur de type Mix_Music
   //Mix_Chunk *musique = NULL;
   char music_file[200];
   if(nb%2==0)sprintf(music_file, "%s%s", AUDIO_PATH, "title_theme.wav");
   else sprintf(music_file, "%s%s", AUDIO_PATH, "mainmusic.wav");
   fprintf(stderr, "Loading music %s\n", music_file);
   musique = Mix_LoadMUS(music_file); //Chargement de la musique

   Mix_MusicType type=Mix_GetMusicType(musique);
   printf("Music type: %s\n",
                                type==MUS_NONE?"MUS_NONE":
                                type==MUS_CMD?"MUS_CMD":
                                type==MUS_WAV?"MUS_WAV":
                                type==MUS_MOD?"MUS_MOD":
                                type==MUS_MID?"MUS_MID":
                                type==MUS_OGG?"MUS_OGG":
                                type==MUS_MP3?"MUS_MP3":
                                type==MUS_FLAC?"MUS_FLAC":
                                "Unknown");

   Mix_PlayMusic(musique, 1); //Jouer infiniment la musique
   while(1){
   Mix_VolumeMusic(volume);
  }
   Mix_FreeMusic(musique); //Libération de la musique
   Mix_CloseAudio(); //Fermeture de l'API
   return NULL;
} */
