
#include "header.h"

bool team_prevent_check(Board board, Color color)
{
	return false;
}

bool move_prevent_check(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;
	Color color = board[start.height][start.width].color;

	if(color == NONE) return false;

	Board copy = copy_chess_board(board);

	remove_board_piece(copy, start.height, start.width);
	
	switch_chess_pieces(copy, start, stop);

	Point king = (color == WHITE) ? info->wKing : info->bKing;

	if(!king_check_situation(copy, king, color))
	{
		free(copy); return true;
	}

	free(copy); return false;
}