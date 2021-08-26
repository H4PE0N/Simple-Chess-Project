
#include "../Header-Program-Folder/chess-pieces-moveable.h"

bool board_piece_moveable(Board board, Piece piece, Point point)
{
	if(piece.color == NONE) return false;

	if(!point_inside_board(point)) return false;

	switch(piece.type)
	{
		case(EMPTY): return false; break;

		case(PAWN):
			if(board_pawn_moveable(board, point)) return true;
			break;

		case(ROOK):
			if(board_rook_moveable(board, point)) return true;
			break;

		case(KNIGHT):
			if(board_knight_moveable(board, point)) return true;
			break;

		case(BISHOP):
			if(board_bishop_moveable(board, point)) return true;
			break;

		case(QUEEN):
			if(board_queen_moveable(board, point)) return true;
			break;

		case(KING):
			if(board_king_moveable(board, point)) return true;
			break;
	}

	return false;
}

bool board_pawn_moveable(Board board, Point start)
{
	Color color = board[start.height][start.width].color;
	Point stop;
	for(int height = 2; height > 0; height = height - 1)
	{
		for(int width = 0; width < 3; width = width + 1)
		{
			int rHeight = (color == WHITE) ? (start.height - height) : (start.height + height);
			int rWidth = (start.width - 1) + width;

			stop = (Point) {rHeight, rWidth};

			if(pawn_move_acceptable(board, start, stop)) return true;
		}
	}
	return false;
}

bool board_rook_moveable(Board board, Point start)
{
	if(straight_move_able(board, start)) return true;

	return false;
}

bool board_knight_moveable(Board board, Point start)
{
	Color color = board[start.height][start.width].color;
	Point stop;
	for(int height = 0; height < 5; height = height + 1)
	{
		for(int width = 0; width < 5; width = width + 1)
		{
			int rHeight = (start.height - 2) + height;
			int rWidth = (start.width - 2) + width;

			stop = (Point) {rHeight, rWidth};

			if(knight_move_acceptable(board, start, stop)) return true;
		}
	}
	return false;
}

bool board_bishop_moveable(Board board, Point start)
{
	if(diagonal_move_able(board, start)) return true;

	return false;
}

bool board_queen_moveable(Board board, Point start)
{
	if(diagonal_move_able(board, start)) return true;

	if(straight_move_able(board, start)) return true;

	return false;
}

bool straight_move_able(Board board, Point start)
{
	Color color = board[start.height][start.width].color;
	Point stop;
	for(int index = 0; index < 8; index = index + 1)
	{
		for(int round = 0; round < 2; round = round + 1)
		{
			int height = (round == 0) ? index : start.height;
			int width = (round == 0) ? start.width : index;

			stop = (Point) {height, width};

			if(straight_move_acceptable(board, start, stop)) return true;
		}
	}
	return false;
}

bool diagonal_move_able(Board board, Point start)
{
	Color color = board[start.height][start.width].color;
	Point stop;
	for(int index = -8; index <= 16; index = index + 1)
	{
		for(int round = 0; round < 2; round = round + 1)
		{
			int height = (index + start.height);
			int width = (round == 0) ? (index + start.width) : (start.width - index);

			stop = (Point) {height, width};

			if(diagonal_move_acceptable(board, start, stop)) return true;
		}
	}
	return false;
}

bool board_king_moveable(Board board, Point start)
{
	Point stop;
	for(int height = 0; height < 3; height = height + 1)
	{
		for(int width = 0; width < 3; width = width + 1)
		{
			int rHeight = (start.height - 1) + height;
			int rWidth = (start.width - 1) + width;

			stop = (Point) {rHeight, rWidth};

			if(king_move_acceptable(board, start, stop)) return true;
		}
	}
	return false;
}