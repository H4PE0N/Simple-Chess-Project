
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

	if(!test_game_loop(board, &info, render, window))
	{
		printf("The game was ended!\n");

		free_display_variables(window, render, surface);

		free_chess_board(board);

		return true;
	}

	display_game_round(board, info);

	if(!render_full_board(render, board)) return false;

	SDL_UpdateWindowSurface(window);

	printf("PRESS ENTER KEY TO STOP...\n");
	getchar();

	free_display_variables(window, render, surface);

	free_chess_board(board);

	return false;
}

bool test_game_loop(Board board, Info* info, Render* render, Window* window)
{
	Team winner;

	while(game_still_running(&winner, board, *info))
	{
		if(!render_full_board(render, board)) return false;

		SDL_UpdateWindowSurface(window);

		if(info->current == WHITE)
		{
			if(!user_move_handler(board, info)) return false;
		}
		else if(!computer_move_handler(board, info))
		{
			winner = WHITE; break;
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
