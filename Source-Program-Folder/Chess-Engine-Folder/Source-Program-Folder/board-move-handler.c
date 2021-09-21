
#include "../Header-Program-Folder/chess-engine-includer.h"

bool move_chess_piece(Board board, Move move, Info* info)
{
	if(!move_inside_board(move)) return false;

	// It must be the current team that is moving the piece!
	Team team = board_point_team(board, move.start);
	if(!piece_team_exists(team)) return false;

	if(team != info->current) return false;

	switch(board_point_type(board, move.start))
	{
		case(EMPTY): return false;

		case(PAWN): return pawn_move_handler(board, move, info);

		case(ROOK): return rook_move_handler(board, move, info);

		case(KNIGHT): return knight_move_handler(board, move, info);

		case(BISHOP): return bishop_move_handler(board, move, info);

		case(QUEEN): return queen_move_handler(board, move, info);

		case(KING): return king_move_handler(board, move, info);

		default: return false;
	}
	return false;
}

bool pawn_move_handler(Board board, Move move, Info* info)
{
	if(!pawn_acceptable_handler(board, move, *info)) return false;

	if(!pawn_execute_handler(board, move, info)) return false;

	return true;
}

bool rook_move_handler(Board board, Move move, Info* info)
{
	if(!rook_acceptable_handler(board, move, *info)) return false;

	if(!rook_execute_handler(board, move, info)) return false;

	return true;
}

bool knight_move_handler(Board board, Move move, Info* info)
{
	if(!knight_acceptable_handler(board, move, *info)) return false;

	if(!knight_execute_handler(board, move, info)) return false;

	return true;
}

bool bishop_move_handler(Board board, Move move, Info* info)
{
	if(!bishop_acceptable_handler(board, move, *info)) return false;

	if(!bishop_execute_handler(board, move, info)) return false;

	return true;
}

bool queen_move_handler(Board board, Move move, Info* info)
{
	if(!queen_acceptable_handler(board, move, *info)) return false;

	if(!queen_execute_handler(board, move, info)) return false;

	return true;
}

bool king_move_handler(Board board, Move move, Info* info)
{
	if(!king_acceptable_handler(board, move, *info)) return false;

	if(!king_execute_handler(board, move, info)) return false;

	return true;
}
