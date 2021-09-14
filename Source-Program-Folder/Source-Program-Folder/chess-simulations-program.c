
#include "../Header-Program-Folder/chess-simulations-program.h"

bool check_after_kingSwitch(Board board, Move move, Info info)
{
	if(!move_inside_board(move)) return false;

	Team team = board_point_team(board, move.start);

	Board boardCopy = copy_chess_board(board);
	Info infoDummy = info;

	execute_rook_switch(boardCopy, move, &infoDummy);

	Point king = team_king_point(infoDummy, team);

	if(!king_inside_check(boardCopy, king))
	{
		free_chess_board(boardCopy); return true;
	}

	free_chess_board(boardCopy); return false;
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

bool simulate_enemy_check(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	Team sTeam = board_point_team(board, start);

	if(sTeam == NONE) return false;

	Point king = (sTeam == WHITE) ? info.bKing : info.wKing;

	Board boardCopy = copy_chess_board(board);
	move_board_piece(boardCopy, start, stop);

	if(king_inside_check(boardCopy, king))
	{
		free_chess_board(boardCopy); return true;
	}

	free_chess_board(boardCopy); return false;
}

bool simulate_check_mate(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	Team sTeam = board_point_team(board, start);

	if(sTeam == NONE) return false;

	Point king = (sTeam == WHITE) ? info.bKing : info.wKing;

	Board boardCopy = copy_chess_board(board);
	move_board_piece(boardCopy, start, stop);

	if(check_mate_situation(boardCopy, info, king))
	{
		free_chess_board(boardCopy); return true;
	}

	free_chess_board(boardCopy); return false;
}
