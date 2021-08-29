
#ifndef ERROR_MESSAGE_FUNCTIONS_H
#define ERROR_MESSAGE_FUNCTIONS_H

#include "global-include-header.h"
#include "game-interface-program.h"

void create_board_error(char[]);

void setup_info_error(Board);

void file_pointer_error(char[]);

void file_values_error(char[]);

void setup_variables_error();

void chess_game_quitted();

void display_error_header(char[]);

void display_error_message(char[]);

#endif