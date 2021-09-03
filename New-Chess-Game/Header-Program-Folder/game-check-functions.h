
#ifndef GAME_CHECK_FUNCTIONS_H
#define GAME_CHECK_FUNCTIONS_H

#include "global-include-header.h"
#include "pieces-moves-valid.h"

bool king_inside_check(Board, Point);

bool board_point_checking(Board, Point, Point);

#endif