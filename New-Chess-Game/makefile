
SOURCE_FOLDER := Source-Program-Folder
SRCOBJ_FOLDER := Source-Object-Folder
GMEOBJ_FOLDER := Game-Object-Folder
GAME_FOLDER := Game-Program-Folder
HEADER_FOLDER := Header-Program-Folder

SOURCE_PROGRAMS := $(wildcard $(SOURCE_FOLDER)/*.c)
HEADER_PROGRAMS := $(wildcard $(HEADER_FOLDER)/*.h)

MULTI_PROGRAM := $(GAME_FOLDER)/multi-player-chess.c
SINGLE_PROGRAM := $(GAME_FOLDER)/single-player-chess.c

SOURCE_OBJECTS := $(patsubst $(SOURCE_FOLDER)/%.c, $(SRCOBJ_FOLDER)/%.o, $(SOURCE_PROGRAMS))

MULTI_OBJECT := $(patsubst $(GAME_FOLDER)/%.c, $(GMEOBJ_FOLDER)/%.o, $(MULTI_PROGRAM))
SINGLE_OBJECT := $(patsubst $(GAME_FOLDER)/%.c, $(GMEOBJ_FOLDER)/%.o, $(SINGLE_PROGRAM))

COMPILE_COMPILOR := gcc
COMPEXE_FLAGS := -lm
COMPOBJ_FLAGS :=

single-player-chess: $(SOURCE_OBJECTS) $(SINGLE_OBJECT)
	$(COMPILE_COMPILOR) $(COMPILE_FLAGS) $^ -o $@

multi-player-chess: $(SOURCE_OBJECTS) $(MULTI_OBJECT)
	$(COMPILE_COMPILOR) $(COMPILE_FLAGS) $^ -o $@

$(SRCOBJ_FOLDER)/%.o: $(SOURCE_FOLDER)/%.c $(HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $(COMPOBJ_FLAGS) $< -c -o $@

$(GMEOBJ_FOLDER)/%.o: $(GAME_FOLDER)/%.c $(HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $(COMPOBJ_FLAGS) $< -c -o $@