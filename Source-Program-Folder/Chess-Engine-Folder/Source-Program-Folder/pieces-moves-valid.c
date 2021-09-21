
#include "../Header-Program-Folder/chess-engine-includer.h"

bool moving_piece_valid(Board board, Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	Team team = board_point_team(board, start);
	if(!piece_team_exists(team)) return false;

	switch(board_point_type(board, start))
	{
		case(EMPTY): return false;

		case(PAWN): return moving_pawn_valid(start, stop, team);

		case(ROOK): return moving_rook_valid(start, stop);

		case(KNIGHT): return moving_knight_valid(start, stop);

		case(BISHOP): return moving_bishop_valid(start, stop);

		case(QUEEN): return moving_queen_valid(start, stop);

		case(KING): return moving_king_valid(start, stop);

		default: return false;
	}
	return false;
}

int pawn_height_offset(Point start, Point stop, Team team)
{
	if(team == WHITE) return (start.height - stop.height);
	if(team == BLACK) return (stop.height - start.height);

	return -1; // This is an invalid move for the pawn.
}

bool pawn_starting_bool(Point start, Team team)
{
	if(team == WHITE && start.height == (BOARD_HEIGHT - 2)) 	return true;
	if(team == BLACK && start.height == 1) 										return true;

	return false;
}

bool moving_pawn_valid(Point start, Point stop, Team team)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	if(!piece_team_exists(team)) return false;

	int heightOffset = pawn_height_offset(start, stop, team);
	int widtheightOffset = abs(start.width - stop.width);

	bool straight = (start.width == stop.width);
	bool starting = pawn_starting_bool(start, team);

	if(straight && heightOffset == 1) 						return true;
	if(straight && starting && heightOffset == 2) return true;
	if(heightOffset == 1 && widtheightOffset == 1) 		return true;

	return false;
}

bool team_castle_valid(Point rook, Point king, Team team)
{
	if(!points_inside_board(rook, king)) return false;

	if(board_points_equal(rook, king)) return false;

	if(!piece_team_exists(team)) return false;

	if(rook.height != king.height) return false;

	if(team == WHITE && rook.height != (BOARD_HEIGHT - 1)) return false;
	if(team == BLACK && rook.height != 0) return false;

	if(king.width != KING_WIDTH) return false;

	if(rook.width != 0 && rook.width != (BOARD_WIDTH - 1)) return false;

	return true;
}

bool moving_rook_valid(Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int heightOffset = abs(start.height - stop.height);
	int widthOffset = abs(start.width - stop.width);

	return (heightOffset == 0) || (widthOffset == 0);
}

bool moving_knight_valid(Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int heightOffset = abs(start.height - stop.height);
	int widthOffset = abs(start.width - stop.width);

	if(heightOffset == 1 && widthOffset == 2) return true;
	if(heightOffset == 2 && widthOffset == 1) return true;

	return false;
}

bool moving_bishop_valid(Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int heightOffset = abs(start.height - stop.height);
	int widthOffset = abs(start.width - stop.width);

	return (heightOffset == widthOffset);
}

bool moving_queen_valid(Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int heightOffset = abs(start.height - stop.height);
	int widthOffset = abs(start.width - stop.width);

	if(heightOffset == 0 || widthOffset == 0) return true;
	if(heightOffset == widthOffset) return true;

	return false;
}

bool moving_king_valid(Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int heightOffset = abs(start.height - stop.height);
	int widthOffset = abs(start.width - stop.width);

	return (heightOffset <= 1) && (widthOffset <= 1);
}

bool moving_straight_valid(Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int heightOffset = abs(start.height - stop.height);
	int widthOffset = abs(start.width - stop.width);

	return (heightOffset == 0) || (widthOffset == 0);
}

bool moving_diagonal_valid(Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int heightOffset = abs(start.height - stop.height);
	int widthOffset = abs(start.width - stop.width);

	return (heightOffset == widthOffset);
}
