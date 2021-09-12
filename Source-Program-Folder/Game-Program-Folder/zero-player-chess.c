
#include "../Header-Program-Folder/zero-player-chess.h"

int main(int argAmount, char* arguments[])
{
	srand(time(NULL));

	char* filename = extract_file_name(arguments, argAmount);

	Board board; Team winner = NONE; Info info;

	if(!setup_game_variables(&board, &info, filename))
	{
		setup_variables_error();
		free(board); free(filename); return false;
	}

	free(filename);

	if(zero_player_chess(&winner, board, &info))
	{
		display_chess_result(board, winner);
	}
	else chess_game_quitted(board, info);

	free(board); return false;
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
			*winner = (info->currTeam == WHITE) ? BLACK : WHITE;
			break;
		}

		if(!update_kings_point(board, info)) return false;

		info->turns += 1;
		info->currTeam = (info->currTeam == WHITE) ? BLACK : WHITE;
	}
	return true;
}

bool computer_move_handler(Board board, Info* info)
{
	Move move = {(Point) {-1, -1}, (Point) {-1, -1}};

	if(!best_possible_move(&move, board, *info, 3, info->currTeam)) return false;

	if(!move_chess_piece(board, move, info)) return false;

	info->lastMove = move;

	return true;
}
