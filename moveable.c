
#include "header.h"

bool board_piece_moveable(Board board, Piece piece, Point point)
{
	Color color = piece.color;
	if(color == NONE) return false;

	if(!point_inside_bounds(point.height, point.width)) return false;

	switch(piece.type)
	{
		case(NONE): return false;

		case(PAWN):
			if(!board_pawn_moveable(board, point, color)) return true;
			break;

		case(ROOK):
			if(!board_rook_moveable(board, point, color)) return true;
			break;

		case(KNIGHT):
			if(!board_knight_moveable(board, point, color)) return true;
			break;

		case(BISHOP):
			if(!board_bishop_moveable(board, point, color)) return true;
			break;

		case(QUEEN):
			if(!board_queen_moveable(board, point, color)) return true;
			break;

		case(KING):
			if(!board_king_moveable(board, point, color)) return true;
			break;
	}

	return false;
}

bool board_pawn_moveable(Board board, Point start, Color color)
{
	Point stop;
	for(int height = 2; height >= 0; height = height - 1)
	{
		for(int width = 0; width < 3; width = width + 1)
		{
			if(height == 2 && (width == 0 || width == 2)) continue;

			int rHeight = (color == WHITE) ? (start.height - height) : (start.height + height);
			int rWidth = (start.width - 1) + width;

			stop = (Point) {rHeight, rWidth};

			if(!point_inside_bounds(stop.height, stop.width)) continue;

			if(width == 1 && (height == 1 || height == 2)) // Forward
			{
				return path_empty_and_clear(board, start, stop);
			}
			else if(height == 1 && (width == 0 || width == 2)) // Attack!
			{
				Color currColor = board[stop.height][stop.width].color;

				if(currColor != NONE && currColor != color) return true;
			}
		}
	}
	return false;
}

bool board_rook_moveable(Board board, Point start, Color color)
{
	Point stop;
	for(int index = 0; index < 8; index = index + 1)
	{
		for(int round = 0; round < 2; round = round + 1)
		{
			int height = (round == 0) ? index : start.height;
			int width = (round == 0) ? start.width : index;

			stop = (Point) {height, width};
			if(chess_team_point(board, start, stop)) continue;

			if(clear_straight_path(board, start, stop)) return true;
		}
	}
	return false;
}

bool path_empty_and_clear(Board board, Point start, Point stop)
{
	bool empty = board_piece_empty(board, stop.height, stop.width);
	bool clear = clear_moving_path(board, start, stop);

	return (empty && clear);
}

bool board_knight_moveable(Board board, Point start, Color color)
{
	Point stop; Color currColor;
	for(int height = 0; height < 5; height = height + 1)
	{
		for(int width = 0; width < 5; width = width + 1)
		{
			if(height == width || (height + width) == 4) continue;
			if(height == 2 || width == 2) continue;

			int rHeight = (start.height - 2) + height;
			int rWidth = (start.width - 2) + width;

			stop = (Point) {rHeight, rWidth};

			if(!point_inside_bounds(stop.height, stop.width)) continue;

			currColor = board[stop.height][stop.width].color;
			if(currColor != color) return true;
		}
	}
	return false;
}

bool board_bishop_moveable(Board board, Point start, Color color)
{
	return true;
}

bool board_queen_moveable(Board board, Point start, Color color)
{
	return true;
}

bool board_king_moveable(Board board, Point point, Color color)
{
	Point enemy;

	for(int height = 0; height < 3; height = height + 1)
	{
		for(int width = 0; width < 3; width = width + 1)
		{
			int rHeight = (point.height - 1) + height;
			int rWidth = (point.width - 1) + width;

			enemy = (Point) {rHeight, rWidth};

			if(board_points_equal(point, enemy)) continue;

			Move move = {point, enemy};

			if(simulate_check_move(board, move, color))
			{
				return true;
			}
		}
	}
	return false;
}

bool simulate_check_move(Board board, Move move, Color color)
{
	Point start = move.start, stop = move.stop;
	if(!point_inside_bounds(stop.height, stop.width)) return false;

	// The function:
	Board copy = copy_chess_board(board);
	allocate_board_piece(copy, start, KING, color);

	if(chess_team_point(copy, start, stop))
	{
		free(copy); return false;
	}

	remove_board_piece(copy, stop.height, stop.width);
	switch_chess_pieces(copy, start, stop);

	if(!king_check_situation(copy, stop, color))
	{
		free(copy); return true;
	}

	free(copy); return false;
}