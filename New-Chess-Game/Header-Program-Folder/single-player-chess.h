
#ifndef SINGLE_PLAYER_CHESS_H
#define SINGLE_PLAYER_CHESS_H

#include "global-include-header.h"
#include "chess-game-functions.h"
#include "setup-game-variables.h"
#include "game-interface-program.h"
#include "board-move-handler.h"
#include "chess-computer-program.h"

bool single_player_chess(Color*, Board, Info*);

bool computer_move_handler(Color*, Board, Info*);

bool user_move_handler(Board, Info*);

#endif