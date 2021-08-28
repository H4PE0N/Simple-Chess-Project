
#include "../Header-Program-Folder/game-interface-program.h"

const char* colors[] = {"\033[0m", "\033[37m", "\033[34m"};

const char blackSymbols[] = {'.', 'P', 'B', 'H', 'R', 'Q', 'K'};
const char whiteSymbols[] = {'.', 'p', 'b', 'h', 'r', 'q', 'k'};

const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
const char numbers[] = {'1', '2', '3', '4', '5', '6', '7', '8'};

void display_chess_board(Board board)
{
	CLEAR_LINE; printf("  A B C D E F G H\n");
	for(int height = 0; height < 8; height = height + 1)
	{
		CLEAR_LINE; printf("%d ", height + 1);
		for(int width = 0; width < 8; width = width + 1)
		{
			Piece piece = board[height][width];
			display_board_symbol(piece); printf(" ");
		}
		printf("\n");
	}
}

void display_game_round(Board board, Info info)
{
	display_chess_board(board);

	display_chess_info(info);
}

void display_board_symbol(Piece piece)
{
	char blackSymbol = blackSymbols[piece.type];
	char whiteSymbol = whiteSymbols[piece.type];

	char symbol = (piece.color == WHITE) ? whiteSymbol : blackSymbol;
	char* color = (char*) colors[piece.color];

	printf("%s%c%s", color, symbol, "\033[0m");
}

void display_move_info(MoveInfo moveInfo)
{
	printf("[SC-%d CM-%d TE-%d GT-%d EX-%d TY-%d EN-%d]\n",
			moveInfo.setsCheck, 
			moveInfo.checkMate, 
			moveInfo.takeEnemy, 
			moveInfo.getsTaken, 
			moveInfo.exposed, 
			moveInfo.type,
			moveInfo.enemy);
}

void display_board_point(Point point)
{
	printf("Point=[%d-%d]\n", point.height, point.width);
}

void display_board_move(Move move)
{
	Point start = move.start, stop = move.stop;
	printf("Move=[%d-%d] [%d-%d]\n", start.height, start.width, stop.height, stop.width);
}

void display_chess_result(Board board, Color winner)
{
	display_chess_board(board);

	if(winner == NONE)
	{
		CLEAR_LINE; printf("[!] The game ended with a draw!\n");
	}
	else 
	{
		char* color = (winner == WHITE) ? "WHITE" : "BLACK";
		CLEAR_LINE; printf("[!] The winner is [%s]!\n", color);
	}
}

void display_chess_info(Info info)
{
	char* color = (info.current == WHITE) ? "WHITE" : "BLACK";

	CLEAR_LINE; printf("[+] PLAYER : [%s]\n", color);
	CLEAR_LINE; printf("[+] TURNS  : [%dst]\n", info.turns);
}

bool input_current_move(char* string)
{
	CLEAR_LINE; printf("[?] INPUT MOVE : ");
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