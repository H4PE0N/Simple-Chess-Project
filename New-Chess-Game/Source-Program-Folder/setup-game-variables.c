
#include "../Header-Program-Folder/global-include-header.h"
#include "../Header-Program-Folder/setup-game-variables.h"

bool setup_game_variables(Board board, Info* info)
{
	char* filename = "Data-Files-Folder/starting-chess-board.txt";

	if(!create_chess_board(board, filename))
	{
		printf("Could not load board!\n");

		return false;
	}

	if(!setup_game_info(info, board))
	{
		printf("Could not create info!\n");

		return false;
	}

	return true;
}

bool setup_game_info(Info* info, Board board)
{
	RKSwitch whiteRKS = extract_rks_values(board, WHITE);
	RKSwitch blackRKS = extract_rks_values(board, BLACK);

	Point bKing, wKing;

	if(!board_piece_point(&bKing, board, (Piece) {KING, BLACK})) 
		return false;

	if(!board_piece_point(&wKing, board, (Piece) {KING, WHITE})) 
		return false;

	*info = (Info) {WHITE, whiteRKS, blackRKS, wKing, bKing, 0};

	return true;
}

RKSwitch extract_rks_values(Board board, Color color)
{
	return (RKSwitch) {true, true};
}

bool create_chess_board(Board board, char filename[])
{
	FILE* filePointer = fopen(filename, "r");

	if(filePointer == NULL)
	{
		printf("The file could not open\n");
		fclose(filePointer); return false;
	}

	if(!allocate_file_values(board, filePointer))
	{
		printf("Could not allocate file values\n");
		fclose(filePointer); return false;
	}

	fclose(filePointer); return true;
}

bool allocate_file_values(Board board, FILE* filePointer)
{
	char lineBuffer[20]; int height = 0;

	while(fgets(lineBuffer, 20, filePointer) != NULL)
	{
		board[height] = malloc(sizeof(Piece) * B_WIDTH);

		if(!extract_file_line(board, lineBuffer, height)) return false;
	
		height += 1;
	}
	return true;
}

bool extract_file_line(Board board, char lineBuffer[], int height)
{
	if(strlen(lineBuffer) < (B_WIDTH * 2)) return false;

	Piece piece;

	for(int index = 0; index < B_WIDTH; index += 1)
	{
		if(!extract_file_value(&piece, lineBuffer, index)) return false;
		append_board_piece(board, (Point) {height, index}, piece);
	}

	return true;
}

bool extract_file_value(Piece* piece, char lineBuffer[], int index)
{
	char type_c = lineBuffer[(index * 2) + 0];
	char color_c = lineBuffer[(index * 2) + 1];

	if(!number_inside_bounds(type_c, '0', '6')) return false;
	if(!number_inside_bounds(color_c, '0', '6')) return false;
	
	piece->type = (int) (type_c - '0');
	piece->color = (int) (color_c - '0');

	return true;
}