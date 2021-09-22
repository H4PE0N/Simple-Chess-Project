
#ifndef CHESS_ENGINE_LOGIC_H
#define CHESS_ENGINE_LOGIC_H

bool point_inside_board(Point);

bool number_inside_bounds(int, int, int);

bool move_inside_board(Move);

bool pawn_becomes_queen(Point, Team);

bool board_points_equal(Point, Point);

bool board_points_enemy(Board, Point, Point);

bool board_points_team(Board, Point, Point);

bool board_pieces_team(Team, Team);

bool board_pieces_enemy(Team, Team);

bool board_point_empty(Board, Point);

bool board_piece_empty(Piece);

bool piece_team_exists(Team);

bool piece_type_exists(Type);

bool points_inside_board(Point, Point);

bool board_pieces_equal(Piece, Piece);

bool points_not_enemy(Board, Point, Point);

#endif
