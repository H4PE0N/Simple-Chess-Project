
#include "../Header-Program-Folder/chess-moves-acceptable.h"

bool piece_move_acceptable(Board board, Move move, Info info)
{
	switch(board_point_type(board, move.start))
	{
		case(EMPTY): return false;
	
		case(PAWN): return pawn_move_acceptable(board, move, info);

		case(ROOK): return rook_move_acceptable(board, move, info);

		case(KNIGHT): return knight_move_acceptable(board, move, info);

		case(BISHOP): return bishop_move_acceptable(board, move, info);

		case(QUEEN): return queen_move_acceptable(board, move, info);

		case(KING): return king_move_acceptable(board, move, info);
	}
	return false;
}

bool queen_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_queen_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool pawn_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_pawn_valid(board, start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	// These controls are vary specific, and should be done last
	if(start.width == stop.width)
	{
		if(!board_point_empty(board, stop)) return false; 
	}
	else if(!board_points_enemy(board, start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool rook_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	// These controls are more specific, and should be done later
	if(!moving_rook_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	// This is a special case, and will skip the following controls
	if(rook_switch_able(board, move, info)) return true;

	// These controls are more specific, and should be done later
	if(board_points_team(board, start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool bishop_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_bishop_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool king_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_king_valid(start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;
	
	return true;
}

bool knight_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;
	
	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_knight_valid(start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool switch_bool_valid(Point start, Info info, Color color)
{
	RKSwitch rookKingSwitch = {false, false};

	if(color == WHITE) rookKingSwitch = info.whiteRKS;
	if(color == BLACK) rookKingSwitch = info.blackRKS;

	return (start.width == 0) ? rookKingSwitch.left : rookKingSwitch.right;
}

bool rook_switch_able(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	Color color = board_point_color(board, start);
	Point king = color_king_point(info, color);

	// This is a special case, you cant switch if the king is in check
	if(king_inside_check(board, king)) return false;

	// This checks if the rook and the king is on the right place
	if(!rook_king_switch(board, start, stop)) return false;

	// This checks that the operation is clear to go (true)
	if(!switch_bool_valid(start, info, color)) return false;

	if(!check_after_kingSwitch(board, move, info)) return false;

	return true;
}