
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

	sprintf(filename, "%s/%s-%s.png", PIECE_FOLDER, teamString, typeString);

	return true;
}

void free_screen_variables(Window* window, Renderer* renderer, Surface* surface)
{
	SDL_DestroyRenderer(renderer);

	SDL_FreeSurface(surface);

	SDL_DestroyWindow(window);

	SDL_Quit();
}

bool create_screen_window(Window** window, char title[])
{
	*window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	return (*window != NULL);
}

bool create_window_surface(Surface** surface, Window* window)
{
	*surface = SDL_GetWindowSurface(window);

	return (*surface != NULL);
}

bool create_surface_renderer(Renderer** renderer, Surface* surface)
{
	*renderer = SDL_CreateSoftwareRenderer(surface);

	return (*renderer != NULL);
}

bool create_surface_texture(Texture** texture, Renderer* renderer, Surface* surface)
{
  *texture = SDL_CreateTextureFromSurface(renderer, surface);

	return (texture != NULL);
}
