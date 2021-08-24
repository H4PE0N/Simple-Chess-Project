
#include "header.h"

bool check_draw_situation(Board board, Point point, Color color)
{
	if(board_king_moveable(board, point, color)) return false;

	if(other_pieces_moveable(board, color)) return false;

	return true;
}

bool other_pieces_moveable(Board board, Color color)
{
	if(color == NONE) return false;

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

bool check_mate_situation(Board board, Point point, Color color)
{
	if(!king_check_situation(board, point, color)) return false;
	// King is in check

	if(board_king_moveable(board, point, color)) return false;
	// King cant move

	if(team_prevent_check(board, color)) return false;
	// Team mate cant prevent check

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

			if(!clear_moving_path(board, point, enemy)) continue;

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

			if(!clear_moving_path(board, point, enemy)) continue;

			if(enemyType == ROOK || enemyType == QUEEN) return true;
		}
	}
	return false;
}