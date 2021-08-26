
#include "../Header-Program-Folder/chess-computer-program.h"

bool computer_chess_move(Board board, Info* info, Color color)
{
	Move move = {(Point) {-1, -1}, (Point) {-1, -1}};

	if(!find_computer_move(&move, board, info, color))
		{
			printf("Cant find move!\n");
			return false;
		}

	printf("move (%d %d) (%d %d)\n",
		move.start.height, move.start.width, move.stop.height, move.stop.width);

	Piece piece = board_point_piece(board, move.start);
	Point* king = (color == WHITE) ? &info->wKing : &info->bKing;

	if(piece.type == KING) *king = move.stop;

	move_board_piece(board, move.start, move.stop);

	return true;
}

bool find_computer_move(Move* move, Board board, Info* info, Color color)
{
	//if(computer_offence_move(move, board, info, color)) return true;

	if(computer_suicide_move(move, board, info, color)) return true;

	//if(computer_defence_move(move, board, info, color)) return true;

	if(computer_regular_move(move, board, info, color)) return true;

	return false;
}

bool computer_suicide_move(Move* move, Board board, Info* info, Color color)
{
	Move moves[16]; int amount = 0;
	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			Point point = {height, width};
			Color currColor = board_point_color(board, point);

			if(currColor != color) continue;

			if(!piece_suicide_move(&moves[amount], board, info, point)) continue;

			amount += 1;
		}
	}

	printf("Found (%d) moves!\n", amount);

	if(amount == 0) return false;

	int index = (rand() % amount);

	*move = moves[index];
	//*move = moves[0];

	return true;
}

bool piece_suicide_move(Move* move, Board board, Info* info, Point start)
{
	Point stop; Move currMove;
	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			stop = (Point) {height, width};
			currMove = (Move) {start, stop};

			if(!piece_move_acceptable(board, currMove, info)) continue;

			if(!move_prevent_check(board, currMove, info)) continue;

			if(!board_points_enemy(board, start, stop)) continue;

			*move = currMove; 
			return true;
		}
	}
	return false;
}

bool computer_offence_move(Move* move, Board board, Info* info, Color color)
{
	return false;
}

bool computer_defence_move(Move* move, Board board, Info* info, Color color)
{
	return false;
}

bool computer_regular_move(Move* move, Board board, Info* info, Color color)
{
	Move moves[16]; int amount = 0;
	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			Point point = {height, width};
			Color currColor = board_point_color(board, point);

			if(currColor != color) continue;

			if(!piece_regular_move(&moves[amount], board, info, point)) continue;

			amount += 1;
		}
	}

	printf("Found (%d) moves!\n", amount);

	if(amount == 0) return false;

	int index = (rand() % amount);

	*move = moves[index];
	//*move = moves[0];

	return true;
}

bool piece_regular_move(Move* move, Board board, Info* info, Point start)
{
	Point stop; Move currMove;
	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			stop = (Point) {height, width};
			currMove = (Move) {start, stop};

			if(!piece_move_acceptable(board, currMove, info)) continue;

			printf("move (%d %d) (%d %d)\n",
				start.height, start.width, stop.height, stop.width);

			if(!move_prevent_check(board, currMove, info)) continue;

			*move = currMove; 
			return true; 
		}
	}
	return false;
}


