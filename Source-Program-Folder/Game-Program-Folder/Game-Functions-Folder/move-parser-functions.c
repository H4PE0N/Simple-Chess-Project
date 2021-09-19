
#include "../Header-Program-Folder/game-files-includer.h"

bool input_current_move(char* string)
{
	CLEAR_LINE; printf("[?] INPUT CURRENT MOVE\t: ");

	if(!input_string_variable(string)) return false;

	convert_string_upper(string, strlen(string));

	return true;
}

bool input_string_variable(char* string)
{
	bool output = scanf("%[^\n]%*c", string);

	fflush(stdin);

	if(!output) return false;

	if(strlen(string) == 0) return false;

	return true;
}

bool parse_chess_move(Move* move, Board board, Info info, char string[])
{
	convert_string_upper(string, strlen(string));

	if(!strcmp(string, "HELP"))
	{
		return help_move_parser(move, board, info, string);
	}
	else if(!strcmp(string, "HINT"))
	{
		return hint_move_parser(move, board, info, string);
	}
	else if(!strcmp(string, "SAVE"))
	{
		return save_move_parser(move, board, info, string);
	}
	else
	{
		return default_move_parser(move, board, info, string);
	}
	return false;
}

bool help_move_parser(Move* move, Board board, Info info, char string[])
{
	return best_possible_move(move, board, info, STD_DEPTH, info.current);
}

bool hint_move_parser(Move* move, Board board, Info info, char string[])
{
	Move hintMove;
	if(!best_possible_move(&hintMove, board, info, STD_DEPTH, info.current)) return false;

	char moveString[20];
	if(!chess_move_string(moveString, hintMove)) return false;

	CLEAR_LINE; printf("[!] HINT OF GOOD MOVE: [%s]\n", moveString);

	return false;
}

bool save_move_parser(Move* move, Board board, Info info, char string[])
{
	FILE* filePointer = fopen(SAVE_FILE, "w");

	if(filePointer == NULL)
	{
		file_pointer_error(SAVE_FILE);

		fclose(filePointer); return false;
	}

	Point point;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		char boardLine[20];

		for(int width = 0; width < BOARD_WIDTH; width += 1)
		{
			point = (Point) {height, width};
			int type = board_point_type(board, point);
			int team = board_point_team(board, point);

			boardLine[width * 2]		= (type + '0');
			boardLine[(width * 2) + 1]	= (team + '0');
		}

		boardLine[BOARD_WIDTH * 2] = '\n';
		fwrite(boardLine, sizeof(char), 17, filePointer);
	}

	CLEAR_LINE; printf("[!] SAVED THE CURRENT BOARD!\n");

	fclose(filePointer); return true;
}

bool default_move_parser(Move* move, Board board, Info info, char string[])
{
	char seperator[] = " ";

	char* startString = strtok(string, seperator);
	char* stopString = strtok(NULL, seperator);

	if(startString == NULL || stopString == NULL) return false;

	Point start, stop;

	if(!parse_chess_position(&start, startString)) return false;
	if(!parse_chess_position(&stop, stopString)) return false;

	*move = (Move) {start, stop}; return true;
}

bool parse_chess_position(Point* point, char string[])
{
	if(strlen(string) < 2 || strlen(string) > 2) return false;

	int width = string_letter_index((char*) letters, BOARD_WIDTH, string[0]);
	int height = string_letter_index((char*) numbers, BOARD_HEIGHT, string[1]);

	if(width == -1 || height == -1) return false;

	*point = (Point) {height, width};

	return true;
}

void extract_file_name(char* filename, char* arguments[], int amount)
{
	if(amount >= 2) strcpy(filename, arguments[1]);

	else strcpy(filename, STD_FILE);
}
