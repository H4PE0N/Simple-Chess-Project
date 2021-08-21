
#include "header.h"

bool clear_moving_path(Board board, Point start, Point stop)
{
	//if(moving_knight_valid(board, start, stop)) return true;

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

	else if(straight)
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

	for(int index = 0; index < abs(hOffset); index = index + 1)
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
		for(int height = 1; height <= abs(hOffset); height = height + 1)
		{
			int hIndex = start.height + (height * hAdder);
			if(board[hIndex][start.width].type != EMPTY) return false;
		}
	}
	else if(hOffset == 0)
	{
		for(int width = 1; width <= abs(wOffset); width += 1)
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
		printf("PAWN!\n");
		if(!execute_pawn_move(board, start, stop)) return false;
		break;

		case(ROOK):
		printf("ROOK!\n");
		if(!execute_rook_move(board, start, stop)) return false;
		break;

		case(KNIGHT):
		printf("KNIGHT!\n");
		if(!execute_knight_move(board, start, stop)) return false;
		break;

		case(BISHOP):
		printf("BISHOP!\n");
		if(!execute_bishop_move(board, start, stop)) return false;
		break;

		case(QUEEN):
		printf("QUEEN!\n");
		if(!execute_queen_move(board, start, stop)) return false;
		break;

		case(KING):
		printf("KING!\n");
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

		switch_chess_pieces(board, start, stop);
	}
	else // Taking a piece!
	{
		Color start_c = board[start.height][start.width].color;
		Color stop_c = board[stop.height][stop.width].color;

		if(stop_c == NONE || stop_c == start_c) return false;
		
		remove_board_piece(board, stop.height, stop.width);
		switch_chess_pieces(board, start, stop);
	}
	return true;
}

bool execute_rook_move(Board board, Point start, Point stop)
{
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
	return true;
}

bool execute_bishop_move(Board board, Point start, Point stop)
{
	return true;
}

bool execute_queen_move(Board board, Point start, Point stop)
{
	return true;
}

bool execute_king_move(Board board, Point start, Point stop)
{
	return true;
}
