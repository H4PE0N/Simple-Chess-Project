
SOURCE_FOLDER := ../Source-Program-Folder/Source-Program-Folder
GAME_FOLDER := ../Source-Program-Folder/Game-Program-Folder
HEADER_FOLDER := ../Source-Program-Folder/Header-Program-Folder

OBJECT_FOLDER := ../Object-Program-Folder

SOURCE_PROGRAMS := $(wildcard $(SOURCE_FOLDER)/*.c)
HEADER_PROGRAMS := $(wildcard $(HEADER_FOLDER)/*.h)

OBJECT_PROGRAMS := $(patsubst $(SOURCE_FOLDER)/%.c, $(OBJECT_FOLDER)/%.o, $(SOURCE_PROGRAMS))

COMPILE_COMPILOR := gcc
COMPILE_FLAGS := -Wall -Werror --std=c99

SDL_INCLUDE_FLAG := -I../Source-Program-Folder/SDL-Library-Programs/include
SDL_LIB_FLAG := -L../Source-Program-Folder/SDL-Library-Programs/lib

SDL_FLAGS := $(SDL_INCLUDE_FLAG) $(SDL_LIB_FLAG) -lmingw32 -lSDL2main -lSDL2

EXE_LINKERS := $(SDL_FLAGS) -lm

#start:
#	gcc ../Source-Program-Folder/Game-Program-Folder/test-game-program.c -ISDL2-64/include -LSDL2-64/lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main

.PRECIOUS: $(OBJECT_PROGRAMS)

default-target: multi-player-chess single-player-chess zero-player-chess test-game-program

#test-game-program: ../Object-Program-Folder/test-game-program.o
#	$(COMPILE_COMPILOR) ../Object-Program-Folder/test-game-program.o $(COMPEXE_FLAGS) -o main

#../Object-Program-Folder/test-game-program.o:
#	$(COMPILE_COMPILOR) ../Source-Program-Folder/Game-Program-Folder/test-game-program.c -c -o ../Object-Program-Folder/test-game-program.o

%: $(OBJECT_PROGRAMS) $(OBJECT_FOLDER)/%.o $(SOURCE_PROGRAMS) $(HEADER_PROGRAMS) $(GAME_FOLDER)/%.c
	$(COMPILE_COMPILOR) $(OBJECT_PROGRAMS) $(OBJECT_FOLDER)/$@.o $(COMPILE_FLAGS) $(EXE_LINKERS) -o $@

$(OBJECT_FOLDER)/%.o: $(SOURCE_FOLDER)/%.c $(HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $< -c $(COMPILE_FLAGS) -o $@

$(OBJECT_FOLDER)/%.o: $(GAME_FOLDER)/%.c $(HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $< -c $(COMPILE_FLAGS) -o $@

