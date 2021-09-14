
#ifndef CHECK_PREVENT_FUNCTIONS_H
#define CHECK_PREVENT_FUNCTIONS_H

#include "global-include-header.h"

bool team_prevent_check(Board, Info, Team);

bool piece_prevent_check(Board, Point, Info);

bool move_prevent_check(Board, Move, Info);

#endif
