
#include "../Header-Program-Folder/interface-files-includer.h"

const char* blackSymbols[] = {" ", "P", "B", "H", "R", "Q", "K"};
const char* whiteSymbols[] = {" ", "p", "b", "h", "r", "q", "k"};

#define DIS_LETS "  | A | B | C | D | E | F | G | H |"
#define DIS_ROW "--+---+---+---+---+---+---+---+---+--"

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
// 		printf("image, could not extract!\n");
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
	char* teamString = (info.current == WHITE) ? "WHITE" : "BLACK";

	char moveString[20] = "\0"; chess_move_string(moveString, info.lastMove);

	// CLEAR_LINE; printf("WHITE RKS (%d %d)\n", info.whiteRKS.left, info.whiteRKS.right);
	// CLEAR_LINE; printf("BLACK RKS (%d %d)\n", info.blackRKS.left, info.blackRKS.right);

	CLEAR_LINE; printf("[+] LAST MADE MOVE  : [%s]\n", moveString);
	CLEAR_LINE; printf("[+] CURRENT PLAYER  : [%s]\n", teamString);
	CLEAR_LINE; printf("[+] NUMBER OF TURNS : [%dst]\n", info.turns);
}
