
#include "../Header-Program-Folder/game-interface-program.h"

const char* symbolTeams[] = {FG_DEFAULT, FG_RED, FG_RED};
const char* squareTeams[] = {BG_DEFAULT, BG_WHITE, BG_BLACK};

const char* blackSymbols[] = {" ", "P", "B", "H", "R", "Q", "K"};
const char* whiteSymbols[] = {" ", "p", "b", "h", "r", "q", "k"};

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

	const char* symbol = (piece.team == WHITE) ? whiteSymbol : blackSymbol;
	const char* symbolTeam = symbolTeams[piece.team];

	const char* whiteSquare = squareTeams[WHITE];
	const char* blackSquare = squareTeams[BLACK];

	bool squareBool = (height % 2 == 0 && width % 2 == 0) ||
					  (height % 2 != 0 && width % 2 != 0);

	const char* squareTeam = squareBool ? whiteSquare : blackSquare;

	printf("%s%s", symbolTeam, squareTeam);

	printf(" ");

	printf("%s", symbol);

	printf(" ");

	printf("%s", "\033[0m");
}

void display_chess_result(Board board, Team winner)
{
	display_chess_board(board);

	if(winner == NONE)
	{
		CLEAR_LINE; printf("[!] THE GAME ENDED WITH A DRAW!\n");
	}
	else
	{
		char* team = (winner == WHITE) ? "WHITE" : "BLACK";
		CLEAR_LINE; printf("[!] THE WINNER IS [%s]!\n", team);
	}
}

void display_chess_info(Info info)
{
	char* team = (info.currTeam == WHITE) ? "WHITE" : "BLACK";

	CLEAR_LINE; printf("[+] CURRENT PLAYER\t: [%s]\n", team);
	CLEAR_LINE; printf("[+] NUMBER OF TURNS\t: [%dst]\n", info.turns);
}

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

	if(!strcmp(string, "RANDOM"))
	{
		return best_possible_move(move, board, info, 3, info.currTeam);
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
