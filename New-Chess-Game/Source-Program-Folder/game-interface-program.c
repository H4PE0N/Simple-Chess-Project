
#include "../Header-Program-Folder/game-interface-program.h"

const char symbols[] = {'.', 'P', 'B', 'H', 'R', 'Q', 'K'};
const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
const char numbers[] = {'1', '2', '3', '4', '5', '6', '7', '8'};

void display_chess_board(Board board)
{
	printf("  A B C D E F G H\n");
	for(int height = 0; height < 8; height = height + 1)
	{
		printf("%d ", height + 1);
		for(int width = 0; width < 8; width = width + 1)
		{
			Type type = board[height][width].type;
			Color color = board[height][width].color;

			char symbol = symbols[type];
			char ascii_c[20];

			if(color == WHITE) strcpy(ascii_c, "\033[31m");
			else if(color == BLACK) strcpy(ascii_c, "\033[34m");
			else strcpy(ascii_c, "\033[0m");

			printf("%s%c%s ", ascii_c, symbol, "\033[0m");
		}
		printf("\n");
	}
}

void display_chess_result(Board board, Color winner)
{
	display_chess_board(board);

	if(winner == NONE) printf("It's a draw!\n");
	else printf("The winner is [%s]!\n", (winner == WHITE) ? "RED" : "BLUE");
}

void display_chess_info(Info info)
{
	printf("Current \t: (%s)\n", (info.current == WHITE) ? "RED" : "BLUE");
	// printf("WhiteRKS\t: (%d-%d)\n", info.whiteRKS.left, info.whiteRKS.right);
	// printf("BlackRKS\t: (%d-%d)\n", info.blackRKS.left, info.blackRKS.right);
	printf("TURNS   \t: (%d)\n", info.turns);
}

bool input_current_move(char* string)
{
	printf("INPUT POSITION: ");
	if(!input_string_variable(string)) return false;

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

bool parse_chess_move(Move* move, char string[])
{
	char seperator[] = " ";
	char* start = strtok(string, seperator);
	char* stop = strtok(NULL, seperator);

	if(start == NULL || stop == NULL) return false;

	if(!parse_chess_position(&move->start, start)) return false;
	if(!parse_chess_position(&move->stop, stop)) return false;

	return true;
}

bool parse_chess_position(Point* point, char string[])
{
	if(strlen(string) < 2 || strlen(string) > 2) return false;

	int width = string_letter_index((char*) letters, 8, string[0]);
	int height = string_letter_index((char*) numbers, 8, string[1]);

	if(width == -1 || height == -1) return false;

	point->height = height;
	point->width = width;

	return true;
}

int string_letter_index(char string[], int length, char letter)
{
	for(int index = 0; index < length; index += 1)
	{	
		if(letter == string[index]) return index;
	}
	return -1;
}