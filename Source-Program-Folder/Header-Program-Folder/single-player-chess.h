
#ifndef SINGLE_PLAYER_CHESS_H
#define SINGLE_PLAYER_CHESS_H

#include "global-include-header.h"

bool single_player_chess(Team*, Board, Info*);

bool computer_move_handler(Board, Info*);

bool user_move_handler(Board, Info*);

#endif
