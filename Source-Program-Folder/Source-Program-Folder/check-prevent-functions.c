
#include "../Header-Program-Folder/check-prevent-functions.h"

bool team_prevent_check(Board board, Info info, Team team)
{
	if(team == NONE) return false;

	Point point;
	for(int height = 0; height < B_HEIGHT; height = height + 1)
	{
		for(int width = 0; width < B_WIDTH; width = width + 1)
		{
			point = (Point) {height, width};
			Team currTeam = board_point_team(board, point);

			if(currTeam != team) continue;

			if(piece_prevent_check(board, point, info)) return true;
		}
	}
	return false;
}

bool piece_prevent_check(Board board, Point start, Info info)
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

			if(!piece_move_acceptable(board, move, info)) continue;

			if(move_prevent_check(board, move, info)) return true;
		}
	}
	return false;
}
