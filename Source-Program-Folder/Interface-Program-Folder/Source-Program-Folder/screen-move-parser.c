
#include "../Header-Program-Folder/interface-files-includer.h"

const Color hintColor = {0, 255, 150};

bool input_screen_move(Move* move, Window* window, Renderer* renderer, Board board, Info info)
{
  Move inputMove = EMPTY_MOVE;
  Event event;

	while(!move_inside_board(inputMove))
	{
		if(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_q) return false;

      if(!screen_move_parser(&inputMove, window, renderer, board, info, event)) continue;
    }
	}

	*move = inputMove;

	return true;
}

bool screen_move_parser(Move* move, Window* window, Renderer* renderer, Board board, Info info, Event event)
{
  if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g)
  {
    return screen_help_parser(move, window, renderer, board, info);
  }
  else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_h)
  {
    return screen_hint_parser(move, window, renderer, board, info);
  }
  return screen_default_parser(move, window, renderer, board, info, event);
}

bool screen_help_parser(Move* move, Window* window, Renderer* renderer, Board board, Info info)
{
  display_screen_board(window, renderer, board, info);
  SDL_UpdateWindowSurface(window);

  return best_possible_move(move, board, info, STD_DEPTH, info.current);
}

bool screen_hint_parser(Move* move, Window* window, Renderer* renderer, Board board, Info info)
{
  Move hintMove;
	if(!best_possible_move(&hintMove, board, info, STD_DEPTH, info.current)) return false;

  display_screen_board(window, renderer, board, info);

	if(!color_point_square(renderer, hintMove.stop, hintColor)) return false;

  SDL_UpdateWindowSurface(window);

	*move = EMPTY_MOVE;

	return false;
}

bool screen_default_parser(Move* move, Window* window, Renderer* renderer, Board board, Info info, Event event)
{
  if(event.type == SDL_MOUSEBUTTONDOWN)
  {
    display_screen_board(window, renderer, board, info);
    SDL_UpdateWindowSurface(window);
  }
  else if(event.type == SDL_MOUSEBUTTONUP)
  {
    display_screen_board(window, renderer, board, info);
    SDL_UpdateWindowSurface(window);
  }

  return false;
}
