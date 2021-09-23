
#ifndef DISPLAY_SCREEN_BOARD_H
#define DISPLAY_SCREEN_BOARD_H

bool display_screen_board(Window*, Renderer*, Board board, Info info);

bool render_board_grid(Renderer*);

bool render_board_pieces(Renderer*, Board);

bool render_board_piece(Renderer*, Point, Piece);

bool render_piece_moves(Renderer*, Board, Info, Point);

bool render_last_move(Renderer*, Move);

#endif
