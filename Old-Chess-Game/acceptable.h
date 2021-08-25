
#ifndef ACCEPTABLE
#define ACCEPTABLE

bool pawn_move_acceptable(Board, Point, Point);

bool knight_move_acceptable(Board, Point, Point);

bool queen_move_acceptable(Board, Point, Point);

bool king_move_acceptable(Board, Point, Point);

bool rook_move_acceptable(Board, Move, Info*);

bool bishop_move_acceptable(Board, Point, Point);

bool diagonal_move_acceptable(Board, Point, Point);

bool straight_move_acceptable(Board, Point, Point);

#endif