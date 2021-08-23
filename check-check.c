
#include "header.h"

bool check_draw_situation(Board board, int height, int width)
{
	if(board[height][width].type != KING) return false;

	if(king_is_moveable(board, height, width)) return false;

	printf("King is not movable!\n");

	return true; // True
}

bool check_mate_situation(Board board, int height, int width)
{
	if(board[height][width].type != KING) return false;

	if(!check_draw_situation(board, height, width)) return false;

	if(!king_check_situation(board, height, width)) return false;

	return true;
}

Board copy_chess_board(Board board)
{
	Board copy = malloc(sizeof(Piece*) * 8);
	for(int height = 0; height < 8; height = height + 1)
	{
		copy[height] = malloc(sizeof(Piece) * 8);
		for(int width = 0; width < 8; width = width + 1)
		{
			copy[height][width].type = board[height][width].type;
			copy[height][width].color = board[height][width].color;
		}
	}
	return copy;
}

bool simulate_check_move(Board copy, Point point, Color color)
{
	int height = point.height, width = point.width;

	if(!point_inside_bounds(height, width)) return false;

	if(copy[height][width].color == color) return false;

	allocate_board_piece(copy, point, KING, color);

	if(!king_check_situation(copy, height, width)) return true;

	remove_board_piece(copy, height, width);

	return false;
}

bool king_is_moveable(Board board, int height, int width)
{
	Board copy = copy_chess_board(board);
	remove_board_piece(copy, height, width);

	Color color = board[height][width].color;
	Point start = {height, width}, stop;

	for(int hIndex = 0; hIndex < 3; hIndex = hIndex + 1)
	{
		for(int wIndex = 0; wIndex < 3; wIndex = wIndex + 1)
		{
			int rHeight = (height - 1) + hIndex;
			int rWidth = (width - 1) + wIndex;

			stop = (Point) {rHeight, rWidth};

			if(board_points_equal(start, stop)) continue;

			if(simulate_check_move(copy, stop, color))
			{
				free(copy); return true;
			}
		}
	}
	free(copy); return false;
}

bool king_check_situation(Board board, int height, int width)
{
	if(check_knight_check(board, height, width)) return true;

	if(check_pawn_check(board, height, width)) return true;

	if(check_diagonal_check(board, height, width)) return true;

	if(check_straight_check(board, height, width)) return true;

	return false;
}

bool check_pawn_check(Board board, int height, int width)
{
	Color color = board[height][width].color;
	int hIndex = (color == WHITE) ? (height - 1) : (height + 1);

	Point start = {height, width};
	Point stop;

	for(int index = -1; index != 3; index = index + 2)
	{
		int wIndex = (width + index);
		stop = (Point) {hIndex, wIndex};

		if(!point_inside_bounds(hIndex, wIndex)) continue;

		if(!chess_enemy_point(board, start, stop)) continue;

		if(board[hIndex][wIndex].type == PAWN) return true;
	}
	return false;
}

bool check_knight_check(Board board, int height, int width)
{
	Point start = {height, width}, stop;
	for(int hIndex = 0; hIndex < 5; hIndex = hIndex + 1)
	{
		for(int wIndex = 0; wIndex < 5; wIndex = wIndex + 1)
		{
			if(hIndex == wIndex || (hIndex + wIndex) == 4) continue;
			if(hIndex == 2 || wIndex == 2) continue;

			int rHeight = (height - 2) + hIndex;
			int rWidth = (width - 2) + wIndex;

			if(!point_inside_bounds(rHeight, rWidth)) continue;

			stop = (Point) {rHeight, rWidth};
			if(!chess_enemy_point(board, start, stop)) continue;

			if(board[rHeight][rWidth].type == KNIGHT) return true;
		}
	}
	return false;
}

bool check_diagonal_check(Board board, int height, int width)
{
	Type type;
	Point start = {height, width}, stop;
	for(int index = -8; index <= 16; index = index + 1)
	{
		for(int round = 0; round < 2; round = round + 1)
		{
			int hIndex = (index + height);
			int wIndex = (round == 0) ? (index + width) : (width - index);

			if(!point_inside_bounds(hIndex, wIndex)) continue;

			stop = (Point) {hIndex, wIndex};
			if(!chess_enemy_point(board, start, stop)) continue;

			if(!clear_straight_path(board, start, stop)) continue;

			type = board[hIndex][wIndex].type;
			if(type == BISHOP || type == QUEEN) return true;
		}
	}
	return false;
}

bool check_straight_check(Board board, int height, int width)
{
	Type type;
	Point start = {height, width}, stop;
	for(int index = 0; index < 8; index = index + 1)
	{
		for(int round = 0; round < 2; round = round + 1)
		{
			int hIndex = (round == 0) ? height : index;
			int wIndex = (round == 0) ? index : width;

			stop = (Point) {hIndex, wIndex};
			if(!chess_enemy_point(board, start, stop)) continue;

			if(!clear_straight_path(board, start, stop)) continue;

			type = board[hIndex][wIndex].type;
			if(type == ROOK || type == QUEEN) return true;
		}
	}
	return false;
}