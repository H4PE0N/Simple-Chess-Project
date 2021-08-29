
#ifndef COMMON_FUNCTIONS_PROGRAM_H
#define COMMON_FUNCTIONS_PROGRAM_H

#include "global-include-header.h"

bool number_inside_bounds(int, int, int);

bool point_inside_board(Point);

bool points_inside_board(Point, Point);

Piece board_point_piece(Board, Point);

void append_board_piece(Board, Point, Piece);

bool move_inside_board(Move);

void remove_board_piece(Board, Point);

void move_board_piece(Board, Point, Point);

int create_random_number(int, int);

void switch_chess_pieces(Board, Point, Point);

char* extract_file_name(char*[], int);

bool board_piece_equal(Piece, Piece);

bool board_piece_point(Point*, Board, Piece);

char convert_char_upper(char);

void convert_string_upper(char*, int);

Color board_point_color(Board, Point);

Board copy_chess_board(Board);

Point color_king_point(Info, Color);

bool clear_moving_path(Board, Point, Point);

bool board_points_enemy(Board, Point, Point);

bool board_points_team(Board, Point, Point);

bool board_point_empty(Board, Point);

Type board_point_type(Board, Point);

bool board_points_equal(Point, Point);

#endif