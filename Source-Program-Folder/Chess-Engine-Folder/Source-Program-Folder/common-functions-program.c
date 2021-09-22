
#include "../Header-Program-Folder/chess-engine-includer.h"

const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
const char numbers[] = {'8', '7', '6', '5', '4', '3', '2', '1'};

bool chess_team_string(char* string, Team team)
{
	switch(team)
	{
		case (NONE): strcpy(string, "NONE"); return true;

		case(WHITE): strcpy(string, "WHITE"); return true;

		case(BLACK): strcpy(string, "BLACK"); return true;

		default: return false;
	}
	return false;
}

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

void convert_string_upper(char* string, int length)
{
	for(int index = 0; index < length; index += 1)
	{
		string[index] = convert_char_upper(string[index]);
	}
}

char convert_char_upper(char character)
{
	// If the letter is not lowercase, it cant be converted
	if(!number_inside_bounds(character, 97, 122)) return character;

	// If the letter is lowercase, it will be converted.
	else return (character - 32);
}

bool board_point_string(char* string, Point point)
{
	int height = point.height, width = point.width;

	if(!number_inside_bounds(height, 0, BOARD_HEIGHT-1)) return false;
	if(!number_inside_bounds(width, 0, BOARD_WIDTH-1)) return false;

	sprintf(string, "%c%c", letters[width], numbers[height]);

	return true;
}

bool chess_move_string(char* string, Move move)
{
	Point start = move.start, stop = move.stop;

	char startString[10], stopString[10];

	if(!board_point_string(startString, start)) return false;
	if(!board_point_string(stopString, stop)) return false;

	sprintf(string, "%s->%s", startString, stopString);

	return true;
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
