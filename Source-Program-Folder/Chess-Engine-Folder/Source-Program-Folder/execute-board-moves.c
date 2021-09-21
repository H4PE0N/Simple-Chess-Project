
#include "../Header-Program-Folder/chess-engine-includer.h"

bool execute_piece_move(Board board, Move move, Info* info)
{
	if(!move_inside_board(move)) return false;

	switch(board_point_type(board, move.start))
	{
		case(EMPTY): return false;

		case(PAWN): return execute_pawn_move(board, move);

		case(ROOK): return execute_rook_move(board, move, info);

		case(KNIGHT): return execute_knight_move(board, move);

		case(BISHOP): return execute_bishop_move(board, move);

		case(QUEEN): return execute_queen_move(board, move);

		case(KING): return execute_king_move(board, move, info);

		default: return false;
	}
	return false;
}

bool execute_pawn_move(Board board, Move move)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	Team team = board_point_team(board, move.start);
	if(!piece_team_exists(team)) return false;

	move_board_piece(board, move.start, move.stop);

	if(pawn_becomes_queen(move.stop, team))
	{
		allocate_board_piece(board, move.stop, (Piece) {QUEEN, team});
	}

	return true;
}

bool execute_team_castle(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	Point rook = move.start, king = move.stop;

	Team team = board_point_team(board, rook);
	if(!piece_team_exists(team)) return false;

	Point castleRook, castleKing;
	if(!extract_castle_points(&castleRook, &castleKing, rook, king, team))
	{
		return false;
	}

	move_board_piece(board, king, castleKing);
	move_board_piece(board, rook, castleRook);

	update_castles_values(&info->castles, team, EMPTY_CASTLE);

	return true;
}

bool extract_castle_points(Point* castleRook, Point* castleKing, Point rook, Point king, Team team)
{
	if(!team_castle_valid(rook, king, team)) return false;

	if(rook.width == 0)
	{
		*castleRook = (Point) {rook.height, king.width - 1};
		*castleKing = (Point) {king.height, king.width - 2};

		return true;
	}

	if(rook.width == (BOARD_WIDTH - 1))
	{
		*castleRook = (Point) {rook.height, king.width + 1};
		*castleKing = (Point) {king.height, king.width + 2};

		return true;
	}

	return false;
}

bool execute_rook_move(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);
	// The rook needs to be in a team to change the castle value
	if(!piece_team_exists(team)) return false;

	Side side = rook_starting_side(start.width);

	move_board_piece(board, start, stop);

	update_castles_value(&info->castles, team, side, false);

	return true;
}

bool execute_knight_move(Board board, Move move)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	move_board_piece(board, move.start, move.stop);

	return true;
}

bool execute_bishop_move(Board board, Move move)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	move_board_piece(board, move.start, move.stop);

	return true;
}

bool execute_queen_move(Board board, Move move)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	move_board_piece(board, move.start, move.stop);

	return true;
}

// void turn_off_rook_switch(Info* info, Team team)
// {
// 	Castle* RKS = (team == WHITE) ? &info->whiteRKS : &info->blackRKS;
// 	*RKS = (Castle) {false, false};
// }

// void update_king_point(Info* info, Team team, Point point)
// {
// 	Point* kingP = (team == WHITE) ? &info->whiteKing : &info->blackKing;
// 	*kingP = (Point) {point.height, point.width};
// }

bool execute_king_move(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);

	if(!piece_team_exists(team)) return false;


	move_board_piece(board, start, stop);

	update_castles_values(&info->castles, team, EMPTY_CASTLE);

	return true;
}

bool pawn_becomes_queen(Point point, Team team)
{
	// If the point is not inside the board:
	if(!point_inside_board(point)) return false;

	if(!piece_team_exists(team)) return false;

	if(team == WHITE && point.height == 0) return true;
	if(team == BLACK && point.height == (BOARD_HEIGHT - 1)) return true;

	return false;
}
