
#include "../Header-Program-Folder/game-files-includer.h"

bool display_console_board(Board board, Info info)
{
	if(!display_chess_board(board))
	{
		printf("Could not display console board!\n");

		return false;
	}

	if(!display_game_info(info))
	{
		printf("Could not display conosle game info\n");

		return false;
	}

	return true;
}

bool render_screen_board(Renderer* renderer, Board board, Info info)
{
  if(!render_board_grid(renderer))
  {
    printf("Could not render board grid!\n");

    return false;
  }

  if(move_inside_board(info.lastMove))
  {
    if(!render_board_move(renderer, info.lastMove, BOARD_MOVE_COLOR))
    {
      printf("Could not render board move!\n");

      return false;
    }
  }

  if(!render_check_squares(renderer, board))
  {
    printf("Could not render check squares!\n");

    return false;
  }

  if(!render_board_pieces(renderer, board))
  {
    printf("Could not render board pieces!\n");

    return false;
  }

  return true;
}

bool render_color_board(Renderer* renderer, Board board, Color color)
{
  if(!render_board_color(renderer, color))
  {
    printf("Could not color board!\n");

    return false;
  }

  if(!render_board_pieces(renderer, board))
  {
    printf("Could not render board pieces!\n");

    return false;
  }

  return true;
}

bool render_movable_board(Renderer* renderer, Board board, Info info, Point point)
{
	if(!render_piece_moves(renderer, board, info, point))
	{
		printf("Could not render piece moves!\n");

		return false;
	}

	if(!render_board_pieces(renderer, board))
	{
		printf("Could not render board pieces!\n");

		return false;
	}

	return true;
}