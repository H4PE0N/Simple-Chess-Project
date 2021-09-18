
#ifndef CHECK_PREVENT_FUNCTIONS_H
#define CHECK_PREVENT_FUNCTIONS_H

bool team_prevent_check(Board, Info, Team);

bool piece_prevent_check(Board, Point, Info);

bool pawn_prevent_check(Board, Info, Point);

bool rook_prevent_check(Board, Info, Point);

bool knight_prevent_check(Board, Info, Point);

bool bishop_prevent_check(Board, Info, Point);

bool queen_prevent_check(Board, Info, Point);

bool king_prevent_check(Board, Info, Point);

bool diagonal_prevent_check(Board, Info, Point);

bool striaght_prevent_check(Board, Info, Point);

bool move_prevent_check(Board, Move, Info);

#endif
