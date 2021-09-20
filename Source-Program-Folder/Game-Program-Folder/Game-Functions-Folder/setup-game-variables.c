
#include "../Header-Program-Folder/game-files-includer.h"

bool setup_display_variables(Window** window, Render** render, Surface** surface, char title[])
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Init Error: %s\n", SDL_GetError());

		return false;
	}

	if(IMG_Init(IMG_INIT_PNG) == 0)
	{
		printf("Init Error: %s\n", SDL_GetError());

		SDL_Quit();

		return false;
	}

	if(!create_screen_window(window, (Point) {0, 0}, title))
	{
		printf("Window Error: %s\n", SDL_GetError());

		SDL_Quit();

		return false;
	}

	if(!create_window_surface(surface, *window))
	{
		printf("Surface is null: %s\n", SDL_GetError());

		SDL_DestroyWindow(*window);

		SDL_Quit();

		return false;
	}

	if(!create_surface_render(render, *surface))
	{
		printf("Render is null: %s\n", SDL_GetError());

		SDL_FreeSurface(*surface);

		SDL_DestroyWindow(*window);

		SDL_Quit();

		return false;
	}

	// This line is just needed to make the window want to show it self:
	SDL_Event event; SDL_PollEvent(&event);

	return true;
}

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

		free_chess_board(*board);

		return false;
	}

	return true;
}

bool setup_game_info(Info* info, Board board)
{
	Castles castles = extract_castles_values(board);

	Team current = WHITE;

	Move lastMove = EMPTY_MOVE;
	Point passant = EMPTY_POINT;

	int counter = 0;
	int turns = 0;

	*info = (Info) {current, castles, passant, counter, turns, lastMove};

	return true;
}

Castles extract_castles_values(Board board)
{
	Castle white = extract_castle_values(board, WHITE);
	Castle black = extract_castle_values(board, BLACK);

	return (Castles) {white, black};
}

Castle extract_castle_values(Board board, Team team)
{
	if(!piece_team_exists(team)) EMPTY_CASTLE;

	Castle castle = EMPTY_CASTLE;

	int expectedHeight = (team == WHITE) ? (BOARD_HEIGHT - 1) : 0;


	Point king = board_piece_point(board, (Piece) {KING, team});

	if(!point_inside_board(king)) return EMPTY_CASTLE;


	if(!board_points_equal(king, (Point) {expectedHeight, 4})) return EMPTY_CASTLE;

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

	Point currentRook;

	for(int index = 0; index < amount; index += 1)
	{
		currentRook = rooks[index];

		if(currentRook.height != expectedHeight) continue;

		// Now the height is right;

		if(currentRook.width == 0) 			castle.queen = true;
		if(currentRook.width == (BOARD_WIDTH - 1)) castle.king = true;
	}

	free(rooks);

	return castle;
}

bool create_chess_board(Board* board, char filename[])
{
	FILE* filePointer = fopen(filename, "r");

	if(filePointer == NULL)
	{
		file_pointer_error(filename);

		//fclose(filePointer);

		return false;
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
		allocate_board_piece(board, (Point) {height, index}, piece);
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
