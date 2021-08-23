
#include "header.h"

bool chess_enemy_point(Board board, Point start, Point stop)
{
	Color start_c = board[start.height][start.width].color;
	Color stop_c = board[stop.height][stop.width].color;

	return (start_c != NONE && stop_c != NONE && stop_c != start_c);
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

bool clear_diagonal_path(Board board, Point start, Point stop)
{
	int hOffset = stop.height - start.height;
	int wOffset = stop.width - start.width;

	int hAdder = (hOffset != 0) ? (hOffset / abs(hOffset)) : 0;
	int wAdder = (wOffset != 0) ? (wOffset / abs(wOffset)) : 0;

	for(int index = 1; index < abs(hOffset); index = index + 1)
	{
		int hIndex = start.height + (index * hAdder);
		int wIndex = start.width + (index * wAdder);
		if(board[hIndex][wIndex].type != EMPTY) return false;
	}
	return true;
}

bool clear_straight_path(Board board, Point start, Point stop)
{
	int hOffset = stop.height - start.height;
	int wOffset = stop.width - start.width;

	int hAdder = (hOffset != 0) ? (hOffset / abs(hOffset)) : 0;
	int wAdder = (wOffset != 0) ? (wOffset / abs(wOffset)) : 0;

	if(wOffset == 0)
	{
		for(int height = 1; height < abs(hOffset); height = height + 1)
		{
			int hIndex = start.height + (height * hAdder);
			if(board[hIndex][start.width].type != EMPTY) return false;
		}
	}
	else if(hOffset == 0)
	{
		for(int width = 1; width < abs(wOffset); width += 1)
		{
			int wIndex = start.width + (width * wAdder);
			if(board[start.height][wIndex].type != EMPTY) return false;
		}
	}
	return true;
}

bool clear_moving_path(Board board, Point start, Point stop)
{
	int hOffset = stop.height - start.height;
	int wOffset = stop.width - start.width;

	int hAdder = (hOffset != 0) ? (hOffset / abs(hOffset)) : 0;
	int wAdder = (wOffset != 0) ? (wOffset / abs(wOffset)) : 0;

	bool diagonal = abs(hOffset) == abs(wOffset);
	bool straight = (abs(hOffset) == 0) || (abs(wOffset) == 0);

	if(diagonal)
	{
		if(!clear_diagonal_path(board, start, stop)) return false;
	}

	if(straight)
	{
		if(!clear_straight_path(board, start, stop)) return false;
	}

	return true;
}

bool moving_pawn_valid(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	int hOffset = stop.height - start.height;
	int wOffset = stop.width - start.width;

	if(abs(hOffset) == 0) return false;

	// White not moving in its direction
	Color color = board[start.height][start.width].color;

	if((color == WHITE) && (hOffset >= 0)) return false;

	// Black not moving in its direction
	if((color == BLACK) && (hOffset <= 0)) return false;

	bool straight = (start.width == stop.width);

	bool starting = (start.height == 1 || start.height == 6);

	if(straight && abs(hOffset) == 1) return true;

	if(straight && starting && abs(hOffset) == 2) return true;

	if(abs(hOffset) == 1 && abs(wOffset) == 1) return true;

	return false;
}

bool moving_rook_valid(Board board, Point start, Point stop)
{
	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	return (hSteps == 0) || (wSteps == 0);
}

bool moving_knight_valid(Board board, Point start, Point stop)
{
	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	if(hSteps == 1 && wSteps == 2) return true;

	if(hSteps == 2 && wSteps == 1) return true;

	return false;
}

bool moving_bishop_valid(Board board, Point start, Point stop)
{
	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	return (hSteps == wSteps);
}

bool moving_queen_valid(Board board, Point start, Point stop)
{
	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	bool diagonal = (hSteps == wSteps);
	bool straight = (hSteps == 0) || (wSteps == 0);

	return (diagonal || straight);
}

bool moving_king_valid(Board board, Point start, Point stop)
{
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