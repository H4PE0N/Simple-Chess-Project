
#include "../Header-Program-Folder/interface-files-includer.h"

const char* typeStrings[] = {"EMPTY", "PAWN", "BISHOP", "KNIGHT", "ROOK", "QUEEN", "KING"};
const char* teamStrings[] = {"NONE", "WHITE", "BLACK"};

bool extract_piece_image(Surface** image, Piece piece)
{
	char filename[200]; extract_piece_filename(filename, piece);

	*image = IMG_Load(filename);

  return (*image != NULL);
}

bool extract_piece_filename(char* filename, Piece piece)
{
	if(!number_inside_bounds(piece.type, 0, 6)) return false;
	if(!number_inside_bounds(piece.team, 0, 2)) return false;

	const char* typeString = typeStrings[piece.type];
	const char* teamString = teamStrings[piece.team];

	char file[200];

	sprintf(file, "%s-%s.png", teamString, typeString);

	sprintf(filename, "%s/%s", PIECE_FOLDER, file);

	//printf("Filename: %s\n", filename);

	return true;
}

void free_display_variables(Window* window, Render* render, Surface* surface)
{
	SDL_DestroyRenderer(render);

	SDL_FreeSurface(surface);

	SDL_DestroyWindow(window);

	SDL_Quit();
}

bool create_screen_window(Window** window, Point position, char title[])
{
	*window = SDL_CreateWindow(title, position.width, position.height, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	return (*window != NULL);
}

bool create_window_surface(Surface** surface, Window* window)
{
	*surface = SDL_GetWindowSurface(window);

	return (*surface != NULL);
}

bool create_surface_render(Render** render, Surface* surface)
{
	*render = SDL_CreateSoftwareRenderer(surface);

	return (*render != NULL);
}

bool create_surface_texture(Texture** texture, Render* render, Surface* surface)
{
  *texture = SDL_CreateTextureFromSurface(render, surface);

	return (texture != NULL);
}
