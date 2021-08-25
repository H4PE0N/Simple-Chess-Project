
#include "header.h"

bool chess_enemy_point(Board board, Point start, Point stop)
{
	Color start_c = board[start.height][start.width].color;
	Color stop_c = board[stop.height][stop.width].color;

	return (start_c != NONE && stop_c != NONE && stop_c != start_c);
}

bool path_empty_and_clear(Board board, Point start, Point stop)
{
	bool empty = board_piece_empty(board, stop.height, stop.width);
	bool clear = clear_moving_path(board, start, stop);

	return (empty && clear);
}

bool chess_team_point(Board board, Point start, Point stop)
{
	Color start_c = board[start.height][start.width].color;
	Color stop_c = board[stop.height][stop.width].color;

	return (start_c != NONE && stop_c != NONE && start_c == stop_c);
}

bool board_points_equal(Point first, Point second)
{
	bool height = first.height == second.height;
	bool width = first.width == second.width;
	return (height && width);
}

bool board_piece_equal(Piece first, Piece second)
{
	bool type = first.type == second.type;
	bool color = first.color == second.color;
	return (type && color);
}

bool rook_switch_able(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!rook_king_switch(board, start, stop)) return false;

	Color color = board[start.height][start.width].color;

	RKSwitch* RKS = (color == BLACK) ? &info->blackRKS : &info->whiteRKS;

	return (start.width == 0) ? RKS->left : RKS->right;
}

bool clear_moving_path(Board board, Point start, Point stop)
{
	int hOffset = stop.height - start.height;
	int wOffset = stop.width - start.width;

	int steps = (abs(hOffset) > abs(wOffset)) ? abs(hOffset) : abs(wOffset);

	int hAdder = (hOffset == 0) ? 0 : (hOffset / abs(hOffset));
	int wAdder = (wOffset == 0) ? 0 : (wOffset / abs(wOffset));

	for(int index = 1; index < steps; index = index + 1)
	{
		int hIndex = start.height + (index * hAdder);
		int wIndex = start.width + (index * wAdder);

		if(board[hIndex][wIndex].type != EMPTY) return false;
	}
	return true;
}

bool check_check_situation(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	Color color = board[start.height][start.width].color;

	Point king = (color == WHITE) ? info->wKing : info->bKing;
	bool* check = (color == WHITE) ? &info->wCheck : &info->bCheck;

	if(!king_check_situation(board, king, color)) return true;

	if(move_prevent_check(board, move, info))
	{
		*check = false;
		return true;
	}
	return false;
}

bool moving_pawn_valid(Board board, Point start, Point stop)
{
	if(!points_inside_bounds(start, stop)) return false;

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

bool moving_rook_valid(Point start, Point stop)
{
	if(straight_move_valid(start, stop)) return true;

	return false;
}

bool moving_knight_valid(Point start, Point stop)
{
	if(!points_inside_bounds(start, stop)) return false;

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

bool straight_move_valid(Point start, Point stop)
{
	if(!points_inside_bounds(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	return (hSteps == 0) || (wSteps == 0);
}

bool diagonal_move_valid(Point start, Point stop)
{
	if(!points_inside_bounds(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	return (hSteps == wSteps);
}

bool moving_queen_valid(Point start, Point stop)
{
	if(diagonal_move_valid(start, stop)) return true;

	if(straight_move_valid(start, stop)) return true;

	return false;
}

bool moving_king_valid(Point start, Point stop)
{
	if(!points_inside_bounds(start, stop)) return false;

	if(board_points_equal(start, stop)) return false;

	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	return (hSteps <= 1) && (wSteps <= 1);
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

bool board_point_piece(Board board, Point point, Type type)
{
	return (board[point.height][point.width].type == type);
}