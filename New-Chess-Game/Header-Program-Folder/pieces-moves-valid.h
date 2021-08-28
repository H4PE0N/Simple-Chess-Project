
#ifndef PIECES_MOVES_VALID_H
#define PIECES_MOVES_VALID_H

#include "global-include-header.h"

bool moving_pawn_valid(Board, Point, Point);

bool rook_king_switch(Board, Point, Point);

bool moving_rook_valid(Point, Point);

bool moving_knight_valid(Point, Point);

bool moving_bishop_valid(Point, Point);

bool moving_queen_valid(Point, Point);

bool moving_king_valid(Point, Point);

bool straight_move_valid(Point, Point);

bool diagonal_move_valid(Point, Point);

#endif