
#include "../Header-Program-Folder/chess-engine-includer.h"

bool king_inside_check(Board board, Point king)
{
	if(!point_inside_board(king)) return false;

	// If it isn't a king, it cant be in check
	if(board_point_type(board, king) != KING) return false;

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
	// These controls is the most obvious, and should be done first
	if(!points_inside_board(point, king)) return false;

	if(board_point_empty(board, point)) return false;
	if(board_point_empty(board, king)) return false;

	if(!board_points_enemy(board, point, king)) return false;

	// These controls are more specific, and should be done later
	if(!moving_piece_valid(board, point, king)) return false;

	if(!clear_moving_path(board, point, king)) return false;

	// If it is a pawn, that is moving forward, it cant check
	// and therefor it should not count as a check
	bool isPawn = (board_point_type(board, point) == PAWN);
	if(isPawn && point.width == king.width) return false;

	return true;
}
