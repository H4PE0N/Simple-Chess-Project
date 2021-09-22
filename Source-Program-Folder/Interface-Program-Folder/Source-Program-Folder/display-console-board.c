
#include "../Header-Program-Folder/interface-files-includer.h"

const char* blackSymbols[] = {" ", "P", "B", "H", "R", "Q", "K"};
const char* whiteSymbols[] = {" ", "p", "b", "h", "r", "q", "k"};

#define DIS_LETS "  | A | B | C | D | E | F | G | H |"
#define DIS_ROW "--+---+---+---+---+---+---+---+---+--"

void display_chess_board(Board board)
{
	CLEAR_LINE; printf("%s\n", DIS_LETS);

	for(int height = 0; height < BOARD_HEIGHT; height = height + 1)
	{
		CLEAR_LINE; printf("%s\n", DIS_ROW);

		CLEAR_LINE; printf("%c", numbers[height]);

		printf(" ");

		for(int width = 0; width < BOARD_WIDTH; width = width + 1)
		{
			printf("|");

			Piece piece = board[height][width];
			display_board_symbol(height, width, piece);
		}

		printf("|"); printf(" ");

		printf("%c", numbers[height]);

		printf("\n");
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

	printf(" ");

	printf("%s", symbol);

	printf(" ");
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
	char* teamString = (info.current == WHITE) ? "WHITE" : "BLACK";

	char moveString[20] = "\0"; chess_move_string(moveString, info.lastMove);

	// CLEAR_LINE; printf("WHITE RKS (%d %d)\n", info.castles.white.queen, info.castles.white.king);
	// CLEAR_LINE; printf("BLACK RKS (%d %d)\n", info.castles.black.queen, info.castles.black.king);
	// CLEAR_LINE; printf("PASSANT: [%d %d]\n", info.passant.height, info.passant.width);

	CLEAR_LINE; printf("[+] LAST MADE MOVE  : [%s]\n", moveString);
	CLEAR_LINE; printf("[+] CURRENT PLAYER  : [%s]\n", teamString);
	CLEAR_LINE; printf("[+] NUMBER OF TURNS : [%dst]\n", info.turns);
}
