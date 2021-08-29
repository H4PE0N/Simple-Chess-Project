
SOURCE_FOLDER := Source-Program-Folder
SRCOBJ_FOLDER := Source-Object-Folder
GMEOBJ_FOLDER := Game-Object-Folder
GAME_FOLDER := Game-Program-Folder
HEADER_FOLDER := Header-Program-Folder

SOURCE_PROGRAMS := $(wildcard $(SOURCE_FOLDER)/*.c)
HEADER_PROGRAMS := $(wildcard $(HEADER_FOLDER)/*.h)

SOURCE_OBJECTS := $(patsubst $(SOURCE_FOLDER)/%.c, $(SRCOBJ_FOLDER)/%.o, $(SOURCE_PROGRAMS))

COMPILE_COMPILOR := gcc
COMPEXE_FLAGS := -lm -Wall -Werror
COMPOBJ_FLAGS := -Wall -Werror

default-target: multi-player-chess

%: $(SOURCE_OBJECTS) $(GMEOBJ_FOLDER)/%.o $(SOURCE_PROGRAMS) $(HEADER_PROGRAMS) $(GAME_FOLDER)/%.c
	$(COMPILE_COMPILOR) $(COMPILE_FLAGS) $(SOURCE_OBJECTS) $(GMEOBJ_FOLDER)/$@.o -o $@

remove-objects:
	rm $(SOURCE_OBJECTS) $(MULTI_OBJECT) $(SINGLE_OBJECT)

$(SRCOBJ_FOLDER)/%.o: $(SOURCE_FOLDER)/%.c $(HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $(COMPOBJ_FLAGS) $< -c -o $@

$(GMEOBJ_FOLDER)/%.o: $(GAME_FOLDER)/%.c $(HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $(COMPOBJ_FLAGS) $< -c -o $@