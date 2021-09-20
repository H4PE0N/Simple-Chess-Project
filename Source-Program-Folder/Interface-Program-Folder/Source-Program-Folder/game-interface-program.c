
#include "../Header-Program-Folder/interface-files-includer.h"

const Color whiteColor = {0, 255, 255};
const Color blackColor = {0, 0, 255};

void render_chess_board(Render* renderer)
{
	Color white = {255, 247, 204};
	Color black = {70, 50, 0};
	Color currentColor;

	Rect rectangle;

	int realHeight, realWidth;

	for(int height = 0; height < 8; height += 1)
	{
		for(int width = 0; width < 8; width += 1)
		{
			realHeight = (height * SQUARE_HEIGHT);
			realWidth = (width * SQUARE_WIDTH);

			rectangle = (Rect) {realWidth, realHeight, SQUARE_WIDTH, SQUARE_HEIGHT};

			currentColor = (Color) (((height + width) % 2 == 0) ? white : black);

			SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.b, currentColor.g, 255);

			SDL_RenderFillRect(renderer, &rectangle);
		}
	}
}

bool render_full_board(Render* renderer, Board board)
{
	render_chess_board(renderer);

	Piece piece; Point point;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		for(int width = 0; width < BOARD_WIDTH; width += 1)
		{
			point = (Point) {height, width};
			piece = (Piece) board_point_piece(board, point);

			if(!render_board_piece(renderer, piece, point))
			{
				printf("Could not render piece!\n");

				return false;
			}
		}
	}

	SDL_RenderPresent(renderer);

	return true;
}

bool render_board_piece(Render* renderer, Piece piece, Point point)
{
	if(!point_inside_board(point)) return false;
	if(piece.type == EMPTY || piece.team == NONE) return true;

	int height = (point.height * SQUARE_HEIGHT);
	int width = (point.width * SQUARE_WIDTH);

	Rect position = {width, height, SQUARE_WIDTH, SQUARE_HEIGHT};

	Surface* image = extract_piece_image(piece);

	if(image == NULL)
	{
		printf("image, could not extract!\n");
		return false;
	}

	Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	if(texture == NULL)
	{
		printf("Read image error %s\n", SDL_GetError());
		return false;
	}

	SDL_RenderCopy(renderer, texture, NULL, &position);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);

	return true;
}

Surface* extract_piece_image(Piece piece)
{
	char filename[200]; extract_piece_filename(filename, piece);

	return IMG_Load(filename);
}

const char* typeStrings[] = {"EMPTY", "PAWN", "BISHOP", "KNIGHT", "ROOK", "QUEEN", "KING"};
const char* teamStrings[] = {"NONE", "WHITE", "BLACK"};

bool extract_piece_filename(char* filename, Piece piece)
{
	if(!number_inside_bounds(piece.type, 0, 6)) return false;
	if(!number_inside_bounds(piece.team, 0, 2)) return false;

	const char* typeString = typeStrings[piece.type];
	const char* teamString = teamStrings[piece.team];

	char file[200];

	sprintf(file, "%s-%s.png", teamString, typeString);

	sprintf(filename, "%s/%s", PIECE_FOLDER, file);

	//printf("Filename: %s\n", filename);

	return true;
}
