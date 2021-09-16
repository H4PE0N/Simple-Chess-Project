
#include "../Header-Program-Folder/global-include-header.h"

int main(int argAmount, char* arguments[])
{
	srand(time(NULL));

	char filename[200]; extract_file_name(filename, arguments, argAmount);

	Board board; Info info;

	if(!setup_game_variables(&board, &info, filename))
	{
		setup_variables_error();

		free_chess_board(board);

		return false;
	}

	test_game_program(board, info);

	free_chess_board(board);

	return false;
}

#define W_HEIGHT	480
#define W_WIDTH		640

void test_game_program(Board board, Info info)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		printf("Init Error: %s\n", SDL_GetError());
		return;
	}

	char windowTitle[20] = "CHESS BOARD WINDOW";

	//												SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
	SDL_Window* window = SDL_CreateWindow(windowTitle, 100, 100, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL)
	{
		printf("Window Error: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == NULL)
	{
		printf("Renderer Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}

	SDL_RenderClear(renderer);


	// SDL_Rect rectangle = {0, 0, 100, 100};

	// SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	// SDL_RenderDrawRect(renderer, &rectangle);


	// SDL_RenderPresent(renderer);



	// SDL_Surface* window_surface = SDL_GetWindowSurface(window);
 //    SDL_Surface* image_surface = SDL_LoadBMP("../../bot-against-chess-com.PNG");

 //    SDL_BlitSurface(image_surface, NULL, window_surface, NULL);

 //    SDL_UpdateWindowSurface(window);



	SDL_Surface* screenSurface = SDL_GetWindowSurface( window );

	//Fill the surface white
	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

	//Update the surface
	SDL_UpdateWindowSurface( window );

	//SDL_FreeSurface(screenSurface);




	SDL_Delay(10000);

	SDL_DestroyWindow(window);
	SDL_Quit();
}