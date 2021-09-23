
#include "../Header-Program-Folder/interface-files-includer.h"

bool display_console_board(Board board, Info info)
{
	if(!display_chess_board(board)) return false;

	if(!display_game_info(info)) return false;

	return true;
}

bool display_chess_board(Board board)
{
	Point point;
	bool boolean = true;

	display_board_letters((char*) boardLetters);

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		CLEAR_LINE; printf("%c ", boardNumbers[height]);

		for(int width = 0; width < BOARD_WIDTH; width += 1)
		{
			point = (Point) {height, width};

			if(!display_board_symbol(board, point)) boolean = false;
		}

		printf("%c\n", boardNumbers[height]);
	}

	display_board_letters((char*) boardLetters);

	return boolean;
}

void display_board_letters(char letters[])
{
	CLEAR_LINE; printf("  ");
	for(int index = 0; index < BOARD_WIDTH; index += 1)
	{
		printf("%c ", letters[index]);
	}
	printf("\n");
}

bool display_board_symbol(Board board, Point point)
{
	if(!point_inside_board(point)) return false;

	Piece piece = board_point_piece(board, point);

	char symbol = extract_piece_symbol(piece);

	printf("%c ", symbol);

	return true;
}

char extract_piece_symbol(Piece piece)
{
	if(board_piece_empty(piece)) return '_';

	if(piece.team == WHITE) return whiteSymbols[piece.type];

	if(piece.team == BLACK) return blackSymbols[piece.type];

	return '_';
}

bool display_game_info(Info info)
{
	char teamString[20] = "\0";
	chess_team_string(teamString, info.current);

	char moveString[20] = "\0";
	chess_move_string(moveString, info.lastMove);

	CLEAR_LINE; printf("LAST MOVE : [%s]\n", moveString);
	CLEAR_LINE; printf("CURRENT   : [%s]\n", teamString);
	CLEAR_LINE; printf("TURNES    : [%dst]\n", info.turns);
	CLEAR_LINE; printf("COUNTER   : [%d]\n", info.counter);
	CLEAR_LINE; printf("PASSANT   : [%d %d]\n", info.passant.height, info.passant.width);
	CLEAR_LINE; printf("W CASTLES : [%d %d]\n", info.castles.white.queen, info.castles.white.king);
	CLEAR_LINE; printf("B CASTLES : [%d %d]\n", info.castles.black.queen, info.castles.black.king);

	return true;
}

bool display_game_result(Board board, Team winner)
{
	if(!display_chess_board(board)) return false;

	if(!piece_team_exists(winner))
	{
		char teamString[20] = "\0";
		if(!chess_team_string(teamString, winner)) return false;

		CLEAR_LINE; printf("[!] THE WINNER IS [%s]!\n", teamString);
	}
	else
	{
		CLEAR_LINE; printf("[!] THE GAME ENDED WITH A DRAW!\n");
	}
	return true;
}
