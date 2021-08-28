
#include "../Header-Program-Folder/board-move-handler.h"

bool move_chess_piece(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(board_point_empty(board, start)) return false;

	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	Piece piece = board_point_piece(board, start);

	if(piece.color != info->current) return false;

	switch(piece.type)
	{
		case(EMPTY): return false;
	
		case(PAWN):
			if(pawn_move_handler(board, move, *info)) return true;
			break;

		case(ROOK):
			if(rook_move_handler(board, move, info)) return true;
			break;

		case(KNIGHT):
			if(knight_move_handler(board, move, *info)) return true;
			break;

		case(BISHOP):
			if(bishop_move_handler(board, move, *info)) return true;
			break;

		case(QUEEN):
			if(queen_move_handler(board, move, *info)) return true;
			break;

		case(KING):
			if(king_move_handler(board, move, info)) return true;
			break;
	}
	return false;
}

bool pawn_move_handler(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!pawn_move_acceptable(board, move, info)) return false;

	execute_pawn_move(board, move);

	return true;
}

bool rook_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!rook_move_acceptable(board, move, *info)) return false;

	if(rook_switch_able(board, move, *info))
	{
		execute_rook_switch(board, move, info); return true;
	}
	
	execute_rook_move(board, move, info);

	return true;
}

bool knight_move_handler(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!knight_move_acceptable(board, move, info)) return false;

	execute_knight_move(board, move);

	return true;
}

bool bishop_move_handler(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!bishop_move_acceptable(board, move, info)) return false;

	execute_bishop_move(board, move);

	return true;
}

bool queen_move_handler(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!queen_move_acceptable(board, move, info)) return false;

	execute_queen_move(board, move);

	return true;
}

bool king_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!king_move_acceptable(board, move, *info)) return false;

	execute_king_move(board, move, info);

	return true;
}