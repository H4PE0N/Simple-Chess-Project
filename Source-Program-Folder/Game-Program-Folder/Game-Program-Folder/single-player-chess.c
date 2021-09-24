
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
		setup_variables_error();

		free_chess_board(board);

		return false;
	}

	Window* window = NULL;
	Renderer* renderer = NULL;
	Surface* surface = NULL;

	if(!setup_screen_variables(&window, &renderer, &surface, "TEST PROGRAM"))
	{
		printf("Error screen vars!\n");

		free_chess_board(board);

		return false;
	}

	// if(console_single_player(&winner, board, &info))
	if(screen_single_player(&winner, board, &info, window, renderer))
	{
		display_game_result(board, winner);
	}
	else chess_game_quitted(board, info);


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
