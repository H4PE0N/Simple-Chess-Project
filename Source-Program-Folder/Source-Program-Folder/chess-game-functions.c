
#include "../Header-Program-Folder/global-include-header.h"

// This function should only check one team, so that the draw gets right
bool game_still_running(Team* winner, Board board, Info info)
{
	for(int round = 0; round < 2; round = round + 1)
	{
		Team team = (round == 0) ? WHITE : BLACK;
		Point point = team_king_point(info, team);

		if(!point_inside_board(point)) return false;
		if(board_point_empty(board, point)) return false;

		if(check_mate_situation(board, info, point))
		{
			*winner = (team == WHITE) ? BLACK : WHITE;
			return false;
		}
		if(check_draw_situation(board, info, point))
		{
			*winner = NONE;
			return false;
		}
	}
	return true;
}

bool update_kings_point(Board board, Info* info)
{
	Point blackKing, whiteKing;

	if(!board_piece_point(&blackKing, board, (Piece) {KING, BLACK})) return false;
	if(!board_piece_point(&whiteKing, board, (Piece) {KING, WHITE})) return false;

	info->blackKing = blackKing;
	info->whiteKing = whiteKing;

	return true;
}

bool other_pieces_moveable(Board board, Info info, Team team)
{
	Piece piece; Point point;

	for(int height = 0; height < B_HEIGHT; height = height + 1)
	{
		for(int width = 0; width < B_WIDTH; width = width + 1)
		{
			piece = board[height][width];
			point = (Point) {height, width};

			if(piece.team != team) continue;

			if(board_piece_moveable(board, info, point)) return true;
		}
	}
	return false;
}

bool check_draw_situation(Board board, Info info, Point king)
{
	Team team = board_point_team(board, king);

	if(king_inside_check(board, king)) return false;

	if(board_piece_moveable(board, info, king)) return false;

	if(other_pieces_moveable(board, info, team)) return false;

	return true;
}

bool check_mate_situation(Board board, Info info, Point king)
{
	Team team = board_point_team(board, king);

	if(!king_inside_check(board, king)) return false;

	if(board_piece_moveable(board, info, king)) return false;

	if(team_prevent_check(board, info, team)) return false;

	return true;
}
