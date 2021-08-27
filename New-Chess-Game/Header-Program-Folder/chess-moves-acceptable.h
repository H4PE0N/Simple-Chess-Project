
#ifndef CHESS_MOVE_ACCEPTABLE_H
#define CHESS_MOVE_ACCEPTABLE_H

#include "../Header-Program-Folder/global-include-header.h"
#include "../Header-Program-Folder/pieces-moves-valid.h"
#include "../Header-Program-Folder/chess-game-functions.h"

bool pawn_move_acceptable(Board, Point, Point);

bool knight_move_acceptable(Board, Point, Point);

bool queen_move_acceptable(Board, Point, Point);

bool king_move_acceptable(Board, Point, Point);

bool rook_switch_able(Board, Move, Info);

bool rook_move_acceptable(Board, Move, Info);

bool check_check_situation(Board, Move, Info);

bool bishop_move_acceptable(Board, Point, Point);

bool diagonal_move_acceptable(Board, Point, Point);

bool straight_move_acceptable(Board, Point, Point);

bool simulate_check_move(Board, Point, Point);

bool piece_move_acceptable(Board, Move, Info);

#endif