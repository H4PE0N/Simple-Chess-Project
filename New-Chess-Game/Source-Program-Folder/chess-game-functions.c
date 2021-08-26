
#include "../Header-Program-Folder/chess-game-functions.h"

bool game_still_running(Color* winner, Board board, Info* info)
{
	for(int round = 0; round < 2; round = round + 1)
	{
		Color color = (round == 0) ? WHITE : BLACK;
		Point point = color_king_point(*info, color);

		if(check_mate_situation(board, point, info))
		{
			*winner = (color == WHITE) ? BLACK : WHITE;
			return false;
		}
		if(check_draw_situation(board, point))
		{
			*winner = NONE;
			return false;
		}
	}

	return true;
}

bool other_pieces_moveable(Board board, Color color)
{
	Piece piece; Point point;

	for(int height = 0; height < 8; height = height + 1)
	{
		for(int width = 0; width < 8; width = width + 1)
		{
			piece = board[height][width];
			point = (Point) {height, width};

			if(piece.color != color) continue;
			
			if(board_piece_moveable(board, piece, point)) return true;
		}
	}
	return false;
}

bool check_draw_situation(Board board, Point point)
{
	Color color = board_point_color(board, point);

	if(king_check_situation(board, point)) return false;

	if(board_king_moveable(board, point)) return false;

	if(other_pieces_moveable(board, color)) return false;

	return true;
}

bool check_mate_situation(Board board, Point point, Info* info)
{
	Color color = board_point_color(board, point);

	if(!king_check_situation(board, point)) return false;

	if(board_king_moveable(board, point)) return false;

	if(team_prevent_check(board, info, color)) return false;

	return true;
}