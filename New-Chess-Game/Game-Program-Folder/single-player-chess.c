
#include "../Header-Program-Folder/single-player-chess.h"

int main(int argAmount, char* arguments[])
{
	srand(time(NULL));
	printf("Welcome to single-player-chess.c!\n");

	Board board = malloc(sizeof(Piece*) * B_HEIGHT);
	Info info;

	if(!setup_game_variables(board, &info))
	{
		printf("Game information error!\n");

		free(board); return false;
	}

	Color winner = NONE;

	if(!single_player_chess(&winner, board, &info))
	{
		printf("The game has ended!\n");
		free(board); return false;
	}

	display_chess_board(board);

	if(winner == NONE) printf("It's a draw!\n");
	else printf("The winner is [%s]!\n", (winner == WHITE) ? "RED" : "BLUE");

	free(board); return false;
}

bool single_player_chess(Color* winner, Board board, Info* info)
{
	Move move; char current[20];
	while(game_still_running(winner, board, info))
	{
		info->current = WHITE;

		display_chess_board(board);
		display_chess_info(*info);
		
		if(!input_current_move(current)) continue;
		if(!strcmp(current, "stop")) return false;
		if(!parse_chess_move(&move, current)) continue;

		if(!move_chess_piece(board, move, info)) continue;
		
		if(!update_kings_point(board, info))
		{
			printf("One of the kings has died BNR!\n");
			return false;
		}

		info->turns += 1;
		info->current = BLACK;

		if(!game_still_running(winner, board, info)) break;

		display_chess_board(board);
		display_chess_info(*info);

		sleep(1);

		if(!computer_chess_move(board, info, BLACK))
		{
			*winner = WHITE;
			printf("The computer cant move!\n");
			break;
		}

		if(!update_kings_point(board, info))
		{
			printf("One of the kings has died BNR!\n");
			return false;
		}

		info->turns += 1;
	}
	return true;
}