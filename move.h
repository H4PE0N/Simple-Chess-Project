
#ifndef MOVE
#define MOVE

#include "header.h"

bool remove_board_piece(Board, int, int);

bool move_chess_piece(Board, Move, Info*);

void switch_chess_pieces(Board, Point, Point);

void switch_pawn_queen(Board, Point, Point);

#endif