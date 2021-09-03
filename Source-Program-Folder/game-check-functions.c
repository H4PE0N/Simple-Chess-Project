
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