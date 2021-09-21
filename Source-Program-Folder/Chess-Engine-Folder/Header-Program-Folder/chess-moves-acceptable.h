
#ifndef CHESS_MOVE_ACCEPTABLE_H
#define CHESS_MOVE_ACCEPTABLE_H

bool pawn_move_acceptable(Board, Move, Info);

bool knight_move_acceptable(Board, Move, Info);

bool queen_move_acceptable(Board, Move, Info);

bool king_move_acceptable(Board, Move, Info);

bool bishop_move_acceptable(Board, Move, Info);

bool rook_move_acceptable(Board, Move, Info);


bool straight_move_acceptable(Board, Move, Info);

bool diagonal_move_acceptable(Board, Move, Info);


bool team_castle_acceptable(Board, Move, Info);

bool castle_bool_valid(Point, Info, Team);

Side rook_starting_side(int);


bool clear_moving_path(Board, Point, Point);

#endif
