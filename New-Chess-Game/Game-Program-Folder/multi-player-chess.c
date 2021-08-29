
#include "../Header-Program-Folder/multi-player-chess.h"

int main(int argAmount, char* arguments[])
{
	srand(time(NULL));

	char* filename = extract_file_name(arguments, argAmount);

	Board board; Color winner = NONE; Info info;

	if(!setup_game_variables(&board, &info, filename))
	{
		setup_variables_error();
		free(board); free(filename); return false;
	}

	free(filename); 

	if(!multi_player_chess(&winner, board, &info))
	{
		chess_game_quitted(board, info);
		free(board); return false;
	}

	display_chess_result(board, winner);

	free(board); return false;
}

bool multi_player_chess(Color* winner, Board board, Info* info)
{
	Move move = {(Point) {-1, -1}, (Point) {-1, -1}};
	char input[20];
	while(game_still_running(winner, board, *info))
	{
		display_game_round(board, *info);
		
		if(!input_current_move(input)) continue;

		MOVE_UP(12);

		if(!strcmp(input, "STOP")) return false;

		if(!parse_chess_move(&move, board, *info, input)) continue;

		if(!move_chess_piece(board, move, info)) continue;
		
		info->current = (info->current == WHITE) ? BLACK : WHITE;
		info->turns += 1;
	}
	return true;
}