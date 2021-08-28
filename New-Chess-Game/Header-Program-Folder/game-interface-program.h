
#ifndef INTERFACE_INPUT_PROGRAM_H
#define INTERFACE_INPUT_PROGRAM_H

#include "global-include-header.h"

void display_chess_board(Board);

void display_chess_info(Info);

bool input_current_move(char*);

bool input_string_variable(char*);

bool parse_chess_move(Move*, char[]);

bool parse_chess_position(Point*, char[]);

int string_letter_index(char[], int, char);

void display_chess_result(Board, Color);

void display_move_info(MoveInfo);

void display_board_move(Move);

void display_board_point(Point);

#endif