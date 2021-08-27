
#include "../Header-Program-Folder/execute-board-moves.h"

void execute_pawn_move(Board board, Move move)
{
	Point start = move.start, stop = move.stop;
	Color color = board[start.height][start.width].color;

	move_board_piece(board, start, stop);

	make_pawn_queen(board, stop);
}

void execute_rook_switch(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	Color color = board[start.height][start.width].color;
	RKSwitch* RKS = (color == BLACK) ? &info->blackRKS : &info->whiteRKS;

	update_king_point(info, color, start);

	switch_chess_pieces(board, start, stop);

	RKS->right = false;
	RKS->left = false;
}

void execute_rook_move(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	Color color = board[start.height][start.width].color;
	RKSwitch* RKS = (color == BLACK) ? &info->blackRKS : &info->whiteRKS;

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

void turn_off_rook_switch(Info* info, Color color)
{
	RKSwitch* RKS = (color == WHITE) ? &info->whiteRKS : &info->blackRKS;
	
	RKS->left = false;
	RKS->right = false;
}

void update_king_point(Info* info, Color color, Point point)
{
	Point* kingP = (color == WHITE) ? &info->wKing : &info->bKing;

	kingP->height = point.height;
	kingP->width = point.width;
}

void execute_king_move(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;
	Color color = board[start.height][start.width].color;

	turn_off_rook_switch(info, color);
	update_king_point(info, color, stop);

	move_board_piece(board, start, stop);
}

void make_pawn_queen(Board board, Point point)
{
	Color color = board_point_color(board, point);

	bool whiteQueen = (color == WHITE && point.height == 0);
	bool blackQueen = (color == BLACK && point.height == 7);

	if(whiteQueen || blackQueen)
	{
		board[point.height][point.width].type = QUEEN;
	}
}