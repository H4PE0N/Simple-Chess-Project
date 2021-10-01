
#ifndef GAME_INTERFACE_FUNCTIONS_H
#define GAME_INTERFACE_FUNCTIONS_H

bool display_console_board(Board, Info);

bool render_screen_board(Renderer*, Board, Info);

bool render_color_board(Renderer*, Board, Color);

bool render_movable_board(Renderer*, Board, Info, Point);

#endif