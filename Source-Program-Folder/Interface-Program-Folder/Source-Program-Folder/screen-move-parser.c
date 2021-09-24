
#include "../Header-Program-Folder/interface-files-includer.h"

bool input_screen_move(Move* move, Window* window, Renderer* renderer, Board board, Info info)
{
  Move inputMove = EMPTY_MOVE;
  Event event;

	while(!move_inside_board(inputMove))
	{
		if(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q))
      {
        // if(!render_color_board(renderer, board, quitColor)) continue;
        render_color_board(renderer, board, quitColor);
        SDL_UpdateWindowSurface(window);

        char string[20];

        printf("ACTION: ");
        scanf("%s", string); fflush(stdin);

        convert_string_upper(string, strlen(string));

        if(!strcmp(string, "STOP")) return false;

        render_screen_board(renderer, board, info);
        SDL_UpdateWindowSurface(window);
      }
      else if(!screen_move_parser(&inputMove, window, renderer, board, info, event))
      {
        continue;
      }
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
  if(!render_screen_board(renderer, board, info)) return false;
  SDL_UpdateWindowSurface(window);

  return best_possible_move(move, board, info, STD_DEPTH, info.current);
}

bool screen_hint_parser(Move* move, Window* window, Renderer* renderer, Board board, Info info)
{
  Move hintMove;
	if(!best_possible_move(&hintMove, board, info, STD_DEPTH, info.current)) return false;

  if(!render_screen_board(renderer, board, info)) return false;

	if(!render_board_move(renderer, hintMove, hintColor)) return false;

  if(!render_board_pieces(renderer, board)) return false;

  SDL_UpdateWindowSurface(window);

	return true;
}

bool screen_default_parser(Move* move, Window* window, Renderer* renderer, Board board, Info info, Event event)
{
  if(event.type == SDL_MOUSEBUTTONDOWN)
  {
    if(!render_screen_board(renderer, board, info)) return false;
    SDL_UpdateWindowSurface(window);

    move->start = parse_mouse_point(event);

    if(!render_piece_moves(renderer, board, info, move->start)) return false;
    SDL_UpdateWindowSurface(window);

    Event upEvent;

    while(upEvent.type != SDL_MOUSEBUTTONUP)
    {
      SDL_PollEvent(&upEvent);
    }

    move->stop = parse_mouse_point(upEvent);

    return true;
  }

  return false;
}

Point parse_mouse_point(Event event)
{
  float squareHeight = SQUARE_HEIGHT;
  float squareWidth = SQUARE_WIDTH;

  int width = floor( (float) event.motion.x / squareWidth);
  int height = floor( (float) event.motion.y / squareHeight);

  return (Point) {height, width};
}
