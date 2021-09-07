
#include "../Header-Program-Folder/game-interface-program.h"

const char* symbolColors[] = {FG_DEFAULT, FG_RED, FG_RED};
const char* squareColors[] = {BG_DEFAULT, BG_WHITE, BG_BLACK};

const char* blackSymbols[] = {" ", "♟", "♝", "♞", "♜", "♛", "♚"};
const char* whiteSymbols[] = {" ", "♙", "♗", "♘", "♖", "♕", "♔"};

const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
const char numbers[] = {'8', '7', '6', '5', '4', '3', '2', '1'};

#define DIS_LETS "  | A | B | C | D | E | F | G | H |"
#define DIS_ROW "--+---+---+---+---+---+---+---+---+--"

void display_chess_board(Board board)
{
	CLEAR_LINE; printf("%s\n", DIS_LETS);

	for(int height = 0; height < 8; height = height + 1)
	{
		CLEAR_LINE; printf("%s\n", DIS_ROW);

		CLEAR_LINE; printf("%c", numbers[height]);

		printf(" ");

		for(int width = 0; width < 8; width = width + 1)
		{
			printf("|");

			Piece piece = board[height][width];
			display_board_symbol(height, width, piece);
		}

		printf("|"); printf(" ");

		printf("%c\n", numbers[height]);
	}
	CLEAR_LINE; printf("%s\n", DIS_ROW);

	CLEAR_LINE; printf("%s\n", DIS_LETS);
}

void display_game_round(Board board, Info info)
{
	display_chess_board(board);

	display_chess_info(info);
}

void display_board_symbol(int height, int width, Piece piece)
{
	const char* blackSymbol = blackSymbols[piece.type];
	const char* whiteSymbol = whiteSymbols[piece.type];

	const char* symbol = (piece.color == WHITE) ? whiteSymbol : blackSymbol;
	const char* symbolColor = symbolColors[piece.color];

	const char* whiteSquare = squareColors[WHITE];
	const char* blackSquare = squareColors[BLACK];

	bool squareBool = (height % 2 == 0 && width % 2 == 0) ||
					  (height % 2 != 0 && width % 2 != 0);

	const char* squareColor = squareBool ? whiteSquare : blackSquare;

	printf("%s%s", symbolColor, squareColor);

	printf(" ");

	printf("%s", symbol);

	printf(" ");

	printf("%s", "\033[0m");
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
	
	if(!strcmp(string, "RANDOM"))
	{
		return find_computer_move(move, board, info, info.current);
	}

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

	*point = (Point) {height, width};

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