
#ifndef CHESS_SIMULATIONS_PROGRAM_H
#define CHESS_SIMULATIONS_PROGRAM_H

#include "global-include-header.h"
#include "chess-moves-acceptable.h"
#include "execute-board-moves.h"

bool move_prevent_check(Board, Move, Info);

bool check_check_situation(Board, Move, Info);

bool simulate_check_move(Board, Point, Point);

bool check_after_kingSwitch(Board, Move, Info);

bool simulate_enemy_check(Board, Move, Info);

bool simulate_check_mate(Board, Move, Info);

#endif