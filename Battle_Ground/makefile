CC=gcc
FLAGS=-Wall -g
SDL_DIR=${HOME}/Bureau/Battle_Ground/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image
INCS=-I${SDL_INC_DIR}
PROG=jeu
all: Battle
Battle: interface.c main.c jeu.c survivant.c animations.c entites.c
	${CC} -o ${PROG} interface.c main.c jeu.c survivant.c animations.c entites.c ${LIBS} ${INCS} ${FLAGS}
clean:
	rm -f ${PROG}
	rm -f *.o
