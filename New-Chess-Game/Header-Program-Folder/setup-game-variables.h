
#ifndef SETUP_GAME_VARIABLES_H
#define SETUP_GAME_VARIABLES_H

#include "global-include-header.h"
#include "error-message-functions.h"

bool extract_file_line(Board, char[], int);

bool extract_file_value(Piece*, char[], int);

bool allocate_file_values(Board*, FILE*);

bool create_chess_board(Board*, char[]);

bool setup_game_info(Info*, Board);

RKSwitch extract_rks_values(Board, Color);

bool setup_game_variables(Board*, Info*);

#endif