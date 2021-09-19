
#include "../Header-Program-Folder/chess-engine-includer.h"

void execute_piece_move(Board board, Move move, Info* info)
{
	if(!move_inside_board(move)) return;

	switch(board_point_type(board, move.start))
	{
		case(EMPTY): break;

		case(PAWN): execute_pawn_move(board, move); break;

		case(ROOK): execute_rook_move(board, move, info); break;

		case(KNIGHT): execute_knight_move(board, move); break;

		case(BISHOP): execute_bishop_move(board, move); break;

		case(QUEEN): execute_queen_move(board, move); break;

		case(KING): execute_king_move(board, move, info); break;

		default: break;
	}
}

void execute_pawn_move(Board board, Move move)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return;

	move_board_piece(board, move.start, move.stop);

	make_pawn_queen(board, move.stop);
}

void execute_team_castle(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return;

	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);

	int difference = (stop.width - start.width);

	int kingWidth = (difference < 0) ? 6 : 2;
	int rookWidth = (difference < 0) ? 5 : 3;

	Point rook = {start.height, rookWidth};
	Point king = {stop.height, kingWidth};

	move_board_piece(board, stop, king);
	move_board_piece(board, start, rook);

	update_castles_values(&info->castles, team, (Castle) {false, false});
}

void execute_rook_move(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return;

	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);

	move_board_piece(board, start, stop);

	Side side = rook_starting_side(start.width);

	update_castles_value(&info->castles, team, side, false);
}

void execute_knight_move(Board board, Move move)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return;

	move_board_piece(board, move.start, move.stop);
}

void execute_bishop_move(Board board, Move move)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return;

	move_board_piece(board, move.start, move.stop);
}

void execute_queen_move(Board board, Move move)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return;

	move_board_piece(board, move.start, move.stop);
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

void execute_king_move(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return;

	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);

	move_board_piece(board, start, stop);

	update_castles_values(&info->castles, team, (Castle) {false, false});
}

void make_pawn_queen(Board board, Point point)
{
	// If the point is not inside the board:
	if(!point_inside_board(point)) return;

	Team team = board_point_team(board, point);

	// If the team does not exists:
	if(!piece_team_exists(team)) return;

	bool whiteQueen = (team == WHITE && point.height == 0);
	bool blackQueen = (team == BLACK && point.height == (BOARD_HEIGHT - 1));

	if(whiteQueen || blackQueen)
	{
		allocate_board_piece(board, point, (Piece) {QUEEN, team});
	}
}
