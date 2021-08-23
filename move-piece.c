
#include "header.h"

bool execute_pawn_move(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_pawn_valid(board, start, stop)) return false;

	bool straight = (start.width == stop.width);
	Color color = board[start.height][start.width].color;

	if(straight)
	{
		if(!board_piece_empty(board, stop.height, stop.width)) return false;
		if(!clear_moving_path(board, start, stop)) return false;

		switch_chess_pieces(board, start, stop);

		make_pawn_queen(board, stop, color);
	}
	else
	{
		if(!chess_enemy_point(board, start, stop)) return false;
		
		remove_board_piece(board, stop.height, stop.width);

		switch_chess_pieces(board, start, stop);
	}

	return true;
}

bool execute_rook_move(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_rook_valid(board, start, stop)) return false;

	if(!clear_straight_path(board, start, stop)) return false;

	bool team = chess_team_point(board, start, stop);
	bool isRKS = rook_king_switch(board, start, stop);

	Color color = board[start.height][start.width].color;
	if(color == NONE) return false;

	RKSwitch* RKS = (color == BLACK) ? &info->blackRKS : &info->whiteRKS;

	bool* RKValue = NULL;

	if(start.width == 0) RKValue = &RKS->left;
	if(start.width == 7) RKValue = &RKS->right;

	if(RKValue != NULL)
	{
		if(isRKS && RKValue)
		{
			switch_chess_pieces(board, start, stop);

			RKS->right = false;
			RKS->left = false;

			return true;
		}
		else if(team) return false;

		*RKValue = false;
	}

	if(chess_enemy_point(board, start, stop))
	{
		remove_board_piece(board, stop.height, stop.width);
	}
	switch_chess_pieces(board, start, stop);

	return true;
}

bool execute_knight_move(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_knight_valid(board, start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	if(chess_enemy_point(board, start, stop))
	{
		remove_board_piece(board, stop.height, stop.width);
	}

	switch_chess_pieces(board, start, stop);

	return true;
}

bool execute_bishop_move(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_bishop_valid(board, start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	if(!clear_diagonal_path(board, start, stop)) return false;

	if(chess_enemy_point(board, start, stop))
	{
		remove_board_piece(board, stop.height, stop.width);
	}

	switch_chess_pieces(board, start, stop);

	return true;
}

bool execute_queen_move(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_queen_valid(board, start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(chess_enemy_point(board, start, stop))
	{
		remove_board_piece(board, stop.height, stop.width);
	}

	switch_chess_pieces(board, start, stop);

	return true;
}

bool execute_king_move(Board board, Move move, Info* info)
{
	Point start = move.start, stop = move.stop;

	if(!moving_king_valid(board, start, stop)) return false;

	if(chess_team_point(board, start, stop)) return false;

	Color color = board[start.height][start.width].color;

	if(!simulate_check_move(board, move, color)) return false;
	
	RKSwitch* RKS = (color == WHITE) ? &info->whiteRKS : &info->blackRKS;
	Point* kingP = (color == WHITE) ? &info->wKing : &info->bKing;

	RKS->left = false;
	RKS->right = false;

	if(chess_enemy_point(board, start, stop))
	{
		remove_board_piece(board, stop.height, stop.width);
	}

	kingP->height = stop.height;
	kingP->width = stop.width;

	switch_chess_pieces(board, start, stop);

	return true;
}