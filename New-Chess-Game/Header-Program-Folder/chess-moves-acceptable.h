
#ifndef CHESS_MOVE_ACCEPTABLE_H
#define CHESS_MOVE_ACCEPTABLE_H

#include "global-include-header.h"
#include "pieces-moves-valid.h"
#include "chess-game-functions.h"

bool piece_move_acceptable(Board, Move, Info);

bool pawn_move_acceptable(Board, Move, Info);

bool knight_move_acceptable(Board, Move, Info);

bool queen_move_acceptable(Board, Move, Info);

bool king_move_acceptable(Board, Move, Info);

bool bishop_move_acceptable(Board, Move, Info);

bool rook_move_acceptable(Board, Move, Info);


bool rook_switch_able(Board, Move, Info);

bool switch_bool_valid(Point, Info, Color);


bool check_check_situation(Board, Move, Info);

bool simulate_check_move(Board, Point, Point);

bool check_after_kingSwitch(Board, Move, Info);



#endif