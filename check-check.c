
#include "header.h"

bool check_draw_situation(Board board, int height, int width)
{
	if(board[height][width].type != KING) return false;

	if(king_is_moveable(board, height, width)) return false;

	return false; // True
}

bool check_mate_situation(Board board, int height, int width)
{
	if(board[height][width].type != KING) return false;

	if(!check_draw_situation(board, height, width)) return false;

	if(!king_check_situation(board, height, width)) return false;

	return true;
}

bool king_is_moveable(Board board, int height, int width)
{
	if(board[height][width].type != KING) return false;

	Point start = {height, width}, stop;
	for(int hIndex = 0; hIndex < 3; hIndex = hIndex + 1)
	{
		for(int wIndex = 0; wIndex < 3; wIndex = wIndex + 1)
		{
			if(hIndex == height && wIndex == width) continue;

			int rHeight = (height - 1) + hIndex;
			int rWidth = (width - 1) + wIndex;

			if(!point_inside_bounds(rHeight, rWidth)) continue;

			stop = (Point) {rHeight, rWidth};
			if(chess_team_point(board, start, stop)) continue;

			if(!king_check_situation(board, rHeight, rWidth)) return true;
		}
	}
	return false;
}

bool king_check_situation(Board board, int height, int width)
{
	if(board[height][width].type != KING) return true;

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
		for(int round = 0; round < 2; round = round + 1);
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