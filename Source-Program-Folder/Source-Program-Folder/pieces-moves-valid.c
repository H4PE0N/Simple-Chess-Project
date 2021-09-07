
#include "../Header-Program-Folder/pieces-moves-valid.h"

// This is a function that JUST cover the regular moves
// You can swap "board" for "color" if you want
bool moving_piece_valid(Board board, Point start, Point stop)
{
	switch(board_point_type(board, start))
	{
		case(EMPTY): return false;

		case(PAWN): return moving_pawn_valid(board, start, stop);

		case(ROOK): return moving_rook_valid(start, stop);

		case(KNIGHT): return moving_knight_valid(start, stop);

		case(BISHOP): return moving_bishop_valid(start, stop);

		case(QUEEN): return moving_queen_valid(start, stop);

		case(KING): return moving_king_valid(start, stop);
	}
	return false;
}

int pawn_height_offset(Point start, Point stop, Color color)
{
	if(color == WHITE) return (start.height - stop.height);
	if(color == BLACK) return (stop.height - start.height);

	return -1; // This is an invalid move for the pawn.
}

bool pawn_starting_bool(Point start, Color color)
{
	if(color == WHITE && start.height == 6) return true;
	if(color == BLACK && start.height == 1) return true;

	return false;
}

bool moving_pawn_valid(Board board, Point start, Point stop)
{
	Color color = board_point_color(board, start);

	int hOffset = pawn_height_offset(start, stop, color);
	int wOffset = abs(start.width - stop.width);

	bool straight = (start.width == stop.width);
	bool starting = pawn_starting_bool(start, color);

	if(straight && hOffset == 1) return true;
	if(straight && starting && hOffset == 2) return true;
	if(hOffset == 1 && wOffset == 1) return true;

	return false;
}

bool rook_starting_bool(Point point, Color color)
{
	if(color == WHITE && point.height != 7) return false;
	if(color == BLACK && point.height != 0) return false;

	return (point.width == 0 || point.width == 7);
}

bool king_starting_bool(Point point, Color color)
{
	if(color == WHITE && point.height != 7) return false;
	if(color == BLACK && point.height != 0) return false;

	return (point.width == 4);
}

bool rook_king_switch(Board board, Point start, Point stop)
{
	if(!board_points_team(board, start, stop)) return false;

	Color color = board_point_color(board, start);

	if(!rook_starting_bool(start, color)) return false;

	if(!king_starting_bool(stop, color)) return false;

	return true;
}

bool moving_rook_valid(Point start, Point stop)
{
	if(board_points_equal(start, stop)) return false;

	int hOffset = abs(start.height - stop.height);
	int wOffset = abs(start.width - stop.width);

	return (hOffset == 0) || (wOffset == 0);
}

bool moving_knight_valid(Point start, Point stop)
{
	int hOffset = abs(start.height - stop.height);
	int wOffset = abs(start.width - stop.width);

	if(hOffset == 1 && wOffset == 2) return true;
	if(hOffset == 2 && wOffset == 1) return true;

	return false;
}

bool moving_bishop_valid(Point start, Point stop)
{
	if(board_points_equal(start, stop)) return false;

	int hOffset = abs(start.height - stop.height);
	int wOffset = abs(start.width - stop.width);

	return (hOffset == wOffset);
}

bool moving_queen_valid(Point start, Point stop)
{
	if(board_points_equal(start, stop)) return false;

	int hOffset = abs(start.height - stop.height);
	int wOffset = abs(start.width - stop.width);

	if(hOffset == 0 || wOffset == 0) return true;
	if(hOffset == wOffset) return true;

	return false;
}

bool moving_king_valid(Point start, Point stop)
{
	if(board_points_equal(start, stop)) return false;

	int hOffset = abs(start.height - stop.height);
	int wOffset = abs(start.width - stop.width);

	return (hOffset <= 1) && (wOffset <= 1);
}