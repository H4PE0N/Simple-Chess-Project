
#ifndef PIECE_POSSIBLE_MOVES_H
#define PIECE_POSSIBLE_MOVES_H

#include "global-include-header.h"

bool piece_possible_moves(Move*, Board, Info, Point);

bool pawn_possible_moves(Move*, Board, Info, Point);

bool rook_possible_moves(Move*, Board, Info, Point);

bool bishop_possible_moves(Move*, Board, Info, Point);

bool knight_possible_moves(Move*, Board, Info, Point);

bool queen_possible_moves(Move*, Board, Info, Point);

bool king_possible_moves(Move*, Board, Info, Point);

#endif