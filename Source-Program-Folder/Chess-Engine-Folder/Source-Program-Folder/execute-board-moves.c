
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
	}
}

void execute_pawn_move(Board board, Move move)
{
	move_board_piece(board, move.start, move.stop);

	make_pawn_queen(board, move.stop);
}

void execute_team_castle(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);
	Castle* RKS = (team == BLACK) ? &info->blackRKS : &info->whiteRKS;

	int difference = (stop.width - start.width);

	int kWidth = (difference < 0) ? 6 : 2;
	int rWidth = (difference < 0) ? 5 : 3;

	Point rook = {start.height, rWidth};
	Point king = {stop.height, kWidth};

	move_board_piece(board, stop, king);
	move_board_piece(board, start, rook);

	update_king_point(info, team, king);

	*RKS = (Castle) {false, false};
}

void execute_rook_move(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);
	Castle* RKS = (team == BLACK) ? &info->blackRKS : &info->whiteRKS;

	move_board_piece(board, start, stop);

	if(start.width == 0) 				RKS->left = false;
	if(start.width == (BOARD_WIDTH - 1))	RKS->right = false;
}

void execute_knight_move(Board board, Move move)
{
	move_board_piece(board, move.start, move.stop);
}

void execute_bishop_move(Board board, Move move)
{
	move_board_piece(board, move.start, move.stop);
}

void execute_queen_move(Board board, Move move)
{
	move_board_piece(board, move.start, move.stop);
}

void turn_off_rook_switch(Info* info, Team team)
{
	Castle* RKS = (team == WHITE) ? &info->whiteRKS : &info->blackRKS;
	*RKS = (Castle) {false, false};
}

void update_king_point(Info* info, Team team, Point point)
{
	Point* kingP = (team == WHITE) ? &info->whiteKing : &info->blackKing;
	*kingP = (Point) {point.height, point.width};
}

void execute_king_move(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);

	turn_off_rook_switch(info, team);
	update_king_point(info, team, stop);

	move_board_piece(board, start, stop);
}

void make_pawn_queen(Board board, Point point)
{
	Team team = board_point_team(board, point);

	bool whiteQueen = (team == WHITE && point.height == 0);
	bool blackQueen = (team == BLACK && point.height == (BOARD_HEIGHT - 1));

	if(whiteQueen || blackQueen)
	{
		board[point.height][point.width].type = QUEEN;
	}
}
