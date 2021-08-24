
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
		case(EMPTY): return false;

		case(PAWN):
			if(pawn_move_handler(board, move, info)) return true;
			break;

		case(ROOK):
			if(rook_move_handler(board, move, info)) return true;
			break;

		case(KNIGHT):
			if(knight_move_handler(board, move, info)) return true;
			break;

		case(BISHOP):
			if(bishop_move_handler(board, move, info)) return true;
			break;

		case(QUEEN):
			if(queen_move_handler(board, move, info)) return true;
			break;

		case(KING):
			if(king_move_handler(board, move, info)) return true;
			break;
	}
	return false;
}

bool switch_chess_pieces(Board board, Point first, Point second)
{
	if(!point_inside_bounds(first.height, first.width)) return false;
	if(!point_inside_bounds(second.height, second.width)) return false;

	Piece temporary = board[first.height][first.width];
	board[first.height][first.width] = board[second.height][second.width];
	board[second.height][second.width] = temporary;

	return true;
}

bool remove_board_piece(Board board, int height, int width)
{
	if(!point_inside_bounds(height, width)) return false;
	Piece piece = {EMPTY, NONE};
	board[height][width] = piece; return true;
}

bool move_board_piece(Board board, Point start, Point stop)
{
	if(!remove_board_piece(board, stop.height, stop.width)) return false;
	if(!switch_chess_pieces(board, start, stop)) return false;

	return true;
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
