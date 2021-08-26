
#include "../Header-Program-Folder/check-prevent-functions.h"

bool team_prevent_check(Board board, Info* info, Color color)
{
	Point point; Piece piece;
	for(int height = 0; height < 8; height = height + 1)
	{
		for(int width = 0; width < 8; width = width + 1)
		{
			point = (Point) {height, width};
			Color currColor = board_point_color(board, point);

			if(currColor != color) continue;

			if(piece_prevent_check(board, point, info)) return true;
		}
	}
	return false;
}

bool piece_prevent_check(Board board, Point point, Info* info)
{
	Piece piece = board_point_piece(board, point);

	if(piece.color == NONE) return false;

	if(!point_inside_board(point)) return false;

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
			return true;
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

	Piece piece = board_point_piece(board, start);

	if(piece.color == NONE) return false;

	Point king = color_king_point(*info, piece.color);

	Board copy = copy_chess_board(board);
	move_board_piece(copy, start, stop);

	if(piece.type == KING) king = stop;

	if(!king_check_situation(copy, king))
	{
		printf("At (%d-%d) to (%d-%d) prevent check!\n",
			start.height, start.width, stop.height, stop.width);
		
		free(copy); return true;
	}

	free(copy); return false;
}