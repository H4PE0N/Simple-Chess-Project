
#include "../Header-Program-Folder/pieces-moves-valid.h"

bool moving_pawn_valid(Board board, Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	Color color = board[start.height][start.width].color;

	int hOffset = (color == WHITE) ? (start.height - stop.height) : (stop.height - start.height);
	int wOffset = abs(start.width - stop.width);

	bool straight = (start.width == stop.width);
	bool starting = (start.height == 1 || start.height == 6);

	if(straight && hOffset == 1) return true;
	if(straight && starting && hOffset == 2) return true;
	if(hOffset == 1 && wOffset == 1) return true;

	return false;
}

bool rook_king_switch(Board board, Point start, Point stop)
{
	bool start_h = (start.height == 0) || (start.height == 7);
	bool start_w = (start.width == 0) || (start.width == 7);
	bool rook_start = (start_h && start_w);

	bool stop_h = (stop.height == start.height);
	bool stop_w = (stop.width == 4);
	bool king_start = (stop_h && stop_w);

	bool king = board[stop.height][stop.width].type == KING;
	bool rook = board[start.height][start.width].type == ROOK;
	bool types = (king && rook);

	return (rook_start && king_start && types);
}

bool moving_rook_valid(Point start, Point stop)
{
	if(straight_move_valid(start, stop)) return true;

	return false;
}

bool moving_knight_valid(Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	if(hSteps == 1 && wSteps == 2) return true;

	if(hSteps == 2 && wSteps == 1) return true;

	return false;
}

bool moving_bishop_valid(Point start, Point stop)
{
	if(diagonal_move_valid(start, stop)) return true;

	return false;
}

bool moving_queen_valid(Point start, Point stop)
{
	if(diagonal_move_valid(start, stop)) return true;

	if(straight_move_valid(start, stop)) return true;

	return false;
}

bool moving_king_valid(Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	return (hSteps <= 1) && (wSteps <= 1);
}

bool straight_move_valid(Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	return (hSteps == 0) || (wSteps == 0);
}

bool diagonal_move_valid(Point start, Point stop)
{
	if(!points_inside_board(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	return (hSteps == wSteps);
}