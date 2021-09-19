
#include "../Header-Program-Folder/game-files-includer.h"

int main(int argAmount, char* arguments[])
{
	srand(time(NULL));

	char filename[200]; extract_file_name(filename, arguments, argAmount);

	Board board; Team winner = NONE; Info info;

	if(!setup_game_variables(&board, &info, filename))
	{
		setup_variables_error();

		//free_chess_board(board);

		return false;
	}

	if(zero_player_chess(&winner, board, &info))
	{
		display_chess_result(board, winner);
	}
	else chess_game_quitted(board, info);

	free_chess_board(board); return false;
}

bool zero_player_chess(Team* winner, Board board, Info* info)
{
	char input[20];
	while(game_still_running(winner, board, *info))
	{
		display_game_round(board, *info);

		fgets (input, 20, stdin);
		input[strlen(input) - 1] = '\0';

		convert_string_upper(input, strlen(input));
		if(!strcmp(input, "STOP")) return false;

		MOVE_UP_BOARD; MOVE_UP_INFO; MOVE_UP_INPUT;

		if(!computer_move_handler(board, info))
		{
			*winner = piece_team_enemy(info->current);
			break;
		}

		info->turns += 1;
		info->current = piece_team_enemy(info->current);
	}
	return true;
}

bool computer_move_handler(Board board, Info* info)
{
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
