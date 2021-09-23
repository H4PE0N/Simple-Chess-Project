
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

	if(multi_player_chess(&winner, board, &info))
	{
		display_game_result(board, winner);
	}
	else chess_game_quitted(board, info);

	free_chess_board(board);

	return false;
}

bool multi_player_chess(Team* winner, Board board, Info* info)
{
	Move move = EMPTY_MOVE;

	while(game_still_running(winner, board, *info))
	{
		display_console_board(board, *info);

		if(!input_console_move(&move, board, *info)) return false;

		if(!move_chess_piece(board, move, info)) continue;

		info->turns += 1;
		info->current = piece_team_enemy(info->current);
	}
	return true;
}
