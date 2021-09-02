
#include "../Header-Program-Folder/board-move-handler.h"

bool move_chess_piece(Board board, Move move, Info* info)
{
	Color color = board_point_color(board, move.start);
	if(color != info->current) return false;

	switch(board_point_type(board, move.start))
	{
		case(EMPTY): return false;
	
		case(PAWN): return pawn_move_handler(board, move, *info);

		case(ROOK): return rook_move_handler(board, move, info);
		
		case(KNIGHT): return knight_move_handler(board, move, *info);
			
		case(BISHOP): return bishop_move_handler(board, move, *info);
			
		case(QUEEN): return queen_move_handler(board, move, *info);
			
		case(KING): return king_move_handler(board, move, info);
	}
	return false;
}

bool pawn_move_handler(Board board, Move move, Info info)
{
	if(!pawn_move_acceptable(board, move, info)) return false;

	else execute_pawn_move(board, move); return true;
}

bool rook_move_handler(Board board, Move move, Info* info)
{
	if(!rook_move_acceptable(board, move, *info)) return false;

	if(rook_switch_able(board, move, *info))
	{
		execute_rook_switch(board, move, info); return true;
	}
	else execute_rook_move(board, move, info); return true;
}

bool knight_move_handler(Board board, Move move, Info info)
{
	if(!knight_move_acceptable(board, move, info)) return false;

	else execute_knight_move(board, move); return true;
}

bool bishop_move_handler(Board board, Move move, Info info)
{
	if(!bishop_move_acceptable(board, move, info)) return false;

	else execute_bishop_move(board, move); return true;
}

bool queen_move_handler(Board board, Move move, Info info)
{
	if(!queen_move_acceptable(board, move, info)) return false;

	else execute_queen_move(board, move); return true;
}

bool king_move_handler(Board board, Move move, Info* info)
{
	if(!king_move_acceptable(board, move, *info)) return false;

	else execute_king_move(board, move, info); return true;
}