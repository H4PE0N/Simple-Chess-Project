
#include "header.h"

bool check_draw_situation(Board board, Point point, Color color)
{
	if(king_is_moveable(board, point, color)) return false;

	if(other_pieces_moveable(board, color)) return false;

	return true;
}

bool other_pieces_moveable(Board board, Color color)
{
	if(color == NONE) return false;
	Color teamColor; Type teamType;
	for(int height = 0; height < 8; height = height + 1)
	{
		for(int width = 0; width < 8; width = width + 1)
		{
			teamColor = board[height][width].color;
			teamType = board[height][width].type;

			if(teamColor != color) continue;
			
			
		}
	}
	return true;
}

// bool board_piece_moveable(Board board, Piece piece, Move move)
// {
	
// }

bool check_mate_situation(Board board, Point point, Color color)
{
	if(king_is_moveable(board, point, color)) return false;

	if(!king_check_situation(board, point, color)) return false;

	return true;
}

Board copy_chess_board(Board board)
{
	Board copy = malloc(sizeof(Piece*) * 8);
	for(int height = 0; height < 8; height = height + 1)
	{
		copy[height] = malloc(sizeof(Piece) * 8);
		for(int width = 0; width < 8; width = width + 1)
		{
			copy[height][width].type = board[height][width].type;
			copy[height][width].color = board[height][width].color;
		}
	}
	return copy;
}

bool simulate_check_move(Board board, Move move, Color color)
{
	Point start = move.start, stop = move.stop;
	if(!point_inside_bounds(stop.height, stop.width)) return false;

	// The function:
	Board copy = copy_chess_board(board);
	allocate_board_piece(copy, start, KING, color);

	printf("(%d %d) -> (%d %d)\n", start.height, start.width, stop.height, stop.width);

	if(chess_team_point(copy, start, stop))
	{
		printf("Team mate is in the way!\n");
		free(copy); return false;
	}

	remove_board_piece(copy, stop.height, stop.width);
	switch_chess_pieces(copy, start, stop);

	if(!king_check_situation(copy, stop, color))
	{
		free(copy); return true;
	}

	printf("The king is in check then!\n");

	free(copy); return false;
}

bool king_is_moveable(Board board, Point point, Color color)
{
	Point enemy;

	for(int height = 0; height < 3; height = height + 1)
	{
		for(int width = 0; width < 3; width = width + 1)
		{
			int rHeight = (point.height - 1) + height;
			int rWidth = (point.width - 1) + width;

			enemy = (Point) {rHeight, rWidth};

			if(board_points_equal(point, enemy)) continue;

			Move move = {point, enemy};

			if(simulate_check_move(board, move, color))
			{
				return true;
			}
		}
	}
	return false;
}

bool king_check_situation(Board board, Point point, Color color)
{
	Board copy = copy_chess_board(board);
	allocate_board_piece(copy, point, KING, color);

	if(check_knight_check(board, point, color))
	{
		free(copy); return true;
	}

	if(check_pawn_check(board, point, color))
	{
		free(copy); return true;
	}

	if(check_diagonal_check(board, point, color))
	{
		free(copy); return true;
	}

	if(check_straight_check(board, point, color))
	{
		free(copy); return true;
	}

	if(check_king_check(board, point, color))
	{
		free(copy); return true;
	}

	free(copy); return false;
}

bool check_king_check(Board board, Point point, Color color)
{
	Color enemyColor; Type enemyType; Point enemy;

	for(int height = 0; height < 3; height = height + 1)
	{
		for(int width = 0; width < 3; width = width + 1)
		{
			int rHeight = (point.height - 1) + height;
			int rWidth = (point.width - 1) + width;

			enemy = (Point) {rHeight, rWidth};

			if(!point_inside_bounds(enemy.height, enemy.width)) continue;

			enemyType = board[enemy.height][enemy.width].type;
			enemyColor = board[enemy.height][enemy.width].color;

			if(enemyColor == NONE || enemyColor == color) continue;

			if(enemyType == KING) return true;
		}
	}
	return false;
}

bool check_pawn_check(Board board, Point point, Color color)
{
	int height = (color == WHITE) ? (point.height - 1) : (point.height + 1);

	Color enemyColor; Type enemyType; Point enemy;

	for(int index = -1; index != 3; index = index + 2)
	{
		int width = (point.width + index);

		enemy = (Point) {height, width};

		if(!point_inside_bounds(enemy.height, enemy.width)) continue;

		enemyType = board[enemy.height][enemy.width].type;
		enemyColor = board[enemy.height][enemy.width].color;

		if(enemyColor == NONE || enemyColor == color) continue;

		if(enemyType == PAWN) return true;
	}
	return false;
}

bool check_knight_check(Board board, Point point, Color color)
{
	Color enemyColor; Type enemyType; Point enemy;

	for(int height = 0; height < 5; height = height + 1)
	{
		for(int width = 0; width < 5; width = width + 1)
		{
			if(height == width || (height + width) == 4) continue;
			if(height == 2 || width == 2) continue;

			int rHeight = (point.height - 2) + height;
			int rWidth = (point.width - 2) + width;

			enemy = (Point) {rHeight, rWidth};

			if(!point_inside_bounds(enemy.height, enemy.width)) continue;

			enemyType = board[enemy.height][enemy.width].type;
			enemyColor = board[enemy.height][enemy.width].color;

			if(enemyColor == NONE || enemyColor == color) continue;

			if(enemyType == KNIGHT) return true;
		}
	}
	return false;
}

bool check_diagonal_check(Board board, Point point, Color color)
{
	Color enemyColor; Type enemyType; Point enemy;

	for(int index = -8; index <= 16; index = index + 1)
	{
		for(int round = 0; round < 2; round = round + 1)
		{
			int height = (index + point.height);
			int width = (round == 0) ? (index + point.width) : (point.width - index);

			enemy = (Point) {height, width};

			if(!point_inside_bounds(enemy.height, enemy.width)) continue;

			enemyType = board[enemy.height][enemy.width].type;
			enemyColor = board[enemy.height][enemy.width].color;

			if(enemyColor == NONE || enemyColor == color) continue;

			if(!clear_straight_path(board, point, enemy)) continue;

			if(enemyType == BISHOP || enemyType == QUEEN) return true;
		}
	}
	return false;
}

bool check_straight_check(Board board, Point point, Color color)
{
	Color enemyColor; Type enemyType; Point enemy;

	for(int index = 0; index < 8; index = index + 1)
	{
		for(int round = 0; round < 2; round = round + 1)
		{
			int height = (round == 0) ? point.height : index;
			int width = (round == 0) ? index : point.width;

			enemy = (Point) {height, width};
			
			enemyType = board[enemy.height][enemy.width].type;
			enemyColor = board[enemy.height][enemy.width].color;

			if(enemyColor == NONE || enemyColor == color) continue;

			if(!clear_straight_path(board, point, enemy)) continue;

			if(enemyType == ROOK || enemyType == QUEEN) return true;
		}
	}
	return false;
}