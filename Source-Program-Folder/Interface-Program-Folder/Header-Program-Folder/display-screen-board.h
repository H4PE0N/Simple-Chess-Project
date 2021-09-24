
#ifndef DISPLAY_SCREEN_BOARD_H
#define DISPLAY_SCREEN_BOARD_H

bool render_screen_board(Renderer*, Board, Info);

bool render_board_grid(Renderer*);

bool render_board_color(Renderer*, Color);

bool render_check_squares(Renderer*, Board);

bool render_color_board(Renderer*, Board, Color);

bool render_board_pieces(Renderer*, Board);

bool render_board_piece(Renderer*, Point, Piece);

bool render_piece_moves(Renderer*, Board, Info, Point);

bool render_board_move(Renderer*, Move, Color);

bool color_point_square(Renderer*, Point, Color);

bool render_piece_image(Renderer*, Piece, Rect);

bool render_surface_texture(Renderer*, Surface*, Rect);

#endif
