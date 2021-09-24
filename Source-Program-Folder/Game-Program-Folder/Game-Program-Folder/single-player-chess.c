
#include "../Header-Program-Folder/game-files-includer.h"

int main(int argAmount, char* arguments[])
{
	srand(time(NULL));

	char filename[200]; extract_file_name(filename, arguments, argAmount);

	Board board = create_board_memory(BOARD_HEIGHT, BOARD_WIDTH);
	Team winner = NONE;
	Info info;

	if(!setup_game_variables(board, &info, filename))
	{
		game_variables_error();

		free_chess_board(board);

		return false;
	}

	Window* window = NULL;
	Renderer* renderer = NULL;
	Surface* surface = NULL;

	if(!setup_screen_variables(&window, &renderer, &surface, "SINGLE PLAYER CHESS"))
	{
		screen_variables_error();

		free_chess_board(board);

		return false;
	}

	// if(console_single_player(&winner, board, &info))
	if(screen_single_player(&winner, board, &info, window, renderer))
	{
		// display_console_result(board, winner);
		render_screen_result(renderer, board, winner);
		SDL_UpdateWindowSurface(window);

		printf("PRESS ANY KEY TO CONTINUE...");
		getchar();
	}
	else chess_game_quitted();


	free_screen_variables(window, renderer, surface);

	free_chess_board(board);

	return false;
}

bool console_single_player(Team* winner, Board board, Info* info)
{
	while(game_still_running(winner, board, *info))
	{
		if(info->current == WHITE)
		{
			if(!console_user_handler(board, info)) return false;
		}
		else if(!console_computer_handler(board, info))
		{
			*winner = WHITE; break;
		}

		info->turns += 1;
		info->current = piece_team_enemy(info->current);
	}
	return true;
}

bool screen_single_player(Team* winner, Board board, Info* info, Window* window, Renderer* renderer)
{
	while(game_still_running(winner, board, *info))
	{
		if(info->current == WHITE)
		{
			if(!screen_user_handler(board, info, window, renderer)) return false;
		}
		else if(!screen_computer_handler(board, info, window, renderer))
		{
			*winner = WHITE; break;
		}

		info->turns += 1;
		info->current = piece_team_enemy(info->current);
	}
	return true;
}
