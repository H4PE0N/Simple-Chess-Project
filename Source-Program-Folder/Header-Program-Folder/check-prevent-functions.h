
#ifndef CHECK_PREVENT_FUNCTIONS_H
#define CHECK_PREVENT_FUNCTIONS_H

#include "global-include-header.h"
#include "chess-moves-acceptable.h"
#include "chess-game-functions.h"
#include "board-move-handler.h"
#include "game-check-functions.h"

bool team_prevent_check(Board, Info, Team);

bool piece_prevent_check(Board, Point, Info);

bool move_prevent_check(Board, Move, Info);

#endif
