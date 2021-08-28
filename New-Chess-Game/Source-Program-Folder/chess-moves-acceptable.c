
#include "../Header-Program-Folder/chess-moves-acceptable.h"

bool piece_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(board_points_equal(start, stop)) return false;

	Piece piece = board_point_piece(board, start);

	switch(piece.type)
	{
		case(EMPTY): return false; break;
	
		case(PAWN):
			if(pawn_move_acceptable(board, move, info)) return true;
			break;

		case(ROOK):
			if(rook_move_acceptable(board, move, info)) return true;
			break;

		case(KNIGHT):
			if(knight_move_acceptable(board, move, info)) return true;
			break;

		case(BISHOP):
			if(bishop_move_acceptable(board, move, info)) return true;
			break;

		case(QUEEN):
			if(queen_move_acceptable(board, move, info)) return true;
			break;

		case(KING):
			if(king_move_acceptable(board, move, info)) return true;
			break;
	}
	return false;
}

bool queen_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_queen_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	if(!check_check_situation(board, move, info)) return false;

	return true;
}

bool pawn_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_pawn_valid(board, start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(start.width == stop.width)
	{
		if(!board_point_empty(board, stop)) return false; 
	}
	else if(!board_points_enemy(board, start, stop)) return false;
	
	if(board_point_piece(board, stop).type == KING) return false;

	if(!check_check_situation(board, move, info)) return false;

	return true;
}

bool rook_switch_able(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	Color color = board_point_color(board, start);
	Point king = color_king_point(info, color);

	if(king_check_situation(board, king, color)) return false;

	if(!rook_king_switch(board, start, stop)) return false;

	RKSwitch RKS = (color == BLACK) ? info.blackRKS : info.whiteRKS;

	bool switchAble = (start.width == 0) ? RKS.left : RKS.right;
	if(!switchAble) return false;

	if(!check_after_kingSwitch(board, move, info)) return false;

	return true;
}

bool rook_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_rook_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(rook_switch_able(board, move, info)) return true;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	if(!check_check_situation(board, move, info)) return false;

	return true;
}

bool bishop_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_bishop_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	if(!check_check_situation(board, move, info)) return false;

	return true;
}

bool king_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_king_valid(start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	if(board_points_team(board, start, stop)) return false;

	if(!simulate_check_move(board, start, stop)) return false;
	
	return true;
}

bool knight_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_knight_valid(start, stop)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	if(!check_check_situation(board, move, info)) return false;

	return true;
}

bool straight_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!straight_move_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	if(!check_check_situation(board, move, info)) return false;

	return true;
}

bool diagonal_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!diagonal_move_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_piece(board, stop).type == KING) return false;

	if(!check_check_situation(board, move, info)) return false;

	return true;
}

bool check_after_kingSwitch(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	Color color = board_point_color(board, start);
	Point king = color_king_point(info, color);

	Board copy = copy_chess_board(board);
	Info infoDummy;

	execute_rook_switch(copy, move, &infoDummy);

	if(!king_check_situation(copy, stop, color))
	{ 
		free(copy); return true; 
	}

	free(copy); return false;
}

// I think you can use "move_prevent_check" instead
bool simulate_check_move(Board board, Point start, Point stop)
{
	Color color = board_point_color(board, start);

	Board copy = copy_chess_board(board);
	move_board_piece(copy, start, stop);

	if(!king_check_situation(copy, stop, color))
	{ 
		free(copy); return true; 
	}

	free(copy); return false;
}

bool check_check_situation(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	Color color = board_point_color(board, start);
	Point king = color_king_point(info, color);

	if(!king_check_situation(board, king, color)) return true;

	if(move_prevent_check(board, move, info)) return true;
	
	return false;
}