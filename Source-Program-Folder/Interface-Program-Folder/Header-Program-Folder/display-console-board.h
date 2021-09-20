
#ifndef DISPLAY_CONSOLE_BOARD_H
#define DISPLAY_CONSOLE_BOARD_H

extern const char* blackSymbols[];
extern const char* whiteSymbols[];

#define DIS_LETS "  | A | B | C | D | E | F | G | H |"
#define DIS_ROW "--+---+---+---+---+---+---+---+---+--"

void display_chess_board(Board);

void display_chess_info(Info);

void display_game_round(Board, Info);

void display_chess_result(Board, Team);

void display_board_symbol(int, int, Piece);

#endif