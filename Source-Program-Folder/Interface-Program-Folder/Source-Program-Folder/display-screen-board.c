
#include "../Header-Program-Folder/interface-files-includer.h"

const Color gridWhite = {255, 247, 204};
const Color gridBlack = {70, 50, 0};

const Color startColor = {100, 100, 100};
const Color stopColor = {100, 100, 100};

bool display_screen_board(Window* window, Renderer* renderer, Board board, Info info)
{
  if(!render_board_grid(renderer)) return false;

  render_last_move(renderer, info.lastMove);

  if(!render_board_pieces(renderer, board)) return false;

  SDL_UpdateWindowSurface(window);

  return true;
}

bool render_board_grid(Renderer* renderer)
{
	Color currentColor;

	Point point;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		for(int width = 0; width < BOARD_WIDTH; width += 1)
		{
      point = (Point) {height, width};

			currentColor = (Color) (((height + width) % 2 == 0) ? gridWhite : gridBlack);

			if(!color_point_square(renderer, point, currentColor)) return false;
		}
	}

  SDL_RenderPresent(renderer);

  return true;
}

bool color_point_square(Renderer* renderer, Point point, Color color)
{
	if(!point_inside_board(point)) return false;

	int height = (point.height * SQUARE_HEIGHT);
	int width = (point.width * SQUARE_WIDTH);

	Rect rectangle = (Rect) {width, height, SQUARE_WIDTH, SQUARE_HEIGHT};

	SDL_SetRenderDrawColor(renderer, color.r, color.b, color.g, 255);

	SDL_RenderFillRect(renderer, &rectangle);

	return true;
}

bool render_board_pieces(Renderer* renderer, Board board)
{
  Piece piece;
  Point point;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		for(int width = 0; width < BOARD_WIDTH; width += 1)
		{
			point = (Point) {height, width};
			piece = (Piece) board_point_piece(board, point);

			if(!render_board_piece(renderer, point, piece))
			{
				printf("Could not render piece!\n");

				return false;
			}
		}
	}

  SDL_RenderPresent(renderer);

  return true;
}

bool render_board_piece(Renderer* renderer, Point point, Piece piece)
{
  if(!point_inside_board(point)) return false;

	if(piece.type == EMPTY || piece.team == NONE) return true;

	int height = (point.height * SQUARE_HEIGHT);
	int width = (point.width * SQUARE_WIDTH);

	Rect position = {width, height, SQUARE_WIDTH, SQUARE_HEIGHT};

	if(!render_piece_image(renderer, piece, position))
	{
		printf("Could not render piece!\n");
		return false;
	}

  SDL_RenderPresent(renderer);

  return true;
}

bool render_piece_image(Renderer* renderer, Piece piece, Rect position)
{
	Surface* image = NULL;

	if(!extract_piece_image(&image, piece))
	{
		printf("image, could not extract!\n");
		return false;
	}

	if(!render_surface_texture(renderer, image, position))
	{
		printf("Could not render image!\n");
		return false;
	}

	SDL_FreeSurface(image);

	return true;
}

bool render_surface_texture(Renderer* renderer, Surface* surface, Rect position)
{
	Texture* texture = NULL;

	if(!create_surface_texture(&texture, renderer, surface))
	{
		return false;
	}

	SDL_RenderCopy(renderer, texture, NULL, &position);

	SDL_DestroyTexture(texture);

	return true;
}

bool render_piece_moves(Renderer* renderer, Board board, Info info, Point point)
{
  SDL_RenderPresent(renderer);

  return true;
}

bool render_last_move(Renderer* renderer, Move move)
{
  if(!move_inside_board(move)) return false;

	if(!color_point_square(renderer, move.start, startColor)) return false;
	if(!color_point_square(renderer, move.stop, stopColor)) return false;

  SDL_RenderPresent(renderer);

  return true;
}
