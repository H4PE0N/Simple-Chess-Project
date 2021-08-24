
#include "header.h"

bool team_prevent_check(Board board, Info* info, Color color)
{
	Point point; Piece piece;
	for(int height = 0; height < 8; height = height + 1)
	{
		for(int width = 0; width < 8; width = width + 1)
		{
			point = (Point) {height, width};
			piece = board[height][width];

			if(piece.color != color) continue;

			if(piece_prevent_check(board, point, info)) return true;
		}
	}
	return false;
}

bool piece_prevent_check(Board board, Point point, Info* info)
{
	Piece piece = board[point.height][point.width];

	if(piece.color == NONE) return false;

	if(!point_inside_bounds(point.height, point.width)) return false;

	printf("Can (T=%d C=%d) at (%d-%d) prevent check?\n",
		piece.type, piece.color, point.height, point.width);

	switch(piece.type)
	{
		case(EMPTY): return false;

		case(PAWN):
			if(pawn_prevent_check(board, point, info)) return true;
			break;

		case(ROOK):
			if(rook_prevent_check(board, point, info)) return true;
			break;

		case(KNIGHT):
			if(knight_prevent_check(board, point, info)) return true;
			break;

		case(BISHOP):
			if(bishop_prevent_check(board, point, info)) return true;
			break;

		case(QUEEN):
			if(queen_prevent_check(board, point, info)) return true;
			break;

		case(KING):
			return false;
			break;
	}

	return false;
}

bool pawn_prevent_check(Board board, Point start, Info* info)
{
	Color color = board[start.height][start.width].color;
	Point stop; Move move;
	for(int height = 2; height > 0; height = height - 1)
	{
		for(int width = 0; width < 3; width = width + 1)
		{
			int rHeight = (color == WHITE) ? (start.height - height) : (start.height + height);
			int rWidth = (start.width - 1) + width;

			stop = (Point) {rHeight, rWidth};

			if(!pawn_move_acceptable(board, start, stop)) continue;

			printf("The pawn can move from (%d-%d) to (%d-%d)\n",
				start.height, start.width, stop.height, stop.width);

			move = (Move) {start, stop};

			if(move_prevent_check(board, move, info)) return true;
		}
	}
	return false;
}

bool rook_prevent_check(Board board, Point start, Info* info)
{
	if(straight_prevent_check(board, start, info)) return true;

	return false;
}

bool knight_prevent_check(Board board, Point start, Info* info)
{
	Point stop; Move move;
	for(int height = 0; height < 5; height = height + 1)
	{
		for(int width = 0; width < 5; width = width + 1)
		{
			int rHeight = (start.height - 2) + height;
			int rWidth = (start.width - 2) + width;

			stop = (Point) {rHeight, rWidth};

			if(!knight_move_acceptable(board, start, stop)) continue;

			move = (Move) {start, stop};

			if(move_prevent_check(board, move, info)) return true;
		}
	}
	return false;
}

bool bishop_prevent_check(Board board, Point start, Info* info)
{
	if(diagonal_prevent_check(board, start, info)) return true;

	return false;
}

bool queen_prevent_check(Board board, Point start, Info* info)
{
	if(diagonal_prevent_check(board, start, info)) return true;

	if(straight_prevent_check(board, start, info)) return true;

	return false;
}

bool straight_prevent_check(Board board, Point start, Info* info)
{
	Point stop; Move move;
	for(int index = 0; index < 8; index = index + 1)
	{
		for(int round = 0; round < 2; round = round + 1)
		{
			int height = (round == 0) ? index : start.height;
			int width = (round == 0) ? start.width : index;

			stop = (Point) {height, width};

			if(!straight_move_acceptable(board, start, stop)) continue;

			move = (Move) {start, stop};

			if(move_prevent_check(board, move, info)) return true;
		}
	}
	return false;
}

bool diagonal_prevent_check(Board board, Point start, Info* info)
{
	Point stop; Move move;
	for(int index = -8; index <= 16; index = index + 1)
	{
		for(int round = 0; round < 2; round = round + 1)
		{
			int height = (index + start.height);
			int width = (round == 0) ? (index + start.width) : (start.width - index);

			stop = (Point) {height, width};

			if(!diagonal_move_acceptable(board, start, stop)) continue;

			move = (Move) {start, stop};

			if(move_prevent_check(board, move, info)) return true;
		}
	}
	return false;
}

bool move_prevent_check(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;
	Color color = board[start.height][start.width].color;

	Point king = (color == WHITE) ? info->wKing : info->bKing;

	Board copy = copy_chess_board(board);

	if(!move_board_piece(board, start, stop)) return false;

	if(!king_check_situation(copy, king, color))
	{
		free(copy); return true;
	}

	free(copy); return false;
}