
#include "../Header-Program-Folder/game-files-includer.h"

bool setup_screen_variables(Window** window, Renderer** renderer, Surface** surface, char title[])
{
	if(!init_screen_variables()) return false;

	if(!create_screen_window(window, title))
	{
		create_window_error();

		SDL_Quit();

		return false;
	}

	if(!create_window_surface(surface, *window))
	{
		create_surface_error(*window);

		SDL_DestroyWindow(*window);

		SDL_Quit();

		return false;
	}

	if(!create_surface_renderer(renderer, *surface))
	{
		create_renderer_error(*surface);

		SDL_FreeSurface(*surface);

		SDL_DestroyWindow(*window);

		SDL_Quit();

		return false;
	}

	return true;
}

bool init_screen_variables()
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		init_screen_error();

		return false;
	}

	if(IMG_Init(IMG_INIT_PNG) == 0)
	{
		init_image_error();

		SDL_Quit();

		return false;
	}
	return true;
}
