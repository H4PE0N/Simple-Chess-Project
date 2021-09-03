
#include "../Header-Program-Folder/game-check-functions.h"

bool king_inside_check(Board board, Point king)
{
	Point point;
	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			point = (Point) {height, width};
			
			if(board_point_checking(board, point, king)) return true;
		}
	}
	return false;
}

bool board_point_checking(Board board, Point point, Point king)
{
	if(!board_points_enemy(board, point, king)) return false;

	if(!moving_piece_valid(board, point, king)) return false;

	if(!clear_moving_path(board, point, king)) return false;

	return true;
}

// Remove color from this function!
/*bool king_check_situation(Board board, Point point, Color color)
{
	Board copy = copy_chess_board(board);
	append_board_piece(copy, point, (Piece) {KING, color});

	if(check_knight_check(copy, point, color))
	{
		free(copy); return true;
	}

	if(check_pawn_check(copy, point, color))
	{
		free(copy); return true;
	}

	if(check_diagonal_check(copy, point, color))
	{
		free(copy); return true;
	}

	if(check_straight_check(copy, point, color))
	{
		free(copy); return true;
	}

	if(check_king_check(copy, point, color))
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

			if(!point_inside_board(enemy)) continue;

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

		if(!point_inside_board(enemy)) continue;

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

			if(!point_inside_board(enemy)) continue;

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

			if(!point_inside_board(enemy)) continue;

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
}*/