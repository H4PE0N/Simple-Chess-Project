
#include "../Header-Program-Folder/chess-engine-includer.h"

bool piece_move_acceptable(Board board, Move move, Info info)
{
	if(!move_inside_board(move)) return false;

	switch(board_point_type(board, move.start))
	{
		case(EMPTY): return false;

		case(PAWN): return pawn_move_acceptable(board, move, info);

		case(ROOK): return rook_move_acceptable(board, move, info);

		case(KNIGHT): return knight_move_acceptable(board, move, info);

		case(BISHOP): return bishop_move_acceptable(board, move, info);

		case(QUEEN): return queen_move_acceptable(board, move, info);

		case(KING): return king_move_acceptable(board, move, info);

		default: return false;
	}
	return false;
}

bool queen_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_type(board, start) != QUEEN) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

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

	if(board_point_type(board, start) != PAWN) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	// These controls are more specific, and should be done later
	Team team = board_point_team(board, start);
	if(!piece_team_exists(team)) return false;

	if(!moving_pawn_valid(start, stop, team)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	// These controls are vary specific, and should be done last
	if(start.width == stop.width) // Going straight
	{
		if(!board_point_empty(board, stop)) return false;
	}
	else if(!board_points_equal(stop, info.passant))
	{
		if(points_not_enemy(board, start, stop)) return false;
	}

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool rook_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_type(board, start) != ROOK) return false;

	if(board_point_empty(board, start)) return false;


	if(!moving_rook_valid(start, stop)) return false;


	if(!clear_moving_path(board, start, stop)) return false;


	Team team = board_point_team(board, start);
	if(!piece_team_exists(team)) return false;


	if(team_castle_valid(start, stop, team))
	{
		Point king = board_piece_point(board, (Piece) {KING, team});
		if(!point_inside_board(king)) return false;

		if(king_inside_check(board, king)) return false;

		// This checks that the operation is clear to go (true)
		if(!castle_bool_valid(start, info, team)) return false;
	}
	else
	{
		if(board_points_team(board, start, stop)) return false;

		if(board_point_type(board, stop) == KING) return false;
	}

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool bishop_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_type(board, start) != BISHOP) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

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

	if(board_point_type(board, start) != KING) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_king_valid(start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool diagonal_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_diagonal_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool straight_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	// These controls are more specific, and should be done later
	if(!moving_straight_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	// These controls are more specific, and should be done later
	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool knight_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_type(board, start) != KNIGHT) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_knight_valid(start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool castle_bool_valid(Point start, Info info, Team team)
{
	// If the team, of the rook in this case, does not exist:
	if(!piece_team_exists(team)) return false;

	// If the rook is not at a width that supports by this function
	// The function return the side STILL
	Side side = rook_starting_side(start.width);

	return board_castles_value(info.castles, team, side);
}

// If the rook is not at a width that supports by this function
// The function return the side STILL
Side rook_starting_side(int width)
{
	Side side = STILL;

	if(width == 0) side = LEFT;

	if(width == (BOARD_WIDTH - 1)) side = RIGHT;

	return side;
}

bool clear_moving_path(Board board, Point start, Point stop)
{
	int heightOffset = (stop.height - start.height);
	int widthOffset = (stop.width - start.width);

	// If the knight is moving, he dont need a clear moving path
	if(moving_knight_valid(start, stop)) return true;

	int steps = (abs(heightOffset) > abs(widthOffset)) ? abs(heightOffset) : abs(widthOffset);

	int heightAdder = (heightOffset == 0) ? 0 : (heightOffset / abs(heightOffset));
	int widthAdder = (widthOffset == 0) ? 0 : (widthOffset / abs(widthOffset));

	int height, width;

	Point point;

	for(int index = 1; index < steps; index = index + 1)
	{
		height = start.height + (index * heightAdder);
		width = start.width + (index * widthAdder);

		point = (Point) {height, width};

		// This means, that there is a full piece here:
		if(!board_point_empty(board, point)) return false;
		// Was board_point_clear
	}
	return true;
}
