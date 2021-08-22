
#ifndef MOVE
#define MOVE

#include "header.h"

bool clear_diagonal_path(Board, Point, Point);
bool clear_straight_path(Board, Point, Point);
bool clear_moving_path(Board, Point, Point);

bool board_points_equal(Point, Point);

bool move_chess_piece(Board, Point, Point);

void switch_chess_pieces(Board, Point, Point);

bool moving_pawn_valid(Board, Point, Point);
bool execute_pawn_move(Board, Point, Point);

bool moving_rook_valid(Board, Point, Point);
bool execute_rook_move(Board, Point, Point);

bool moving_knight_valid(Board, Point, Point);
bool execute_knight_move(Board, Point, Point);

bool moving_bishop_valid(Board, Point, Point);
bool execute_bishop_move(Board, Point, Point);

bool moving_queen_valid(Board, Point, Point);
bool execute_queen_move(Board, Point, Point);

bool moving_king_valid(Board, Point, Point);
bool execute_king_move(Board, Point, Point);

#endif