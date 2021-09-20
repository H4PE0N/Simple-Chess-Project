
#include "../Header-Program-Folder/game-files-includer.h"

// gcc ../Source-Program-Folder/Game-Program-Folder/test-game-program.c -ISDL2-64/include -LSDL2-64/lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main

int main(int argAmount, char* arguments[])
{
	srand(time(NULL));

	char filename[200]; extract_file_name(filename, arguments, argAmount);

	Board board;
	Info info;

	if(!setup_game_variables(&board, &info, filename))
	{
		setup_variables_error();

		free_chess_board(board);

		return false;
	}

	Window* window = NULL;
	Render* render = NULL;
	Surface* surface = NULL;

	if(!setup_display_variables(&window, &render, &surface, "TITLE NAME"))
	{
		printf("Error! Display!\n");

		free_chess_board(board);

		return true;
	}

    SDL_Event event;
    SDL_PollEvent(&event);

	if(!test_game_loop(board, &info, render, window))
	{
		printf("The game was ended!\n");
	}

	free_display_variables(window, render, surface);

	SDL_Quit();

	return false;

// 	srand(time(NULL));
//
// 	char filename[200]; extract_file_name(filename, arguments, argAmount);
//
// 	Board board; Info info;
//
// 	if(!setup_game_variables(&board, &info, filename))
// 	{
// 		setup_variables_error();
//
// 		free_chess_board(board);
//
// 		return false;
// 	}
//
// 	Move move = { (Point) {7, 0}, (Point) {7, 4} };
//
// 	display_chess_board(board);
//
// 	if(team_castle_acceptable(board, move, info))
// 	{
// 		printf("Ya!\n");
// 		execute_team_castle(board, move, &info);
// 	}
//
// 	display_chess_board(board);
//
// 	free_chess_board(board);
//
// 	return false;
}

bool test_game_loop(Board board, Info* info, Render* render, Window* window)
{
	Team* winner = NULL;

	while(game_still_running(winner, board, *info))
	{
		if(!render_full_board(render, board)) return false;

		SDL_UpdateWindowSurface(window);

		if(info->current == WHITE)
		{
			if(!user_move_handler(board, info)) return false;
		}
		else if(!computer_move_handler(board, info))
		{
			*winner = WHITE; break;
		}

		info->turns += 1;
		info->current = piece_team_enemy(info->current);
	}
	return true;
}

bool single_player_chess(Team* winner, Board board, Info* info)
{
	while(game_still_running(winner, board, *info))
	{
		if(info->current == WHITE)
		{
			if(!user_move_handler(board, info)) return false;
		}
		else if(!computer_move_handler(board, info))
		{
			*winner = WHITE; break;
		}

		info->turns += 1;
		info->current = piece_team_enemy(info->current);
	}
	return true;
}

bool user_move_handler(Board board, Info* info)
{
	Move move = EMPTY_MOVE;
	char input[20];

	while(!move_inside_board(move))
	{
		display_game_round(board, *info);

		if(!input_current_move(input)) continue;

		MOVE_UP_BOARD; MOVE_UP_INFO; MOVE_UP_INPUT;

		if(!strcmp(input, "STOP")) return false;

		if(!parse_chess_move(&move, board, *info, input)) continue;
	}

	if(!move_chess_piece(board, move, info))
	{
		user_move_handler(board, info);
	}

	info->lastMove = move;

	return true;
}

bool computer_move_handler(Board board, Info* info)
{
	display_game_round(board, *info);

	MOVE_UP_BOARD; MOVE_UP_INFO;

	Move move = EMPTY_MOVE;

	if(!best_possible_move(&move, board, *info, STD_DEPTH, info->current))
	{
		can_not_find_move(board, *info, info->current);

		return false;
	}

	if(!move_chess_piece(board, move, info)) return false;

	info->lastMove = move;

	return true;
}

// void test_game_program(Board board, Info info)
// {
// 	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
// 	{
// 		printf("Init Error: %s\n", SDL_GetError());
// 		return;
// 	}
//
// 	char windowTitle[20] = "CHESS BOARD WINDOW";
//
// 	//												SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
// 	SDL_Window* window = SDL_CreateWindow(windowTitle, 100, 100, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN);
//
// 	if(window == NULL)
// 	{
// 		printf("Window Error: %s\n", SDL_GetError());
// 		SDL_Quit();
// 		return;
// 	}
//
// 	SDL_render* render = SDL_Createrender(window, -1, SDL_render_ACCELERATED | SDL_render_PRESENTVSYNC);
//
// 	if(render == NULL)
// 	{
// 		printf("render Error: %s\n", SDL_GetError());
// 		SDL_DestroyWindow(window);
// 		SDL_Quit();
// 		return;
// 	}
//
// 	SDL_RenderClear(render);
//
//
// 	// SDL_Rect rectangle = {0, 0, 100, 100};
//
// 	// SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
// 	// SDL_RenderDrawRect(render, &rectangle);
//
//
// 	// SDL_RenderPresent(render);
//
//
//
// 	// SDL_Surface* window_surface = SDL_GetWindowSurface(window);
//  //    SDL_Surface* image_surface = SDL_LoadBMP("../../bot-against-chess-com.PNG");
//
//  //    SDL_BlitSurface(image_surface, NULL, window_surface, NULL);
//
//  //    SDL_UpdateWindowSurface(window);
//
//
//
// 	SDL_Surface* surface = SDL_GetWindowSurface( window );
//
// 	//Fill the surface white
// 	SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) );
//
// 	//Update the surface
// 	SDL_UpdateWindowSurface( window );
//
// 	//SDL_FreeSurface(surface);
//
//
//
//
// 	SDL_Delay(10000);
//
// 	SDL_DestroyWindow(window);
// 	SDL_Quit();
// }
