
# This is the base folders
BINARY_FOLDER := ../Binary-Program-Folder
OBJECT_FOLDER := ../Object-Program-Folder
SOURCE_FOLDER := ../Source-Program-Folder

# This is the base source folders
ENGINE_FOLDER			:= $(SOURCE_FOLDER)/Chess-Engine-Folder
GAME_FOLDER 			:= $(SOURCE_FOLDER)/Game-Program-Folder
INTERFACE_FOLDER 	:= $(SOURCE_FOLDER)/Interface-Program-Folder

# This is the source and header folder in the engine folder
ENGINE_SOURCE_FOLDER := $(ENGINE_FOLDER)/Source-Program-Folder
ENGINE_HEADER_FOLDER := $(ENGINE_FOLDER)/Header-Program-Folder

# This is the source and header folder in the game folder
GAME_SOURCE_FOLDER := $(GAME_FOLDER)/Source-Program-Folder
GAME_FUNCTIONS_FOLDER := $(GAME_FOLDER)/Game-Functions-Folder
GAME_HEADER_FOLDER := $(GAME_FOLDER)/Header-Program-Folder

# This is the source and header folder in the interface folder
INTERFACE_SOURCE_FOLDER := $(INTERFACE_FOLDER)/Source-Program-Folder
INTERFACE_HEADER_FOLDER := $(INTERFACE_FOLDER)/Header-Program-Folder

# This is the source programs in the engine folder
ENGINE_SOURCE_PROGRAMS := $(wildcard $(ENGINE_SOURCE_FOLDER)/*.c)
ENGINE_HEADER_PROGRAMS := $(wildcard $(ENGINE_HEADER_FOLDER)/*.h)

# This is the source programs that help the game
GAME_SOURCE_PROGRAMS := $(wildcard $(GAME_SOURCE_FOLDER)/*.c)
GAME_FUNCTIONS_PROGRAMS := $(wildcard $(GAME_FUNCTIONS_FOLDER)/*.c)
GAME_HEADER_PROGRAMS := $(wildcard $(GAME_HEADER_FOLDER)/*.h)

# This is the source programs in the engine folder
INTERFACE_SOURCE_PROGRAMS := $(wildcard $(INTERFACE_SOURCE_FOLDER)/*.c)
INTERFACE_HEADER_PROGRAMS := $(wildcard $(INTERFACE_HEADER_FOLDER)/*.h)

# This is all the object, source and header files in the entire project
SOURCE_PROGRAMS := $(ENGINE_SOURCE_PROGRAMS) $(GAME_FUNCTIONS_PROGRAMS) $(INTERFACE_SOURCE_PROGRAMS)

HEADER_PROGRAMS := $(ENGINE_HEADER_PROGRAMS) $(GAME_HEADER_PROGRAMS) $(INTERFACE_HEADER_PROGRAMS)

OBJECT_PROGRAMS := $(patsubst $(ENGINE_SOURCE_FOLDER)/%.c, $(OBJECT_FOLDER)/%.o, $(ENGINE_SOURCE_PROGRAMS)) \
									 $(patsubst $(INTERFACE_SOURCE_FOLDER)/%.c, $(OBJECT_FOLDER)/%.o, $(INTERFACE_SOURCE_PROGRAMS)) \
									 $(patsubst $(GAME_FUNCTIONS_FOLDER)/%.c, $(OBJECT_FOLDER)/%.o, $(GAME_FUNCTIONS_PROGRAMS))

# This is the object files and the executables of the game files
GAME_OBJECT_PROGRAMS := $(patsubst $(GAME_SOURCE_FOLDER)/%.c, $(OBJECT_FOLDER)/%.o, $(GAME_SOURCE_PROGRAMS))
GAME_BINARY_PROGRAMS := $(patsubst $(GAME_SOURCE_FOLDER)/%.c, %, $(GAME_SOURCE_PROGRAMS))

COMPILE_FLAGS := -Wall -Werror --std=c99

SDL_LIB_FLAGS := -lSDL2main -lSDL2 -lSDL2_image
SDL_FOLDERS_LINKER := -ISDL2/include -LSDL2/lib

# This is the compile flags needed for Windows:
WIN_SDL_FLAGS := $(SDL_FOLDERS_LINKER) -lmingw32 $(SDL_LIB_FLAGS)

# This is the compile flags needed for MacOS:
MAC_SDL_FLAGS := `sdl2-config --libs --cflags` $(SDL_LIB_FLAGS)


COMPILE_COMPILOR := mingw32-gcc


# When creating an executable file, this is the linkers that is useful
EXE_LINKERS := $(WIN_SDL_FLAGS) -lm

default-targets: $(OBJECT_PROGRAMS) $(SOURCE_PROGRAMS) $(HEADER_PROGRAMS) $(GAME_BINARY_PROGRAMS)

.PRECIOUS: $(OBJECT_PROGRAMS)
.PRECIOUS: $(GAME_OBJECT_PROGRAMS)

# This is the target for compiling the executable files
%: $(GAME_SOURCE_FOLDER)/%.c $(GAME_HEADER_FOLDER)/%.h $(OBJECT_FOLDER)/%.o $(OBJECT_PROGRAMS) $(SOURCE_PROGRAMS) $(HEADER_PROGRAMS)
	$(COMPILE_COMPILOR) $(OBJECT_PROGRAMS) $(OBJECT_FOLDER)/$@.o $(COMPILE_FLAGS) $(EXE_LINKERS) -o $@

# This is the targets for the object files in the different folders
$(OBJECT_FOLDER)/%.o: $(GAME_SOURCE_FOLDER)/%.c $(GAME_HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $< -c $(COMPILE_FLAGS) -o $@

$(OBJECT_FOLDER)/%.o: $(ENGINE_SOURCE_FOLDER)/%.c $(ENGINE_HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $< -c $(COMPILE_FLAGS) -o $@

$(OBJECT_FOLDER)/%.o: $(INTERFACE_SOURCE_FOLDER)/%.c $(INTERFACE_HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $< -c $(COMPILE_FLAGS) -o $@

$(OBJECT_FOLDER)/%.o: $(GAME_FUNCTIONS_FOLDER)/%.c $(GAME_HEADER_FOLDER)/%.h
	$(COMPILE_COMPILOR) $< -c $(COMPILE_FLAGS) -o $@
