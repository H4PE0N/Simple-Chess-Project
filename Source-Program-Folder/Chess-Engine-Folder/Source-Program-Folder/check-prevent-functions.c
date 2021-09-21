
#include "../Header-Program-Folder/chess-engine-includer.h"

bool team_prevent_check(Board board, Info info, Team team)
{
	if(!piece_team_exists(team)) return false;

	Point point;
	Team currentTeam;

	for(int height = 0; height < BOARD_HEIGHT; height = height + 1)
	{
		for(int width = 0; width < BOARD_WIDTH; width = width + 1)
		{
			point = (Point) {height, width};
			currentTeam = board_point_team(board, point);

			if(currentTeam != team) continue;

			if(piece_prevent_check(board, point, info)) return true;
		}
	}
	return false;
}

bool piece_prevent_check(Board board, Point start, Info info)
{
	if(!point_inside_board(start)) return false;

	switch(board_point_type(board, start))
	{
		case(EMPTY): return false;

		case(PAWN): return pawn_prevent_check(board, info, start);

		case(ROOK): return rook_prevent_check(board, info, start);

		case(KNIGHT): return knight_prevent_check(board, info, start);

		case(BISHOP): return bishop_prevent_check(board, info, start);

		case(QUEEN): return queen_prevent_check(board, info, start);

		case(KING): return king_prevent_check(board, info, start);

		default: return false;
	}
	return false;
}

bool pawn_prevent_check(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_point_type(board, start) != PAWN) return false;


	Team team = board_point_team(board, start);

	Point stop;
	Move currentMove;

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

			currentMove = (Move) {start, stop};

			if(!pawn_acceptable_handler(board, currentMove, info)) continue;

			if(move_prevent_check(board, currentMove, info)) return true;
		}
	}
	return false;
}

bool rook_prevent_check(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_point_type(board, start) != ROOK) return false;


	Point stop;
	Move currentMove;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		stop = (Point) {height, start.width};

		if(!point_inside_board(stop)) continue;

		currentMove = (Move) {start, stop};

		if(!rook_acceptable_handler(board, currentMove, info)) continue;

		if(move_prevent_check(board, currentMove, info)) return true;
	}

	for(int width = 0; width < BOARD_WIDTH; width += 1)
	{
		stop = (Point) {start.height, width};

		if(!point_inside_board(stop)) continue;

		currentMove = (Move) {start, stop};

		if(!rook_acceptable_handler(board, currentMove, info)) continue;

		if(move_prevent_check(board, currentMove, info)) return true;
	}

	return false;
}

bool knight_prevent_check(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_point_type(board, start) != KNIGHT) return false;


	Point stop;
	Move currentMove;

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

			currentMove = (Move) {start, stop};

			if(!knight_acceptable_handler(board, currentMove, info)) continue;

			if(move_prevent_check(board, currentMove, info)) return true;
		}
	}
	return false;
}

bool bishop_prevent_check(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_point_type(board, start) != BISHOP) return false;


	Point stop;
	Move currentMove;

	int height, width;

	for(int index = -8; index <= 16; index = index + 1)
	{
		height = (start.height + index);
		width = (start.width + index);

		stop = (Point) {height, width};

		if(!point_inside_board(stop)) continue;

		currentMove = (Move) {start, stop};

		if(!bishop_acceptable_handler(board, currentMove, info)) continue;

		if(move_prevent_check(board, currentMove, info)) return true;
	}

	for(int index = -8; index <= 16; index = index + 1)
	{
		height = (start.height + index);
		width = (start.width - index);

		stop = (Point) {height, width};

		if(!point_inside_board(stop)) continue;

		currentMove = (Move) {start, stop};

		if(!bishop_acceptable_handler(board, currentMove, info)) continue;

		if(move_prevent_check(board, currentMove, info)) return true;
	}
	return false;
}

bool diagonal_prevent_check(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	Point stop;
	Move currentMove;

	int height, width;

	for(int index = -8; index <= 16; index = index + 1)
	{
		height = (start.height + index);
		width = (start.width + index);

		stop = (Point) {height, width};

		if(!point_inside_board(stop)) continue;

		currentMove = (Move) {start, stop};

		if(!diagonal_acceptable_handler(board, currentMove, info)) continue;

		if(move_prevent_check(board, currentMove, info)) return true;
	}

	for(int index = -8; index <= 16; index = index + 1)
	{
		height = (start.height + index);
		width = (start.width - index);

		stop = (Point) {height, width};

		if(!point_inside_board(stop)) continue;

		currentMove = (Move) {start, stop};

		if(!diagonal_acceptable_handler(board, currentMove, info)) continue;

		if(move_prevent_check(board, currentMove, info)) return true;
	}
	return false;
}

bool straight_prevent_check(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	Point stop;
	Move currentMove;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		stop = (Point) {height, start.width};

		if(!point_inside_board(stop)) continue;

		currentMove = (Move) {start, stop};

		if(!straight_acceptable_handler(board, currentMove, info)) continue;

		if(move_prevent_check(board, currentMove, info)) return true;
	}

	for(int width = 0; width < BOARD_WIDTH; width += 1)
	{
		stop = (Point) {start.height, width};

		if(!point_inside_board(stop)) continue;

		currentMove = (Move) {start, stop};

		if(!straight_acceptable_handler(board, currentMove, info)) continue;

		if(move_prevent_check(board, currentMove, info)) return true;
	}
	return false;
}

bool queen_prevent_check(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_point_type(board, start) != QUEEN) return false;


	if(diagonal_prevent_check(board, info, start)) return true;

	if(straight_prevent_check(board, info, start)) return true;

	return false;
}

bool king_prevent_check(Board board, Info info, Point start)
{
	if(!point_inside_board(start)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_point_type(board, start) != KING) return false;


	Point stop;
	Move currentMove;

	int realHeight, realWidth;

	for(int height = 0; height < 3; height += 1)
	{
		for(int width = 0; width < 3; width += 1)
		{
			realHeight  = (start.height - 1) + height;
			realWidth = (start.width - 1) + width;

			stop = (Point) {realHeight, realWidth};

			if(!point_inside_board(stop)) continue;

			currentMove = (Move) {start, stop};

			if(!king_acceptable_handler(board, currentMove, info)) continue;

			if(move_prevent_check(board, currentMove, info)) return true;
		}
	}
	return false;
}

bool move_prevent_check(Board board, Move move, Info info)
{
	Point start = move.start;

	if(!move_inside_board(move)) return false;

	if(board_point_empty(board, start)) return false;

	Team team = board_point_team(board, start);

	Board boardCopy = copy_chess_board(board);
	Info dummyInfo = info;

	if(!execute_piece_move(boardCopy, move, &dummyInfo)) return false;

	Point king = board_piece_point(boardCopy, (Piece) {KING, team});
	// If the king cant be found, it must have been taken
	if(!point_inside_board(king)) return false;

	// If the king is not inside check, the move had to have prevented the check
	if(!king_inside_check(boardCopy, king))
	{
		free_chess_board(boardCopy); return true;
	}

	free_chess_board(boardCopy); return false;
}
