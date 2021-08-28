
#include "../Header-Program-Folder/single-player-chess.h"

int main(int argAmount, char* arguments[])
{
	srand(time(NULL));

	Board board; Color winner = NONE; Info info;

	if(!setup_game_variables(&board, &info))
	{
		setup_variables_error();
		free(board); return false;
	}

	if(!single_player_chess(&winner, board, &info))
	{
		chess_game_quitted(board, info);
		free(board); return false;
	}

	display_chess_result(board, winner);

	free(board); return false;
}

bool single_player_chess(Color* winner, Board board, Info* info)
{
	while(game_still_running(winner, board, *info))
	{
		info->current = WHITE;

		if(!user_move_handler(board, info)) return false;

		if(!update_kings_point(board, info)) return false;

		info->turns += 1;
		info->current = BLACK;

		if(!game_still_running(winner, board, *info)) break;

		if(!computer_move_handler(winner, board, info)) break;

		if(!update_kings_point(board, info)) return false;

		info->turns += 1;
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

		if(!strcmp(input, "stop")) return false;

		if(!parse_chess_move(&move, input)) continue;

		MOVE_UP(9); MOVE_UP(2); MOVE_UP(1);
	}
	
	if(!move_chess_piece(board, move, info))
		user_move_handler(board, info);

	return true;
}

bool computer_move_handler(Color* winner, Board board, Info* info)
{
	display_game_round(board, *info);

	MOVE_UP(9); MOVE_UP(2);

	sleep(1);

	if(!computer_chess_move(board, info, BLACK))
	{
		// The computer cant make a move and lets white (opponent) win
		*winner = WHITE; return false;
	}

	return true;
}