
#include "header.h"

bool move_chess_piece(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!point_inside_bounds(start.height, start.width)) return false;
	if(!point_inside_bounds(stop.height, stop.width)) return false;

	if(board_points_equal(start, stop)) return false;

	Piece piece = board[start.height][start.width];

	if(piece.color != info->current) return false;

	switch(piece.type)
	{
		case(NONE): return false;

		case(PAWN):
			if(!execute_pawn_move(board, move, info)) return false;
			break;

		case(ROOK):
			if(!execute_rook_move(board, move, info)) return false;
			break;

		case(KNIGHT):
			if(!execute_knight_move(board, move, info)) return false;
			break;

		case(BISHOP):
			if(!execute_bishop_move(board, move, info)) return false;
			break;

		case(QUEEN):
			if(!execute_queen_move(board, move, info)) return false;
			break;

		case(KING):
			if(!execute_king_move(board, move, info)) return false;
			break;
	}
	return true;
}

void switch_chess_pieces(Board board, Point first, Point second)
{
	Piece temporary = board[first.height][first.width];
	board[first.height][first.width] = board[second.height][second.width];
	board[second.height][second.width] = temporary;
}

bool remove_board_piece(Board board, int height, int width)
{
	if(!point_inside_bounds(height, width)) return false;
	Piece piece = {EMPTY, NONE};
	board[height][width] = piece; return true;
}

void make_pawn_queen(Board board, Point point, Color color)
{
	bool whiteQueen = (color == WHITE && point.height == 0);
	bool blackQueen = (color == BLACK && point.height == 7);

	if(whiteQueen || blackQueen)
	{
		board[point.height][point.width].type = QUEEN;
	}
}
