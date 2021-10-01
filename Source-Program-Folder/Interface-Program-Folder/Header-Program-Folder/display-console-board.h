
#ifndef DISPLAY_CONSOLE_BOARD_H
#define DISPLAY_CONSOLE_BOARD_H

bool display_chess_board(Board);

bool display_game_info(Info);

bool display_board_symbol(Board, Point);

char extract_piece_symbol(Piece);

void display_board_letters(char[]);

#endif
