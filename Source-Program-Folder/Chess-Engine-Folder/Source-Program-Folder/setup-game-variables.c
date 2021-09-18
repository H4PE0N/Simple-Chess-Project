
#include "../Header-Program-Folder/chess-engine-includer.h"

bool setup_game_variables(Board* board, Info* info, char filename[])
{
	if(!create_chess_board(board, filename))
	{
		create_board_error(filename);

		return false;
	}

	if(!setup_game_info(info, *board))
	{
		setup_info_error(*board);

		return false;
	}

	return true;
}

bool setup_game_info(Info* info, Board board)
{
	Castle whiteRKS = extract_rks_values(board, WHITE);
	Castle blackRKS = extract_rks_values(board, BLACK);

	Point blackKing, whiteKing;

	if(!board_piece_point(&blackKing, board, (Piece) {KING, BLACK})) return false;
	if(!board_piece_point(&whiteKing, board, (Piece) {KING, WHITE})) return false;

	Move lastMove = {(Point) {-1, -1}, (Point) {-1, -1}};
	int turns = 0;

	*info = (Info) {WHITE, whiteRKS, blackRKS, whiteKing, blackKing, turns, lastMove};

	return true;
}

Castle extract_rks_values(Board board, Team team)
{
	if(!piece_team_exists(team)) return (Castle) {false, false};

	Castle rKSwitch = {false, false};
	Point king;

	int expectedHeight = (team == WHITE) ? (BOARD_HEIGHT - 1) : 0;

	if(!board_piece_point(&king, board, (Piece) {KING, team})) return (Castle) {false, false};

	if(!board_points_equal(king, (Point) {expectedHeight, 4})) return (Castle) {false, false};

	//Now the king exists and is in the right place

	// It could be 64 rooks in the same team in the board
	Point* rooks = create_point_array(64);

	// If there is no rooks on the board;
	if(!board_piece_points(rooks, board, (Piece) {ROOK, team}))
	{
		free(rooks);

		return (Castle) {false, false};
	}

	int amount = point_array_amount(rooks);

	Point currRook;

	for(int index = 0; index < amount; index += 1)
	{
		currRook = rooks[index];

		if(currRook.height != expectedHeight) continue;

		// Now the height is right;

		if(currRook.width == 0) 			rKSwitch.queen = true;
		if(currRook.width == (BOARD_WIDTH - 1)) rKSwitch.king = true;
	}

	free(rooks);

	return rKSwitch;
}

bool create_chess_board(Board* board, char filename[])
{
	FILE* filePointer = fopen(filename, "r");

	if(filePointer == NULL)
	{
		file_pointer_error(filename);

		fclose(filePointer); return false;
	}

	if(!allocate_file_values(board, filePointer))
	{
		file_values_error(filename);

		fclose(filePointer); return false;
	}

	fclose(filePointer); return true;
}

bool allocate_file_values(Board* board, FILE* filePointer)
{
	(*board) = malloc(sizeof(Piece*) * BOARD_HEIGHT);
	char lineBuffer[1024];

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		if(fgets(lineBuffer, 1024, filePointer) == NULL) return false;

		(*board)[height] = malloc(sizeof(Piece) * BOARD_WIDTH);

		if(!extract_file_line(*board, lineBuffer, height)) return false;
	}
	return true;
}

bool extract_file_line(Board board, char lineBuffer[], int height)
{
	if(strlen(lineBuffer) < (BOARD_WIDTH * 2)) return false;

	Piece piece;

	for(int index = 0; index < BOARD_WIDTH; index += 1)
	{
		if(!extract_file_value(&piece, lineBuffer, index)) return false;
		append_board_piece(board, (Point) {height, index}, piece);
	}

	return true;
}

bool extract_file_value(Piece* piece, char lineBuffer[], int index)
{
	char typeChar = lineBuffer[(index * 2) + 0];
	char teamChar = lineBuffer[(index * 2) + 1];

	if(!number_inside_bounds(typeChar, '0', '6')) return false;
	if(!number_inside_bounds(teamChar, '0', '2')) return false;

	Type type = (Type) (typeChar - '0');
	Team team = (Team) (teamChar - '0');

	if(type != EMPTY && team == NONE) return false;
	if(team != NONE && type == EMPTY) return false;

	piece->type = type;
	piece->team = team;

	return true;
}
