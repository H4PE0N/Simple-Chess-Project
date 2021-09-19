
#ifndef SETUP_ERROR_FUNCTIONS_H
#define SETUP_ERROR_FUNCTIONS_H

void create_board_error(char[]);

void setup_info_error(Board);

void file_pointer_error(char[]);

void file_values_error(char[]);

void setup_variables_error();

void can_not_find_move(Board, Info, Team);

void chess_game_quitted();

void display_error_header(char[]);

void display_error_message(char[]);

#endif
