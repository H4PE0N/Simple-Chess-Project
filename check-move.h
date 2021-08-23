
#ifndef CHECK_MOVE
#define CHECK_MOVE

#include "header.h"

bool rook_king_switch(Board, Point, Point);

bool clear_diagonal_path(Board, Point, Point);

bool clear_straight_path(Board, Point, Point);

bool clear_moving_path(Board, Point, Point);

bool board_points_equal(Point, Point);

bool board_piece_equal(Piece, Piece);

bool chess_enemy_point(Board, Point, Point);

bool chess_team_point(Board, Point, Point);

bool moving_pawn_valid(Board, Point, Point);

bool moving_rook_valid(Board, Point, Point);

bool moving_knight_valid(Board, Point, Point);

bool moving_bishop_valid(Board, Point, Point);

bool moving_queen_valid(Board, Point, Point);

bool moving_king_valid(Board, Point, Point);

bool board_point_piece(Board, Point, Type);

#endif