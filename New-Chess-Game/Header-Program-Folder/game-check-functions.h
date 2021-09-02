
#ifndef GAME_CHECK_FUNCTIONS_H
#define GAME_CHECK_FUNCTIONS_H

#include "global-include-header.h"
#include "pieces-moves-valid.h"

bool king_inside_check(Board, Point);

bool board_piece_check(Board, Point, Point);

/*bool king_check_situation(Board, Point, Color);

bool check_knight_check(Board, Point, Color);

bool check_diagonal_check(Board, Point, Color);

bool check_straight_check(Board, Point, Color);

bool check_pawn_check(Board, Point, Color);	

bool check_king_check(Board, Point, Color);*/

#endif