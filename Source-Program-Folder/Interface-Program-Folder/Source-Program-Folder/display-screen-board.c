
#include "../Header-Program-Folder/interface-files-includer.h"

bool display_screen_board(Window* window, Renderer* renderer, Board board, Info info)
{
  if(!render_board_grid(renderer)) return false;

  if(!render_last_move(renderer, info.lastMove)) return false;

  if(!render_board_pieces(renderer, board)) return false;



  return true;
}

bool render_board_grid(Renderer* renderer)
{
  SDL_RenderPresent(renderer);

  return true;
}

bool render_board_pieces(Renderer* renderer, Board board)
{
  SDL_RenderPresent(renderer);

  return true;
}

bool render_board_piece(Renderer* renderer, Point point, Piece piece)
{
  SDL_RenderPresent(renderer);

  return true;
}

bool render_piece_moves(Renderer* renderer, Board board, Info info, Point point)
{
  SDL_RenderPresent(renderer);

  return true;
}

bool render_last_move(Renderer* renderer, Move move)
{
  SDL_RenderPresent(renderer);

  return true;
}
