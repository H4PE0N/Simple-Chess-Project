
#include "../Header-Program-Folder/global-include-header.h"

// gcc ../Source-Program-Folder/Game-Program-Folder/test-game-program.c -ISDL2-64/include -LSDL2-64/lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main

int main(int argAmount, char* arguments[])
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		printf("Init Error: %s\n", SDL_GetError());
		return true;
	}

	char windowTitle[20] = "CHESS BOARD WINDOW";

	//												SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
	SDL_Window* window = SDL_CreateWindow(windowTitle, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL)
	{
		printf("Window Error: %s\n", SDL_GetError());
		SDL_Quit();
		return true;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == NULL)
	{
		printf("Renderer Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return true;
	}


	// ================================================================================================
	/*SDL_Surface* screenSurface = SDL_GetWindowSurface( window );

	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

	SDL_UpdateWindowSurface( window );

	SDL_FreeSurface(screenSurface);*/
	// ================================================================================================


	// ================================================================================================
	SDL_RenderClear(renderer);




	render_chess_board(renderer);

	SDL_Delay(2000);

	
	Piece piece = {KING, BLACK};
	Point point = {2, 3};

	if(!render_board_piece(renderer, piece, point))
	{
		printf("Could not render piece!\n");
	}

	SDL_RenderPresent(renderer);
	// ================================================================================================


	// SDL_Surface* window_surface = SDL_GetWindowSurface(window);
	 //    SDL_Surface* image_surface = SDL_LoadBMP("../../bot-against-chess-com.PNG");

	 //    SDL_BlitSurface(image_surface, NULL, window_surface, NULL);

	 //    SDL_UpdateWindowSurface(window);


	bool running = 1;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = 0;
                    break;

                default:
                    break;
            }
        }
    }

	SDL_DestroyWindow(window);
	SDL_Quit();

	return false;
	/*srand(time(NULL));

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

	return false;*/
}

/*void test_game_program(Board board, Info info)
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
}*/