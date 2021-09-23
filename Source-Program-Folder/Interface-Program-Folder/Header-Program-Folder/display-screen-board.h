
#ifndef DISPLAY_SCREEN_BOARD_H
#define DISPLAY_SCREEN_BOARD_H

extern const Color gridWhite;
extern const Color gridBlack;

extern const Color startColor;
extern const Color stopColor;

extern const Color hintColor;
extern const Color quitColor;

bool render_screen_board(Renderer*, Board, Info);

bool render_board_grid(Renderer*);

bool render_board_color(Renderer*, Color);

bool render_quit_board(Renderer*, Board);

bool render_board_pieces(Renderer*, Board);

bool render_board_piece(Renderer*, Point, Piece);

bool render_piece_moves(Renderer*, Board, Info, Point);

bool render_board_move(Renderer*, Move, Color);

bool color_point_square(Renderer*, Point, Color);

bool render_piece_image(Renderer*, Piece, Rect);

bool render_surface_texture(Renderer*, Surface*, Rect);

#endif
