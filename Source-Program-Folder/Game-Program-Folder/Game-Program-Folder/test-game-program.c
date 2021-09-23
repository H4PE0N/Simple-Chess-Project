
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

	if(test_game_program(&winner, board, &info, window, renderer))
	{
		display_game_result(board, winner);
	}
	else chess_game_quitted(board, info);

	free_screen_variables(window, renderer, surface);

	free_chess_board(board);

	return false;
}

bool test_game_program(Team* winner, Board board, Info* info, Window* window, Renderer* renderer)
{
	Move move = EMPTY_MOVE;

	while(game_still_running(winner, board, *info))
	{
		display_console_board(board, *info);
		display_screen_board(window, renderer, board, *info);

		if(!input_console_move(&move, board, *info)) return false;

		if(!move_chess_piece(board, move, info)) continue;

		info->turns += 1;
		info->current = piece_team_enemy(info->current);
	}
	return true;
}
