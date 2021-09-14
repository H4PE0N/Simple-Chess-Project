
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

	// The code after this is going to be replaced:

	Point stop; Move move;
	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			stop = (Point) {height, width};
			move = (Move) {start, stop};

			if(!piece_move_acceptable(board, move, info)) continue;

			if(move_prevent_check(board, move, info)) return true;
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
