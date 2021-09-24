
#include "../Header-Program-Folder/interface-files-includer.h"

bool chess_team_string(char* string, Team team)
{
	switch(team)
	{
		case (NONE): strcpy(string, NONE_STRING); return true;

		case(WHITE): strcpy(string, WHITE_STRING); return true;

		case(BLACK): strcpy(string, BLACK_STRING); return true;

		default: return false;
	}
	return false;
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

	sprintf(string, "%c%c", boardLetters[width], boardNumbers[height]);

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
