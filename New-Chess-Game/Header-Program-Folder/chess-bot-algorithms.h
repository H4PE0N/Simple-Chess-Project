
#ifndef CHESS_BOT_ALGORITHMS_H
#define CHESS_BOT_ALGORITHMS_H

#include "global-include-header.h"

bool default_bot_algorithm(Board, MoveInfo, MoveInfo);

bool defensive_bot_algorithm(Board, MoveInfo, MoveInfo);

bool offensive_bot_algorithm(Board, MoveInfo, MoveInfo);

bool smart_bot_algorithm1(Board, MoveInfo, MoveInfo);

#endif