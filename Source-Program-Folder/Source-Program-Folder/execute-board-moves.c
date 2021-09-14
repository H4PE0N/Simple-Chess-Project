
#include "../Header-Program-Folder/global-include-header.h"

void execute_pawn_move(Board board, Move move)
{
	move_board_piece(board, move.start, move.stop);

	make_pawn_queen(board, move.stop);
}

void execute_rook_switch(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	Team team = board[start.height][start.width].team;
	RKSwitch* RKS = (team == BLACK) ? &info->blackRKS : &info->whiteRKS;

	int difference = (stop.width - start.width);

	int kWidth = (difference < 0) ? 6 : 2;
	int rWidth = (difference < 0) ? 5 : 3;

	Point rook = {start.height, rWidth};
	Point king = {stop.height, kWidth};

	move_board_piece(board, stop, king);
	move_board_piece(board, start, rook);

	update_king_point(info, team, king);

	*RKS = (RKSwitch) {false, false};
}

void execute_rook_move(Board board, Move move, Info* info)
{
	Point start = move.start;

	Team team = board[start.height][start.width].team;
	RKSwitch* RKS = (team == BLACK) ? &info->blackRKS : &info->whiteRKS;

	move_board_piece(board, move.start, move.stop);

	if(start.width == 0) RKS->left = false;
	if(start.width == 7) RKS->right = false;
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
	RKSwitch* RKS = (team == WHITE) ? &info->whiteRKS : &info->blackRKS;
	*RKS = (RKSwitch) {false, false};
}

void update_king_point(Info* info, Team team, Point point)
{
	Point* kingP = (team == WHITE) ? &info->wKing : &info->bKing;
	*kingP = (Point) {point.height, point.width};
}

void execute_king_move(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;
	Team team = board[start.height][start.width].team;

	turn_off_rook_switch(info, team);
	update_king_point(info, team, stop);

	move_board_piece(board, start, stop);
}

void make_pawn_queen(Board board, Point point)
{
	Team team = board_point_team(board, point);

	bool whiteQueen = (team == WHITE && point.height == 0);
	bool blackQueen = (team == BLACK && point.height == 7);

	if(whiteQueen || blackQueen)
	{
		board[point.height][point.width].type = QUEEN;
	}
}
