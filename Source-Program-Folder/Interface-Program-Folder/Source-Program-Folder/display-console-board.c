
#include "../Header-Program-Folder/interface-files-includer.h"

bool display_chess_board(Board board)
{
	Point point;
	bool boolean = true;

	display_board_letters((char*) boardLetters);

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		printf("%c ", boardNumbers[height]);

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
	printf("  ");
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
	// if(!chess_team_string(teamString, info.current))
	chess_team_string(teamString, info.current);

	char moveString[20] = "\0";
	// if(!chess_move_string(moveString, info.lastMove))
	chess_move_string(moveString, info.lastMove);

	printf("%s[%s]\n", LAST_MOVE_OUTPUT, moveString);

	printf("%s[%s]\n", CURRENT_TEAM_OUTPUT, teamString);

	printf("%s[%dst]\n", TURNS_OUTPUT, info.turns);

	printf("%s[%d]\n", COUNTER_OUTPUT, info.counter);

	printf("%s[%d %d]\n", PASSANT_OUTPUT, info.passant.height, info.passant.width);

	printf("%s[%d %d]\n", WHITE_CASTLE_OUTPUT, info.castles.white.queen, info.castles.white.king);
	
	printf("%s[%d %d]\n", BLACK_CASTLE_OUTPUT, info.castles.black.queen, info.castles.black.king);

	return true;
}
