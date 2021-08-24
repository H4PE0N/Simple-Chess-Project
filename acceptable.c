
#include "header.h"

bool queen_move_acceptable(Board board, Point start, Point stop)
{
	if(!moving_queen_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	return true;
}

bool pawn_move_acceptable(Board board, Point start, Point stop)
{
	if(!moving_pawn_valid(board, start, stop)) return false;

	if(start.width == stop.width)
	{
		if(path_empty_and_clear(board, start, stop)) return true;
	}
	else
	{
		if(chess_enemy_point(board, start, stop)) return true;
	}
	return false;
}

bool rook_move_acceptable(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_rook_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(rook_switch_able(board, move, info)) return true;
	
	if(chess_team_point(board, start, stop)) return false;

	return true;
}

bool bishop_move_acceptable(Board board, Point start, Point stop)
{
	if(!moving_bishop_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	return true;
}

bool king_move_acceptable(Board board, Point start, Point stop)
{
	if(!moving_king_valid(start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	Move move = {start, stop};

	Color color = board[start.height][start.width].color;

	if(simulate_check_move(board, move, color)) return true;

	return false;
}

bool knight_move_acceptable(Board board, Point start, Point stop)
{
	if(!moving_knight_valid(start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	return true;
}

bool straight_move_acceptable(Board board, Point start, Point stop)
{
	if(!straight_move_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	return true;
}

bool diagonal_move_acceptable(Board board, Point start, Point stop)
{
	if(!diagonal_move_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	return true;
}