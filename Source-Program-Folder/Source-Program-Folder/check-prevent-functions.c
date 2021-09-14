
#include "../Header-Program-Folder/global-include-header.h"

bool team_prevent_check(Board board, Info info, Team team)
{
	if(team == NONE) return false;

	Point point; Team currTeam;
	for(int height = 0; height < B_HEIGHT; height = height + 1)
	{
		for(int width = 0; width < B_WIDTH; width = width + 1)
		{
			point = (Point) {height, width};
			currTeam = board_point_team(board, point);

			// This function is only going to check for
			// the team that is inputted
			if(currTeam != team) continue;

			// The code after this is the actual check-code:

			if(piece_prevent_check(board, point, info)) return true;
		}
	}
	return false;
}

/*
Optimize this function so that it only checks the squares that
the piece is accepted to be on: one function for every piece
with a switch case in this function.
*/
bool piece_prevent_check(Board board, Point start, Info info)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	switch(board_point_type(board, start))
	{
		case(EMPTY): return false;

		case(PAWN): return pawn_prevent_check(board, info, start);

		case(ROOK): return pawn_prevent_check(board, info, start);

		case(KNIGHT): return pawn_prevent_check(board, info, start);

		case(BISHOP): return pawn_prevent_check(board, info, start);

		case(QUEEN): return pawn_prevent_check(board, info, start);

		case(KING): return pawn_prevent_check(board, info, start);
	}
	return false;
}

bool pawn_prevent_check(Board board, Info info, Point start)
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

			if(!pawn_move_acceptable(board, currMove, info)) continue;

			if(move_prevent_check(board, currMove, info)) return true;
		}
	}
	return false;
}

bool rook_prevent_check(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	Point stop; Move currMove;

	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		stop = (Point) {height, start.width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(!rook_move_acceptable(board, currMove, info)) continue;

		if(move_prevent_check(board, currMove, info)) return true;
	}

	for(int width = 0; width < B_WIDTH; width += 1)
	{
		stop = (Point) {start.height, width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(!rook_move_acceptable(board, currMove, info)) continue;

		if(move_prevent_check(board, currMove, info)) return true;
	}

	return false;
}

bool knight_prevent_check(Board board, Info info, Point start)
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

			if(!knight_move_acceptable(board, currMove, info)) continue;

			if(move_prevent_check(board, currMove, info)) return true;
		}
	}
	return false;
}

bool bishop_prevent_check(Board board, Info info, Point start)
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

		if(!bishop_move_acceptable(board, currMove, info)) continue;

		if(move_prevent_check(board, currMove, info)) return true;
	}

	for(int index = -8; index <= 16; index = index + 1)
	{
		height = (start.height + index);
		width = (start.width - index);

		stop = (Point) {height, width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(!bishop_move_acceptable(board, currMove, info)) continue;

		if(move_prevent_check(board, currMove, info)) return true;
	}
	return false;
}

bool diagonal_prevent_check(Board board, Info info, Point start)
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

		if(!diagonal_move_acceptable(board, currMove, info)) continue;

		if(move_prevent_check(board, currMove, info)) return true;
	}

	for(int index = -8; index <= 16; index = index + 1)
	{
		height = (start.height + index);
		width = (start.width - index);

		stop = (Point) {height, width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(!diagonal_move_acceptable(board, currMove, info)) continue;

		if(move_prevent_check(board, currMove, info)) return true;
	}
	return false;
}

bool straight_prevent_check(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	Point stop; Move currMove;

	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		stop = (Point) {height, start.width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(!straight_move_acceptable(board, currMove, info)) continue;

		if(move_prevent_check(board, currMove, info)) return true;
	}

	for(int width = 0; width < B_WIDTH; width += 1)
	{
		stop = (Point) {start.height, width};

		if(!point_inside_board(stop)) continue;

		currMove = (Move) {start, stop};

		if(!straight_move_acceptable(board, currMove, info)) continue;

		if(move_prevent_check(board, currMove, info)) return true;
	}
	return false;
}

bool queen_prevent_check(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;
	
	if(board_point_empty(board, start)) return false;

	if(diagonal_prevent_check(board, info, start)) return true;

	if(straight_prevent_check(board, info, start)) return true;

	return false;
}

bool king_prevent_check(Board board, Info info, Point start)
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

			if(!king_move_acceptable(board, currMove, info)) continue;

			if(move_prevent_check(board, currMove, info)) return true;
		}
	}
	return false;
}

bool move_prevent_check(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!move_inside_board(move)) return false;

	Piece piece = board_point_piece(board, start);
	if(board_point_empty(board, start)) return false;

	Board boardCopy = copy_chess_board(board);
	move_board_piece(boardCopy, start, stop);

	Point king = team_king_point(info, piece.team);
	if(piece.type == KING) king = stop;

	if(!king_inside_check(boardCopy, king))
	{
		free_chess_board(boardCopy); return true;
	}

	free_chess_board(boardCopy); return false;
}
