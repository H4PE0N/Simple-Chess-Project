
SOURCE_FOLDER := ../Source-Program-Folder/Source-Program-Folder
GAME_FOLDER := ../Source-Program-Folder/Game-Program-Folder
HEADER_FOLDER := ../Source-Program-Folder/Header-Program-Folder

OBJECT_FOLDER := ../Object-Program-Folder

SOURCE_PROGRAMS := $(wildcard $(SOURCE_FOLDER)/*.c)
HEADER_PROGRAMS := $(wildcard $(HEADER_FOLDER)/*.h)

OBJECT_PROGRAMS := $(patsubst $(SOURCE_FOLDER)/%.c, $(OBJECT_FOLDER)/%.o, $(SOURCE_PROGRAMS))

COMPILE_COMPILOR := gcc
COMPEXE_FLAGS := -lm # -Wall -Werror
COMPOBJ_FLAGS := # -Wall -Werror

.PRECIOUS: $(OBJECT_PROGRAMS)

default-target: multi-player-chess single-player-chess zero-player-chess

%: $(OBJECT_PROGRAMS) $(OBJECT_FOLDER)/%.o $(SOURCE_PROGRAMS) $(HEADER_PROGRAMS) $(GAME_FOLDER)/%.c
	$(COMPILE_COMPILOR) $(COMPEXE_FLAGS) $(OBJECT_PROGRAMS) $(OBJECT_FOLDER)/$@.o -o $@

$(OBJECT_FOLDER)/%.o: $(SOURCE_FOLDER)/%.c $(HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $(COMPOBJ_FLAGS) $< -c -o $@

$(OBJECT_FOLDER)/%.o: $(GAME_FOLDER)/%.c $(HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $(COMPOBJ_FLAGS) $< -c -o $@

