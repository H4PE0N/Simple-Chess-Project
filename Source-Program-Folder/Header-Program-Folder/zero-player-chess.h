
#ifndef ZERO_PLAYER_CHESS_H
#define ZERO_PLAYER_CHESS_H

#include "global-include-header.h"
#include "chess-game-functions.h"
#include "setup-game-variables.h"
#include "game-interface-program.h"
#include "board-move-handler.h"
#include "chess-computer-program.h"

bool zero_player_chess(Color*, Board, Info*);

bool computer_move_handler(Board, Info*);

#endif