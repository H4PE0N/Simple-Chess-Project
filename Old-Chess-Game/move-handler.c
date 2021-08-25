
#include "header.h"

bool pawn_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!pawn_move_acceptable(board, start, stop)) return false;

	if(!check_check_situation(board, move, info)) return false;

	execute_pawn_move(board, move, info);

	return true;
}

bool rook_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!rook_move_acceptable(board, move, info)) return false;

	if(!check_check_situation(board, move, info)) return false;

	if(rook_switch_able(board, move, info))
	{
		execute_rook_switch(board, move, info); return true;
	}
	
	execute_rook_move(board, move, info);

	return true;
}

bool knight_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!knight_move_acceptable(board, start, stop)) return false;

	if(!check_check_situation(board, move, info)) return false;

	execute_knight_move(board, move, info);

	return true;
}

bool bishop_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!bishop_move_acceptable(board, start, stop)) return false;

	if(!check_check_situation(board, move, info)) return false;

	execute_bishop_move(board, move, info);

	return true;
}

bool queen_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!queen_move_acceptable(board, start, stop)) return false;

	if(!check_check_situation(board, move, info)) return false;

	execute_queen_move(board, move, info);

	return true;
}

bool king_move_handler(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;
	Color color = board[start.height][start.width].color;

	if(!king_move_acceptable(board, start, stop)) return false;

	if(!simulate_check_move(board, move, color)) return false;

	execute_king_move(board, move, info);

	return true;
}