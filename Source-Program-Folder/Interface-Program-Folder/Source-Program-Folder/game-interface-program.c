
#include "../Header-Program-Folder/interface-files-includer.h"

const char* blackSymbols[] = {" ", "P", "B", "H", "R", "Q", "K"};
const char* whiteSymbols[] = {" ", "p", "b", "h", "r", "q", "k"};

#define DIS_LETS "  | A | B | C | D | E | F | G | H |"
#define DIS_ROW "--+---+---+---+---+---+---+---+---+--"

void extract_file_name(char* filename, char* arguments[], int amount)
{
	if(amount >= 2) strcpy(filename, arguments[1]);

	else strcpy(filename, STD_FILE);
}

// const Color whiteColor = {0, 255, 255};
// const Color blackColor = {0, 0, 255};

// void render_chess_board(SDL_Renderer* renderer)
// {
// 	SDL_Color white = {255, 247, 204};
// 	SDL_Color black = {70, 50, 0};
// 	SDL_Color currentColor;

// 	SDL_Rect rectangle;

// 	int realHeight, realWidth;

// 	for(int height = 0; height < 8; height += 1)
// 	{
// 		for(int width = 0; width < 8; width += 1)
// 		{
// 			realHeight = (height * SQUARE_HEIGHT);
// 			realWidth = (width * SQUARE_WIDTH);

// 			rectangle = (SDL_Rect) {realWidth, realHeight, SQUARE_WIDTH, SQUARE_HEIGHT};

// 			currentColor = (SDL_Color) (((height + width) % 2 == 0) ? white : black);

// 			SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.b, currentColor.g, 255);

// 			SDL_RenderFillRect(renderer, &rectangle);
// 		}
// 	}
// }

// bool render_full_board(Render* renderer, Board board)
// {
// 	render_chess_board(renderer);

// 	Piece piece; Point point;

// 	for(int height = 0; height < BOARD_HEIGHT; height += 1)
// 	{
// 		for(int width = 0; width < BOARD_WIDTH; width += 1)
// 		{
// 			point = (Point) {height, width};
// 			piece = (Piece) board_point_piece(board, point);

// 			if(!render_board_piece(renderer, piece, point))
// 			{
// 				printf("Could not render piece!\n");

// 				return false;
// 			}
// 		}
// 	}
// 	return true;
// }

// bool render_board_piece(Render* renderer, Piece piece, Point point)
// {
// 	if(!point_inside_board(point)) return false;
// 	if(piece.type == EMPTY || piece.team == NONE) return true;

// 	int height = (point.height * SQUARE_HEIGHT);
// 	int width = (point.width * SQUARE_WIDTH);

// 	Rect position = {width, height, SQUARE_WIDTH, SQUARE_HEIGHT};

// 	Surface* image = extract_piece_image(piece);

// 	if(image == NULL)
// 	{
// 		printf("ErrorG, could not extract!\n");
// 		return false;
// 	}

// 	Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

// 	if(texture == NULL)
// 	{
// 		printf("Read image error %s\n", SDL_GetError());
// 		return false;
// 	}

// 	SDL_RenderCopy(renderer, texture, NULL, &position);

// 	SDL_DestroyTexture(texture);
// 	SDL_FreeSurface(image);

// 	return true;
// }

// Surface* extract_piece_image(Piece piece)
// {
// 	char filename[200]; extract_piece_filename(filename, piece);

// 	return IMG_Load(filename);
// }

// const char* typeStrings[] = {"EMPTY", "PAWN", "BISHOP", "KNIGHT", "ROOK", "QUEEN", "KING"};
// const char* teamStrings[] = {"NONE", "WHITE", "BLACK"};

// bool extract_piece_filename(char* filename, Piece piece)
// {
// 	if(!number_inside_bounds(piece.type, 0, 6)) return false;
// 	if(!number_inside_bounds(piece.team, 0, 2)) return false;

// 	const char* typeString = typeStrings[piece.type];
// 	const char* teamString = teamStrings[piece.team];

// 	char file[200];

// 	sprintf(file, "%s-%s.png", teamString, typeString);

// 	sprintf(filename, "%s/%s", PIECE_FOLDER, file);

// 	//printf("Filename: %s\n", filename);

// 	return true;
// }

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
	char* teamString = (info.currTeam == WHITE) ? "WHITE" : "BLACK";

	char moveString[20] = "\0"; chess_move_string(moveString, info.lastMove);

	// CLEAR_LINE; printf("WHITE RKS (%d %d)\n", info.whiteRKS.left, info.whiteRKS.right);
	// CLEAR_LINE; printf("BLACK RKS (%d %d)\n", info.blackRKS.left, info.blackRKS.right);

	CLEAR_LINE; printf("[+] LAST MADE MOVE  : [%s]\n", moveString);
	CLEAR_LINE; printf("[+] CURRENT PLAYER  : [%s]\n", teamString);
	CLEAR_LINE; printf("[+] NUMBER OF TURNS : [%dst]\n", info.turns);
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

	if(!strcmp(string, "HELP"))
	{
		return help_move_parser(move, board, info, string);
	}
	else if(!strcmp(string, "HINT"))
	{
		return hint_move_parser(move, board, info, string);
	}
	else if(!strcmp(string, "SAVE"))
	{
		return save_move_parser(move, board, info, string);
	}
	else
	{
		return default_move_parser(move, board, info, string);
	}
	return false;
}

bool help_move_parser(Move* move, Board board, Info info, char string[])
{
	return best_possible_move(move, board, info, STD_DEPTH, info.currTeam);
}

bool hint_move_parser(Move* move, Board board, Info info, char string[])
{
	Move hintMove;
	if(!best_possible_move(&hintMove, board, info, STD_DEPTH, info.currTeam)) return false;

	char moveString[20];
	if(!chess_move_string(moveString, hintMove)) return false;

	CLEAR_LINE; printf("[!] HINT OF GOOD MOVE: [%s]\n", moveString);

	return false;
}

bool save_move_parser(Move* move, Board board, Info info, char string[])
{
	FILE* filePointer = fopen(SAVE_FILE, "w");

	if(filePointer == NULL)
	{
		file_pointer_error(SAVE_FILE);

		fclose(filePointer); return false;
	}

	Point point;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		char boardLine[20];

		for(int width = 0; width < BOARD_WIDTH; width += 1)
		{
			point = (Point) {height, width};
			int type = board_point_type(board, point);
			int team = board_point_team(board, point);

			boardLine[width * 2]		= (type + '0');
			boardLine[(width * 2) + 1]	= (team + '0');
		}

		boardLine[BOARD_WIDTH * 2] = '\n';
		fwrite(boardLine, sizeof(char), 17, filePointer);
	}

	CLEAR_LINE; printf("[!] SAVED THE CURRENT BOARD!\n");

	fclose(filePointer); return true;
}

bool default_move_parser(Move* move, Board board, Info info, char string[])
{
	char seperator[] = " ";

	char* startString = strtok(string, seperator);
	char* stopString = strtok(NULL, seperator);

	if(startString == NULL || stopString == NULL) return false;

	Point start, stop;

	if(!parse_chess_position(&start, startString)) return false;
	if(!parse_chess_position(&stop, stopString)) return false;

	*move = (Move) {start, stop}; return true;
}

bool parse_chess_position(Point* point, char string[])
{
	if(strlen(string) < 2 || strlen(string) > 2) return false;

	int width = string_letter_index((char*) letters, BOARD_WIDTH, string[0]);
	int height = string_letter_index((char*) numbers, BOARD_HEIGHT, string[1]);

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
