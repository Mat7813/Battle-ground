CC=gcc
FLAGS=-g -Wall
SDL_DIR=${HOME}/Bureau/Battle_Ground/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -L
INCS=-I${SDL_INC_DIR}
OBJ=obj
BIN=bin
SRC=src
PROG=jeu

DIRS=$(OBJ) $(BIN)
all: $(DIRS) $(BIN)/$(PROG)


$(OBJ):
	mkdir -p $(OBJ)
$(BIN):
	mkdir -p $(BIN)
$(DOC):
	mkdir -p $(DOC)

SOURCES=$(wildcard $(SRC)/*.c)
INCLUDES=$(wildcard $(SRC)/*.h)

OBJECTS=$(SOURCES:$(SRC)/%.c=$(OBJ)/%.o)
OBJECTSALL=$(wildcard $(OBJ)/*.o)

$(BIN)/$(PROG): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN)/$(PROG) ${LIBS} ${INCS} 
	@echo "compilation terminée !"

$(OBJECTS): $(OBJ)/%.o : $(SRC)/%.c
	$(CC) -c $< -o $@ ${FLAGS} ${LIBS} ${INCS} 
	@echo "liens effectués !"
	
clean:
	rm $(OBJ)/*.o
