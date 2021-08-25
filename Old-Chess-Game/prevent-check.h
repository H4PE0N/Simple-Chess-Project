
#ifndef PREVENT_CHECK
#define PREVENT_CHECK

bool team_prevent_check(Board, Info*, Color);

bool piece_prevent_check(Board, Point, Info*);

bool pawn_prevent_check(Board, Point, Info*);

bool rook_prevent_check(Board, Point, Info*);

bool knight_prevent_check(Board, Point, Info*);

bool bishop_prevent_check(Board, Point, Info*);

bool queen_prevent_check(Board, Point, Info*);

bool straight_prevent_check(Board, Point, Info*);

bool diagonal_prevent_check(Board, Point, Info*);

bool move_prevent_check(Board, Move, Info*);

#endif