
#ifndef INTERFACE_INPUT_PROGRAM_H
#define INTERFACE_INPUT_PROGRAM_H

#include "global-include-header.h"
#include "chess-computer-program.h"

#define CLEAR_LINE printf("\033[2K")

#define MOVE_UP_LINES(lines) printf("\033[%dA", lines)

#define MOVE_UP_BOARD MOVE_UP_LINES(19);

#define MOVE_UP_INFO MOVE_UP_LINES(3);

#define MOVE_UP_INPUT MOVE_UP_LINES(1);

void display_chess_board(Board);

bool board_point_string(char*, Point);

bool chess_move_string(char*, Move);

void display_chess_info(Info);

bool input_current_move(char*);

bool input_string_variable(char*);

bool parse_chess_move(Move*, Board, Info, char[]);

bool parse_chess_position(Point*, char[]);

void display_game_round(Board, Info);

int string_letter_index(char[], int, char);

void display_chess_result(Board, Team);

void display_board_symbol(int, int, Piece);

#endif
