
#include "../Header-Program-Folder/chess-engine-includer.h"

bool board_piece_moveable(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	switch(board_point_type(board, start))
	{
		case(EMPTY): return false;

		case(PAWN): return board_pawn_moveable(board, info, start);

		case(ROOK): return board_rook_moveable(board, info, start);

		case(KNIGHT): return board_knight_moveable(board, info, start);

		case(BISHOP): return board_bishop_moveable(board, info, start);

		case(QUEEN): return board_queen_moveable(board, info, start);

		case(KING): return board_king_moveable(board, info, start);
	}
	return false;
}

bool board_pawn_moveable(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	Team team = board_point_team(board, start);

	if(team == NONE) return false;

	Point stop; Move currMove;

	int realHeight, realWidth;

	for(int height = 0; height < 2; height += 1)
	{
		for(int width = 0; width < 3; width += 1)
		{
			// This is the squares that the pawn cant move on.
			// This check is not needed because the "accept" function
			// but its nice just to check simple before.
			if(height == 2 && (width == 0 || width == 2) ) continue;

			realHeight = (team == WHITE) ? (start.height - (height + 1) ) : (start.height + (height + 1) );
			realWidth = (start.width - 1) + width;

			stop = (Point) {realHeight, realWidth};

			if(!point_inside_board(stop)) continue;

			currMove = (Move) {start, stop};

			if(pawn_move_acceptable(board, currMove, info)) return true;
		}
	}
	return false;
}

bool board_rook_moveable(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	Point stop; Move currMove;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		stop = (Point) {height, start.width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(rook_move_acceptable(board, currMove, info)) return true;
	}

	for(int width = 0; width < BOARD_WIDTH; width += 1)
	{
		stop = (Point) {start.height, width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(rook_move_acceptable(board, currMove, info)) return true;
	}

	return false;
}

bool board_knight_moveable(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	Point stop; Move currMove;

	int realHeight, realWidth;

	for(int height = 0; height < 5; height = height + 1)
	{
		for(int width = 0; width < 5; width = width + 1)
		{
			// This is the squares that the knight cant move on.
			// This check is not needed because the "accept" function
			// but its nice just to check simple before.
			if(height == width || (height + width) == 4) continue;
			if(height == 2 || width == 2) continue;

			realHeight = (start.height - 2) + height;
			realWidth = (start.width - 2) + width;

			stop = (Point) {realHeight, realWidth};

			if(!point_inside_board(stop)) continue;

			currMove = (Move) {start, stop};

			if(knight_move_acceptable(board, currMove, info)) return true;
		}
	}
	return false;
}

bool board_diagonal_moveable(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	Point stop; Move currMove;

	int height, width;

	for(int index = -8; index <= 16; index = index + 1)
	{
		height = (start.height + index);
		width = (start.width + index);

		stop = (Point) {height, width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(diagonal_move_acceptable(board, currMove, info)) return true;
	}

	for(int index = -8; index <= 16; index = index + 1)
	{
		height = (start.height + index);
		width = (start.width - index);

		stop = (Point) {height, width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(diagonal_move_acceptable(board, currMove, info)) return true;
	}
	return false;
}

bool board_straight_moveable(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	Point stop; Move currMove;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		stop = (Point) {height, start.width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(straight_move_acceptable(board, currMove, info)) return true;
	}

	for(int width = 0; width < BOARD_WIDTH; width += 1)
	{
		stop = (Point) {start.height, width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(straight_move_acceptable(board, currMove, info)) return true;
	}
	return false;
}

bool board_bishop_moveable(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	Point stop; Move currMove;

	int height, width;

	for(int index = -8; index <= 16; index = index + 1)
	{
		height = (start.height + index);
		width = (start.width + index);

		stop = (Point) {height, width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(bishop_move_acceptable(board, currMove, info)) return true;
	}

	for(int index = -8; index <= 16; index = index + 1)
	{
		height = (start.height + index);
		width = (start.width - index);

		stop = (Point) {height, width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(bishop_move_acceptable(board, currMove, info)) return true;
	}
	return false;
}

bool board_queen_moveable(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_diagonal_moveable(board, info, start)) return true;

	if(board_straight_moveable(board, info, start)) return true;

	return false;
}

bool board_king_moveable(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	Point stop; Move currMove;

	int realHeight, realWidth;

	for(int height = 0; height < 3; height += 1)
	{
		for(int width = 0; width < 3; width += 1)
		{
			realHeight  = (start.height - 1) + height;
			realWidth = (start.width - 1) + width;

			stop = (Point) {realHeight, realWidth};

			if(!point_inside_board(stop)) continue;

			currMove = (Move) {start, stop};

			if(king_move_acceptable(board, currMove, info)) return true;
		}
	}
	return false;
}
