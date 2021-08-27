
#ifndef CHESS_BOT_ALGORITHMS_H
#define CHESS_BOT_ALGORITHMS_H

#include "global-include-header.h"

bool default_bot_algorithm(Board, BestMove, BestMove);

bool defensive_bot_algorithm(Board, BestMove, BestMove);

bool offensive_bot_algorithm(Board, BestMove, BestMove);

bool smart_bot_algorithm1(Board, BestMove, BestMove);

#endif