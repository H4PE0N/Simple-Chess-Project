
#include "../Header-Program-Folder/interface-files-includer.h"

// bool display_screen_board(Window* window, Renderer* render, Board board, Info info)
// {
//   if(!render_board_grid(renderer)) return false;
//
//   if(!render_last_move(renderer, info.lastMove)) return false;
//
//   if(!render_board_pieces(renderer, board)) return false;
//
//
//
//   return true;
// }
//
// bool render_board_grid(Renderer* renderer)
// {
//   SDL_RenderPresent(renderer);
//
//   return true;
// }
//
// bool render_board_pieces(Renderer* renderer, Board board)
// {
//   SDL_RenderPresent(renderer);
//
//   return true;
// }
//
// bool render_board_piece(Renderer* renderer, Board board)
// {
//   SDL_RenderPresent(renderer);
//
//   return true;
// }
//
// bool render_piece_moves(Renderer* renderer, Board board, Info info, Point point)
// {
//   SDL_RenderPresent(renderer);
//
//   return true;
// }
//
// bool render_last_move(Renderer* renderer, Move move)
// {
//   SDL_RenderPresent(renderer);
//
//   return true;
// }



// const Color whiteColor = {0, 255, 255};
// const Color blackColor = {0, 0, 255};

// void render_chess_board(Render* renderer)
// {
// 	Color white = {255, 247, 204};
// 	Color black = {70, 50, 0};
// 	Color currentColor;
//
// 	Rect rectangle;
//
// 	int realHeight, realWidth;
//
// 	for(int height = 0; height < 8; height += 1)
// 	{
// 		for(int width = 0; width < 8; width += 1)
// 		{
// 			realHeight = (height * SQUARE_HEIGHT);
// 			realWidth = (width * SQUARE_WIDTH);
//
// 			rectangle = (Rect) {realWidth, realHeight, SQUARE_WIDTH, SQUARE_HEIGHT};
//
// 			currentColor = (Color) (((height + width) % 2 == 0) ? white : black);
//
// 			SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.b, currentColor.g, 255);
//
// 			SDL_RenderFillRect(renderer, &rectangle);
// 		}
// 	}
// }
//
// bool render_full_board(Render* renderer, Board board)
// {
// 	render_chess_board(renderer);
//
// 	Piece piece; Point point;
//
// 	for(int height = 0; height < BOARD_HEIGHT; height += 1)
// 	{
// 		for(int width = 0; width < BOARD_WIDTH; width += 1)
// 		{
// 			point = (Point) {height, width};
// 			piece = (Piece) board_point_piece(board, point);
//
// 			if(!render_board_piece(renderer, piece, point))
// 			{
// 				printf("Could not render piece!\n");
//
// 				return false;
// 			}
// 		}
// 	}
//
// 	SDL_RenderPresent(renderer);
//
// 	return true;
// }
//
// bool render_board_piece(Render* render, Piece piece, Point point)
// {
// 	if(!point_inside_board(point)) return false;
//
// 	if(piece.type == EMPTY || piece.team == NONE) return true;
//
// 	int height = (point.height * SQUARE_HEIGHT);
// 	int width = (point.width * SQUARE_WIDTH);
//
// 	Rect position = {width, height, SQUARE_WIDTH, SQUARE_HEIGHT};
//
// 	if(!render_piece_image(render, piece, position))
// 	{
// 		printf("Could not render piece!\n");
// 		return false;
// 	}
//
// 	return true;
// }
//
// bool render_piece_image(Render* render, Piece piece, Rect position)
// {
// 	Surface* image = NULL;
//
// 	if(!extract_piece_image(&image, piece))
// 	{
// 		printf("image, could not extract!\n");
// 		return false;
// 	}
//
// 	if(!render_surface_texture(render, image, position))
// 	{
// 		printf("Could not render image!\n");
// 		return false;
// 	}
//
// 	SDL_FreeSurface(image);
//
// 	return true;
// }
//
// bool render_surface_texture(Render* render, Surface* surface, Rect position)
// {
// 	Texture* texture = NULL;
//
// 	if(!create_surface_texture(&texture, render, surface))
// 	{
// 		return false;
// 	}
//
// 	SDL_RenderCopy(render, texture, NULL, &position);
//
// 	SDL_DestroyTexture(texture);
//
// 	return true;
// }
