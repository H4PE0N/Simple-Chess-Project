
#ifndef MOVE
#define MOVE

#include "header.h"

bool remove_board_piece(Board, int, int);

bool move_chess_piece(Board, Move, Info*);

bool switch_chess_pieces(Board, Point, Point);

void make_pawn_queen(Board, Point, Color);

bool move_board_piece(Board, Point, Point);

#endif