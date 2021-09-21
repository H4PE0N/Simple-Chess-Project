
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

		case(PAWN): return pawn_move_handler(board, move, *info);

		case(ROOK): return rook_move_handler(board, move, info);

		case(KNIGHT): return knight_move_handler(board, move, *info);

		case(BISHOP): return bishop_move_handler(board, move, *info);

		case(QUEEN): return queen_move_handler(board, move, *info);

		case(KING): return king_move_handler(board, move, info);

		default: return false;
	}
	return false;
}

bool pawn_move_handler(Board board, Move move, Info info)
{
	if(!pawn_move_acceptable(board, move, info)) return false;

	if(!execute_pawn_move(board, move)) return false;

	return true;
}

bool rook_move_handler(Board board, Move move, Info* info)
{
	if(!rook_move_acceptable(board, move, *info)) return false;

	if(team_castle_acceptable(board, move, *info))
	{
		if(!execute_team_castle(board, move, info)) return false;
	}
	else if(!execute_rook_move(board, move, info)) return false;

	return true;
}

bool knight_move_handler(Board board, Move move, Info info)
{
	if(!knight_move_acceptable(board, move, info)) return false;

	if(!execute_knight_move(board, move)) return false;

	return true;
}

bool bishop_move_handler(Board board, Move move, Info info)
{
	if(!bishop_move_acceptable(board, move, info)) return false;

	if(!execute_bishop_move(board, move)) return false;

	return true;
}

bool queen_move_handler(Board board, Move move, Info info)
{
	if(!queen_move_acceptable(board, move, info)) return false;

	if(!execute_queen_move(board, move)) return false;

	return true;
}

bool king_move_handler(Board board, Move move, Info* info)
{
	if(!king_move_acceptable(board, move, *info)) return false;

	if(!execute_king_move(board, move, info)) return false;

	return true;
}
