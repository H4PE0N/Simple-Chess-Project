
#include "../Header-Program-Folder/chess-pieces-moveable.h"

bool board_piece_moveable(Board board, Info* info, Point start)
{
	if(!point_inside_board(start)) return false;
	if(board_point_empty(board, start)) return false;

	Point stop; Move move;
	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			stop = (Point) {height, width};
			move = (Move) {start, stop};

			if(piece_move_acceptable(board, move, info)) return true;
		}
	}
	return false;
}