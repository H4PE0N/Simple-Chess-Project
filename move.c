
#include "header.h"

void check_remove_piece(Board board, Point start, Point stop)
{
	bool empty = board_piece_empty(board, stop.height, stop.width);

	Color start_c = board[start.height][start.width].color;
	Color stop_c = board[stop.height][stop.width].color;

	bool different = (stop_c != NONE && stop_c != start_c);

	if(!empty && different)
	{
		remove_board_piece(board, stop.height, stop.width);
	}
}

bool team_board_piece(Board board, Point start, Point stop)
{
	Color start_c = board[start.height][start.width].color;
	Color stop_c = board[stop.height][stop.width].color;

	return (start_c == stop_c);
}

bool remove_board_piece(Board board, int height, int width)
{
	if(!point_inside_bounds(height, width)) return false;
	Piece piece = {EMPTY, NONE};
	board[height][width] = piece; return true;
}

bool clear_moving_path(Board board, Point start, Point stop)
{
	int hOffset = start.height - stop.height;
	int wOffset = start.width - stop.width;

	int hAdder = (hOffset != 0) ? (-hOffset / abs(hOffset)) : 0;
	int wAdder = (wOffset != 0) ? (-wOffset / abs(wOffset)) : 0;

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

bool clear_diagonal_path(Board board, Point start, Point stop)
{
	int hOffset = start.height - stop.height;
	int wOffset = start.width - stop.width;

	int hAdder = (hOffset != 0) ? (-hOffset / abs(hOffset)) : 0;
	int wAdder = (wOffset != 0) ? (-wOffset / abs(wOffset)) : 0;

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
	int hOffset = start.height - stop.height;
	int wOffset = start.width - stop.width;

	int hAdder = (hOffset != 0) ? (-hOffset / abs(hOffset)) : 0;
	int wAdder = (wOffset != 0) ? (-wOffset / abs(wOffset)) : 0;

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

bool move_chess_piece(Board board, Point start, Point stop)
{
	if(!point_inside_bounds(start.height, start.width)) return false;
	if(!point_inside_bounds(stop.height, stop.width)) return false;

	if(board_points_equal(start, stop)) return false;

	Piece piece = board[start.height][start.width];

	switch(piece.type)
	{
		case(NONE): return false;

		case(PAWN):
			if(!execute_pawn_move(board, start, stop)) return false;
			break;

		case(ROOK):
			if(!execute_rook_move(board, start, stop)) return false;
			break;

		case(KNIGHT):
			if(!execute_knight_move(board, start, stop)) return false;
			break;

		case(BISHOP):
			if(!execute_bishop_move(board, start, stop)) return false;
			break;

		case(QUEEN):
			if(!execute_queen_move(board, start, stop)) return false;
			break;

		case(KING):
			if(!execute_king_move(board, start, stop)) return false;
			break;
	}
	return true;
}

bool board_points_equal(Point first, Point second)
{
	bool height = first.height == second.height;
	bool width = first.width == second.width;
	return (height && width);
}

void switch_chess_pieces(Board board, Point first, Point second)
{
	Piece temporary = board[first.height][first.width];
	board[first.height][first.width] = board[second.height][second.width];
	board[second.height][second.width] = temporary;
}

bool moving_pawn_valid(Board board, Point start, Point stop)
{
	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	bool straight = (start.width == stop.width);

	bool starting = (start.height == 1 || start.height == 6);

	if(straight && hSteps == 1) return true;

	if(straight && starting && hSteps == 2) return true;

	if(hSteps == 1 && wSteps == 1) return true;

	return false;
}

bool execute_pawn_move(Board board, Point start, Point stop)
{
	if(!moving_pawn_valid(board, start, stop)) return false;

	bool straight = (start.width == stop.width);
	int hSteps = (start.height - stop.height);

	if(straight)
	{
		if(!board_piece_empty(board, stop.height, stop.width)) return false;
		if(!clear_moving_path(board, start, stop)) return false;
	}
	else // Taking a piece!
	{
		if(team_board_piece(board, start, stop)) return false;
		
		check_remove_piece(board, start, stop);
	}

	switch_chess_pieces(board, start, stop);

	return true;
}

bool moving_rook_valid(Board board, Point start, Point stop)
{
	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	return (hSteps == 0) || (wSteps == 0);
}

bool rook_king_switch(Board board, Point start, Point stop)
{
	bool start_h = (start.height == 0) || (start.height == 7);
	bool start_w = (start.width == 0) || (start.width == 7);
	bool rook_start = (start_h && start_w);

	bool stop_h = (stop.height == 0) || (stop.height == 7);
	bool stop_w = (stop.width == 4);
	bool king_start = (stop_h && stop_w);

	bool king = board[stop.height][stop.width].type == KING;

	return (rook_start && king_start && king);
}

bool execute_rook_move(Board board, Point start, Point stop)
{
	if(!moving_rook_valid(board, start, stop)) return false;

	if(!clear_straight_path(board, start, stop)) return false;

	if(!rook_king_switch(board, start, stop))
	{
		if(team_board_piece(board, start, stop)) return false;

		check_remove_piece(board, start, stop);
	}

	switch_chess_pieces(board, start, stop);

	return true;
}

bool moving_knight_valid(Board board, Point start, Point stop)
{
	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	if(hSteps == 1 && wSteps == 2) return true;

	if(hSteps == 2 && wSteps == 1) return true;

	return false;
}

bool execute_knight_move(Board board, Point start, Point stop)
{
	if(!moving_knight_valid(board, start, stop)) return false;

	if(team_board_piece(board, start, stop)) return false;

	check_remove_piece(board, start, stop);

	switch_chess_pieces(board, start, stop);

	return true;
}

bool moving_bishop_valid(Board board, Point start, Point stop)
{
	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	return (hSteps == wSteps);
}

bool execute_bishop_move(Board board, Point start, Point stop)
{
	if(!moving_bishop_valid(board, start, stop)) return false;

	if(team_board_piece(board, start, stop)) return false;

	if(!clear_diagonal_path(board, start, stop)) return false;

	check_remove_piece(board, start, stop);

	switch_chess_pieces(board, start, stop);

	return true;
}

bool moving_queen_valid(Board board, Point start, Point stop)
{
	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	bool diagonal = (hSteps == wSteps);
	bool straight = (hSteps == 0) || (wSteps == 0);

	return (diagonal || straight);
}

bool execute_queen_move(Board board, Point start, Point stop)
{
	if(!moving_queen_valid(board, start, stop)) return false;

	if(team_board_piece(board, start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	check_remove_piece(board, start, stop);

	switch_chess_pieces(board, start, stop);

	return true;
}

bool moving_king_valid(Board board, Point start, Point stop)
{
	int hSteps = abs(start.height - stop.height);
	int wSteps = abs(start.width - stop.width);

	return (hSteps <= 1) && (wSteps <= 1);
}

bool execute_king_move(Board board, Point start, Point stop)
{
	if(!moving_king_valid(board, start, stop)) return false;

	if(team_board_piece(board, start, stop)) return false;

	check_remove_piece(board, start, stop);

	switch_chess_pieces(board, start, stop);

	return true;
}
