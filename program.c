
#include "header.h"

const char white_symbols[] = {'.', 'p', 'r', 'n', 'b', 'q', 'k'};
const char black_symbols[] = {'.', 'P', 'R', 'N', 'B', 'Q', 'K'};

const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
const char numbers[] = {'1', '2', '3', '4', '5', '6', '7', '8'};

int main(int argAmount, char* arguments[])
{
	Board board = create_chess_board();
	if(!extract_start_board(board, FILENAME))
	{
		free(board);
		return false;
	}

	char start[10], stop[10];

	while(strcmp(start, "stop"))
	{
		display_chess_board(board);

		printf("INPUT: ");
		scanf("%s", start); 

		if(!strcmp(start, "stop")) break;

		scanf("%s", stop);

		Point start_p, stop_p;

		parse_chess_position(&start_p, start);
		parse_chess_position(&stop_p, stop);

		move_chess_piece(board, start_p, stop_p);
	}
	
	display_chess_board(board);

	free(board);
	return false;
}

bool point_inside_bounds(int height, int width)
{
	return (height >= 0 && height < 8) && (width >= 0 && width < 8);
}

bool board_piece_empty(Board board, int height, int width)
{
	return (board[height][width].type == EMPTY);
}

bool parse_chess_position(Point* point, char string[])
{
	if(strlen(string) < 2 || strlen(string) > 2) return false;

	int width = -1;

	for(int index = 0; index < 8; index = index + 1)
	{
		char letter = string[0];
		if(letter == letters[index]) 
		{
			width = index; 
			break;
		}
	}

	if(width == -1) return false;

	char number = string[1];

	if(number < '1' || number > '8') return false;

	int height = number - '1';

	point->height = height;
	point->width = width;

	return true;
}

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

			char symbol = (color == WHITE) ? white_symbols[type] : black_symbols[type];

			printf("%c ", symbol);
		}
		printf("\n");
	}
}

Board create_chess_board(void)
{
	Board board = malloc(sizeof(Piece*) * 8);
	for(int index = 0; index < 8; index = index + 1)
	{
		board[index] = malloc(sizeof(Piece) * 8);
	}
	return board;
}

void parse_starting_file(Board board, FILE* filePoint)
{
	char lineBuffer[32];
	int height = 0;

	while(fgets(lineBuffer, 32, filePoint) != NULL)
	{
		for(int index = 0; index < 8; index += 1)
		{
			Type type = lineBuffer[(index * 2) + 0] - '0';
			Color color = lineBuffer[(index * 2) + 1] - '0';

			board[height][index].type = type;
			board[height][index].color = color;
		}
		height = height + 1;
	}
}

bool extract_start_board(Board board, char filename[])
{
	FILE* filePoint = fopen(filename, "r");
	if(filePoint == NULL)
	{
		fclose(filePoint);
		return false;
	}

	parse_starting_file(board, filePoint);

	fclose(filePoint); 
	return true;
}

