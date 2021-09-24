
#include "../Header-Program-Folder/game-files-includer.h"

bool display_game_result(Board board, Team winner)
{
	if(!display_chess_board(board)) return false;

	if(piece_team_exists(winner))
	{
		char teamString[20] = "\0";
		if(!chess_team_string(teamString, winner)) return false;

		CLEAR_LINE; printf("[!] THE WINNER IS [%s]!\n", teamString);
	}
	else
	{
		CLEAR_LINE; printf("[!] THE GAME ENDED WITH A DRAW!\n");
	}
	return true;
}

bool console_user_handler(Board board, Info* info)
{
	Move move = EMPTY_MOVE;

	while(!move_inside_board(move))
	{
		display_console_board(board, *info);

		if(!input_console_move(&move, board, *info)) return false;
	}

	if(!move_chess_piece(board, move, info))
	{
		return console_user_handler(board, info);
	}

	return true;
}

bool console_computer_handler(Board board, Info* info)
{
	display_console_board(board, *info);

	Move move = EMPTY_MOVE;

	if(!best_possible_move(&move, board, *info, STD_DEPTH, info->current))
	{
		can_not_find_move(board, *info, info->current);

		return false;
	}

	if(!move_chess_piece(board, move, info)) return false;

	return true;
}

bool screen_user_handler(Board board, Info* info, Window* window, Renderer* renderer)
{
	return false;
}

bool screen_computer_handler(Board board, Info* info, Window* window, Renderer* renderer)
{
	return false;
}
