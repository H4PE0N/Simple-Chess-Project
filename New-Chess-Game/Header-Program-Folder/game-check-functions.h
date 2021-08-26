
#ifndef GAME_CHECK_FUNCTIONS_H
#define GAME_CHECK_FUNCTIONS_H

#include "../Header-Program-Folder/global-include-header.h"

bool king_check_situation(Board, Point, Color);

bool check_knight_check(Board, Point, Color);

bool check_diagonal_check(Board, Point, Color);

bool check_straight_check(Board, Point, Color);

bool check_pawn_check(Board, Point, Color);	

bool check_king_check(Board, Point, Color);

#endif