
#include "../Header-Program-Folder/chess-simulations-program.h"

bool check_after_kingSwitch(Board board, Move move, Info info)
{
	Team team = board_point_team(board, move.start);

	Board copy = copy_chess_board(board);
	Info infoDummy;

	execute_rook_switch(copy, move, &infoDummy);

	Point king = team_king_point(info, team);

	if(!king_inside_check(copy, king))
	{
		free_chess_board(copy); return true;
	}

	free_chess_board(copy); return false;
}

bool move_prevent_check(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	Piece piece = board_point_piece(board, start);
	if(board_point_empty(board, start)) return false;

	Point king = team_king_point(info, piece.team);

	Board copy = copy_chess_board(board);
	move_board_piece(copy, start, stop);

	if(piece.type == KING) king = stop;

	if(!king_inside_check(copy, king))
	{
		free_chess_board(copy); return true;
	}

	free_chess_board(copy); return false;
}

bool simulate_enemy_check(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	Team sTeam = board_point_team(board, start);

	if(sTeam == NONE) return false;

	Point king = (sTeam == WHITE) ? info.bKing : info.wKing;

	Board copy = copy_chess_board(board);
	move_board_piece(copy, start, stop);

	if(king_inside_check(copy, king))
	{
		free_chess_board(copy); return true;
	}

	free_chess_board(copy); return false;
}

bool simulate_check_mate(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	Team sTeam = board_point_team(board, start);

	if(sTeam == NONE) return false;

	Point king = (sTeam == WHITE) ? info.bKing : info.wKing;

	Board copy = copy_chess_board(board);
	move_board_piece(copy, start, stop);

	if(check_mate_situation(copy, info, king))
	{
		free_chess_board(copy); return true;
	}

	free_chess_board(copy); return false;
}
