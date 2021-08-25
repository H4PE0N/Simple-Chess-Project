
#ifndef CHECK_MOVE
#define CHECK_MOVE

#include "header.h"

bool rook_king_switch(Board, Point, Point);

bool check_check_situation(Board, Move, Info*);

bool path_empty_and_clear(Board, Point, Point);

bool rook_switch_able(Board, Move, Info*);

bool straight_move_valid(Point, Point);

bool diagonal_move_valid(Point, Point);

bool clear_moving_path(Board, Point, Point);

bool board_points_equal(Point, Point);

bool board_piece_equal(Piece, Piece);

bool chess_enemy_point(Board, Point, Point);

bool chess_team_point(Board, Point, Point);

bool moving_pawn_valid(Board, Point, Point);

bool moving_rook_valid(Point, Point);

bool moving_knight_valid(Point, Point);

bool moving_bishop_valid(Point, Point);

bool moving_queen_valid(Point, Point);

bool moving_king_valid(Point, Point);

bool board_point_piece(Board, Point, Type);

#endif