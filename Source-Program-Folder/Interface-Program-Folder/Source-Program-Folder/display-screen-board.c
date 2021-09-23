
#include "../Header-Program-Folder/interface-files-includer.h"

const Color gridWhite = {232, 235, 239};
const Color gridBlack = {125, 135, 150};

const Color moveColor = {100, 100, 100};

const Color hintColor = {0, 255, 150};
const Color quitColor = {255, 0, 0};

const Color movableColor = {0, 0, 255};
const Color checkColor = {255, 0, 0};

bool render_screen_board(Renderer* renderer, Board board, Info info)
{
  if(!render_board_grid(renderer)) return false;

  render_board_move(renderer, info.lastMove, moveColor);

  if(!render_board_pieces(renderer, board)) return false;

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

bool render_quit_board(Renderer* renderer, Board board)
{
  if(!render_board_color(renderer, quitColor)) return false;

  if(!render_board_pieces(renderer, board)) return false;

  return true;
}

bool render_board_color(Renderer* renderer, Color color)
{
  Point point;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		for(int width = 0; width < BOARD_WIDTH; width += 1)
		{
      point = (Point) {height, width};

			if(!color_point_square(renderer, point, color)) return false;
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
  if(!point_inside_board(point)) return false;
  if(board_point_team(board, point) != info.current) return false;

  Move* moves = create_moves_array(32);

  if(!piece_possible_moves(moves, board, info, point))
  {
    free(moves);

    return true;
  }

  int amount = moves_array_amount(moves);

  for(int index = 0; index < amount; index += 1)
  {
    render_board_move(renderer, moves[index], movableColor);
  }

  free(moves);

  render_board_pieces(renderer, board);

  SDL_RenderPresent(renderer);

  return true;
}

bool render_board_move(Renderer* renderer, Move move, Color color)
{
  if(!move_inside_board(move)) return false;

	if(!color_point_square(renderer, move.start, color)) return false;
	if(!color_point_square(renderer, move.stop, color)) return false;

  SDL_RenderPresent(renderer);

  return true;
}
