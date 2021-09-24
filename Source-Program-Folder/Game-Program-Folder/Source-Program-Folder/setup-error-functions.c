
#include "../Header-Program-Folder/game-files-includer.h"

void create_board_error(char filename[])
{
	printf("\n");
	display_error_message("THE CHESS BOARD COULD NOT BE CREATED!");
	display_file_error(filename);
}

void setup_info_error()
{
	printf("\n");
	display_error_message("THE BOARD INFO COULD NOT BE EXTRACTED!");
}

void file_values_error(char filename[])
{
	printf("\n");
	display_error_message("THE FILE HAD INVALID BOARD VALUES!");
	display_file_error(filename);
}

void game_variables_error()
{
	printf("\n");
	display_error_message("THE GAME-VARIABLES COULD NOT BE CREATED!");
}

void chess_game_quitted()
{
	printf("\n");
	display_error_message("THE CHESS GAME QUITTED UNEXPECTEDLY!");
}

void file_pointer_error(char filename[])
{
	printf("\n");
	display_error_message("THE FILE COULD NOT BE OPENED [NO FILE]!");
	display_file_error(filename);
}


void screen_variables_error()
{
	printf("\n");
	display_error_message("THE SCREEN-VARIABLES COULD NOT BE CREATED!");
}

void init_screen_error()
{
	printf("\n");
	display_error_message("THE SDL SCREEN COULD NOT INITIALIZE!");
	display_sdl_error();
}

void init_image_error()
{
	printf("\n");
	display_error_message("THE SDL IMAGE COULD NOT INITIALIZE!");
	display_sdl_error();
}

void create_window_error(char title[])
{
	printf("\n");
	display_error_message("COULD NOT CREATE WINDOW VARIABLE!");
	printf("[!] WINDOW TITLE WOULD BE: (%s)\n", title);
	display_sdl_error();
}

void create_surface_error(Window* window)
{
	printf("\n");
	display_error_message("COULD NOT CRAETE SURFACE VARIABLE!");
	printf("[!] ADDRESS OF WINDOW VARIABLE: (%p)\n", window);
	display_sdl_error();
}

void create_renderer_error(Surface* surface)
{
	printf("\n");
	display_error_message("COULD NOT CREATE RENDERER VARIABLE!");
	printf("[!] ADDRESS OF SURFACE VARIABLE: (%p)\n", surface);
	display_sdl_error();
}


void display_error_message(char message[])
{
	printf("[ERROR]: %s\n", message);
}

void display_file_error(char filename[])
{
	printf("[!] FILE THAT CAUSED ERROR: (%s)\n", filename);
}

void display_sdl_error()
{
	printf("[SDL]: %s\n", SDL_GetError());
}
