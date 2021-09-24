
#include "../Header-Program-Folder/game-files-includer.h"

bool display_console_result(Board board, Team winner)
{
	if(!display_chess_board(board)) return false;

	if(piece_team_exists(winner))
	{
		char teamString[20] = "\0";
		if(!chess_team_string(teamString, winner)) return false;

		printf("[!] THE WINNER IS [%s]!\n", teamString);
	}
	else
	{
		printf("[!] THE GAME ENDED WITH A DRAW!\n");
	}
	return true;
}

bool render_screen_result(Renderer* renderer, Board board, Team winner)
{
	if(winner == WHITE)
	{
		if(!render_color_board(renderer, board, GRID_WHITE_COLOR)) return false;
	}
	else if(winner == BLACK)
	{
		if(!render_color_board(renderer, board, GRID_BLACK_COLOR)) return false;
	}
	else
	{
		if(!render_color_board(renderer, board, DRAW_GAME_COLOR)) return false;
	}

	return true;
}

bool screen_result_handler(Window* window, Renderer* renderer, Board board, Team winner)
{
	if(!render_screen_result(renderer, board, winner)) return false;
	SDL_UpdateWindowSurface(window);

	printf("[!] PRESS ENTER TO QUIT..."); getchar();

	return true;
}

bool console_user_handler(Board board, Info* info)
{
	Move move = EMPTY_MOVE;

	while(!move_inside_board(move))
	{
		display_console_board(board, *info);

		if(!input_console_move(&move, board, *info)) return false;
	}

	if(!move_chess_piece(board, move, info))
	{
		return console_user_handler(board, info);
	}

	return true;
}

bool console_computer_handler(Board board, Info* info)
{
	display_console_board(board, *info);

	Move move = EMPTY_MOVE;

	if(!best_possible_move(&move, board, *info, STD_DEPTH, info->current)) return false;

	if(!move_chess_piece(board, move, info)) return false;

	return true;
}

bool screen_user_handler(Board board, Info* info, Window* window, Renderer* renderer)
{
	Move move = EMPTY_MOVE;

	while(!move_inside_board(move))
	{
		render_screen_board(renderer, board, *info);
		SDL_UpdateWindowSurface(window);

		// display_console_board(board, *info);

		if(!input_screen_move(&move, window, renderer, board, *info)) return false;
	}

	if(!move_chess_piece(board, move, info))
	{
		return screen_user_handler(board, info, window, renderer);
	}

	return true;
}

bool screen_computer_handler(Board board, Info* info, Window* window, Renderer* renderer)
{
	render_screen_board(renderer, board, *info);
	SDL_UpdateWindowSurface(window);

	// display_console_board(board, *info);

	Move move = EMPTY_MOVE;

	if(!best_possible_move(&move, board, *info, STD_DEPTH, info->current)) return false;

	if(!move_chess_piece(board, move, info)) return false;

	return true;
}
