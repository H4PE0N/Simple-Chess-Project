
#include "header.h"

bool pawn_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_pawn_valid(board, start, stop)) return false;

	if(execute_pawn_move(board, move, info)) return true;

	return false;
}

bool rook_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_rook_valid(board, start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(execute_rook_move(board, move, info)) return true;

	return false;
}

bool knight_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_knight_valid(board, start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	if(execute_knight_move(board, move, info)) return true;

	return false;
}

bool bishop_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_bishop_valid(board, start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(execute_bishop_move(board, move, info)) return true;

	return false;
}

bool queen_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_queen_valid(board, start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(execute_queen_move(board, move, info)) return true;

	return false;
}

bool king_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_king_valid(board, start, stop)) return false;

	if(execute_king_move(board, move, info)) return true;

	return false;
}