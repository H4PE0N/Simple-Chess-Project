
#include "../Header-Program-Folder/chess-engine-includer.h"

Point* create_point_array(int length)
{
	Point* points = malloc(sizeof(Point) * (length + 1));

	for(int index = 0; index <= length; index += 1)
	{
		points[index] = EMPTY_POINT;
	}
	return points;
}

int point_array_amount(Point points[])
{
	int amount = 0;
	while(point_inside_board(points[amount]))
	{
		amount += 1;
	}
	return amount;
}

void switch_array_moves(Move* moves, int first, int second)
{
	Move firstMove = moves[first];
	Move secondMove = moves[second];

	moves[first] = secondMove;
	moves[second] = firstMove;
}

void append_moves_array(Move* moves, Move adding[])
{
	int amount = moves_array_amount(moves);
	int addAmount = moves_array_amount(adding);

	for(int index = 0; index < addAmount; index += 1)
	{
		moves[amount + index] = adding[index];
	}
}

int moves_array_amount(Move moves[])
{
	int amount = 0;
	while(points_inside_board(moves[amount].start, moves[amount].stop))
	{
		amount += 1;
	}
	return amount;
}

void clear_moves_array(Move* moves)
{
	int amount = moves_array_amount(moves);

	for(int index = 0; index < amount; index += 1)
	{
		moves[index] = EMPTY_MOVE;
	}
}

Move* create_moves_array(int amount)
{
	Move* moves = malloc(sizeof(Move) * amount);
	for(int index = 0; index < amount; index += 1)
	{
		moves[index] = EMPTY_MOVE;
	}
	return moves;
}

int string_letter_index(char string[], int length, char letter)
{
	for(int index = 0; index < length; index += 1)
	{
		if(letter == string[index]) return index;
	}
	return -1;
}
