
#include "../Header-Program-Folder/single-player-chess.h"

int main(int argAmount, char* arguments[])
{
	srand(time(NULL));

	char filename[200]; extract_file_name(filename, arguments, argAmount);

	Board board; Team winner = NONE; Info info;

	if(!setup_game_variables(&board, &info, filename))
	{
		setup_variables_error();
		free_chess_board(board); return false;
	}

	if(single_player_chess(&winner, board, &info))
	{
		display_chess_result(board, winner);
	}
	else chess_game_quitted(board, info);

	free_chess_board(board); return false;
}

bool single_player_chess(Team* winner, Board board, Info* info)
{
	while(game_still_running(winner, board, *info))
	{
		if(info->currTeam == WHITE)
		{
			if(!user_move_handler(board, info)) return false;
		}
		else if(!computer_move_handler(board, info))
		{
			*winner = WHITE; break;
		}

		if(!update_kings_point(board, info)) return false;

		info->turns += 1;
		info->currTeam = (info->currTeam == WHITE) ? BLACK : WHITE;
	}
	return true;
}

bool user_move_handler(Board board, Info* info)
{
	Move move = {(Point) {-1, -1}, (Point) {-1, -1}};
	char input[20];

	while(!move_inside_board(move))
	{
		display_game_round(board, *info);

		if(!input_current_move(input)) continue;

		//MOVE_UP_BOARD; MOVE_UP_INFO; MOVE_UP_INPUT;

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

	//MOVE_UP_BOARD; MOVE_UP_INFO;

	Move move = {(Point) {-1, -1}, (Point) {-1, -1}};

	if(!best_possible_move(&move, board, *info, 3, info->currTeam)) return false;

	if(!move_chess_piece(board, move, info)) return false;

	info->lastMove = move;

	return true;
}
