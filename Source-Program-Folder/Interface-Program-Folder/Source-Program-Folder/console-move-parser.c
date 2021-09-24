
#include "../Header-Program-Folder/interface-files-includer.h"

bool input_console_move(Move* move, Board board, Info info)
{
	Move inputMove = EMPTY_MOVE;
	char inputString[20];

	while(!move_inside_board(inputMove))
	{
		if(!input_string_move(inputString)) continue;

		if(!strcmp(inputString, QUIT_STRING)) return false;

		if(!parse_move_string(&inputMove, board, info, inputString)) continue;
	}

	*move = inputMove;

	return true;
}

bool input_string_move(char* string)
{
	printf("%s", MOVE_STRING_INPUT);

	bool output = scanf("%[^\n]%*c", string);

	fflush(stdin);

	if(output <= 0) return false;

	int length = strlen(string);

	if(length <= 0) return false;

	convert_string_upper(string, length);

	return true;
}

bool parse_move_string(Move* move, Board board, Info info, char string[])
{
	convert_string_upper(string, strlen(string));

	if(!strcmp(string, HELP_STRING))
	{
		return help_move_parser(move, board, info);
	}
	else if(!strcmp(string, HINT_STRING))
	{
		return hint_move_parser(move, board, info);
	}
	return default_move_parser(move, board, info, string);
}

bool help_move_parser(Move* move, Board board, Info info)
{
	return best_possible_move(move, board, info, STD_DEPTH, info.current);
}

bool hint_move_parser(Move* move, Board board, Info info)
{
	Move hintMove;
	if(!best_possible_move(&hintMove, board, info, STD_DEPTH, info.current)) return false;

	char moveString[20];
	if(!chess_move_string(moveString, hintMove)) return false;

	printf("%s[%s]\n", HINT_MOVE_OUTPUT, moveString);

	*move = EMPTY_MOVE;

	return false;
}

bool default_move_parser(Move* move, Board board, Info info, char string[])
{
	char seperator[] = " ";

	char* startString = strtok(string, seperator);
	char* stopString = strtok(NULL, seperator);

	if(startString == NULL || stopString == NULL) return false;

	Point start, stop;

	if(!parse_board_point(&start, startString)) return false;
	if(!parse_board_point(&stop, stopString)) return false;

	*move = (Move) {start, stop};

	return true;
}

bool parse_board_point(Point* point, char string[])
{
	if(strlen(string) < 2 || strlen(string) > 2) return false;

	int width = string_letter_index((char*) boardLetters, BOARD_WIDTH, string[0]);
	int height = string_letter_index((char*) boardNumbers, BOARD_HEIGHT, string[1]);

	if(width == -1 || height == -1) return false;

	*point = (Point) {height, width};

	return true;
}
