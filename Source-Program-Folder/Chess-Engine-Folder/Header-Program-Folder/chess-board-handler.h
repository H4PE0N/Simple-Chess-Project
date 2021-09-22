
#ifndef CHESS_BOARD_HANDLER_H
#define CHESS_BOARD_HANDLER_H

void allocate_board_piece(Board, Point, Piece);

Piece board_point_piece(Board, Point);

void copy_board_variable(Board, Board); // Remove this

Point passant_remove_point(Point, Team);

Point pawn_passant_point(Point, Team);

bool extract_castle_points(Point*, Point*, Point, Point, Team);

Type board_point_type(Board, Point);

Team board_point_team(Board, Point);

bool board_piece_points(Point*, Board, Piece);

Point board_piece_point(Board, Piece);

void update_castle_value(Castle*, Side, bool);

void update_castles_value(Castles*, Team, Side, bool);

bool board_castles_value(Castles, Team, Side);

bool board_castle_value(Castle, Side);

void update_castles_values(Castles*, Team, Castle);

void move_board_piece(Board, Point, Point);

void switch_chess_pieces(Board, Point, Point);

void remove_board_piece(Board, Point);

void free_chess_board(Board);

Board copy_chess_board(Board);

Team piece_team_enemy(Team);

#endif
