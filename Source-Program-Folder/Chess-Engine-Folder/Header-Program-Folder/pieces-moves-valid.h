
#ifndef PIECES_MOVES_VALID_H
#define PIECES_MOVES_VALID_H

bool moving_pawn_valid(Point, Point, Team);

bool team_castle_valid(Point, Point, Team);

bool moving_rook_valid(Point, Point);

bool moving_knight_valid(Point, Point);

bool moving_bishop_valid(Point, Point);

bool moving_queen_valid(Point, Point);

bool moving_king_valid(Point, Point);

int pawn_height_offset(Point, Point, Team);

bool pawn_starting_bool(Point, Team);

bool rook_starting_bool(Point, Team);

bool king_starting_bool(Point, Team);

bool moving_piece_valid(Board, Point, Point);

bool moving_straight_valid(Point, Point);

bool moving_diagonal_valid(Point, Point);

#endif
