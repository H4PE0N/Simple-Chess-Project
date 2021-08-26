
#include "../Header-Program-Folder/chess-computer-program.h"

bool computer_chess_move(Board board, Info* info, Color color)
{
	Move move;

	if(!get_computer_move(&move, board, info, color)) return false;

	if(!move_chess_piece(board, move, info)) return false;
	
	return true;
}

bool get_computer_move(Move* move, Board board, Info* info, Color color)
{
	if(computer_suicide_move(move, board, info, color)) return true;

	//if(computer_offence_move(move, board, info, color)) return true;

	if(computer_regular_move(move, board, info, color)) return true;
	// Go through all team pieces and for every piece:
	// - check if they can move (move acceptable)
	// - check if they can take out someone else (return piece)
	// If no piece can take out:
	// - go through again and take the first
	return false;
}

bool computer_suicide_move(Move* move, Board board, Info* info, Color color)
{
	return false;
}

bool computer_regular_move(Move* move, Board board, Info* info, Color color)
{
	return false;
}


