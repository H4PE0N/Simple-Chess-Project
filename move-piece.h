
#ifndef MOVE_PIECE
#define MOVE_PIECE

#include "header.h"

bool execute_pawn_move(Board, Move, Info*);

bool execute_rook_move(Board, Move, Info*);

bool execute_knight_move(Board, Move, Info*);

bool execute_bishop_move(Board, Move, Info*);

bool execute_queen_move(Board, Move, Info*);

bool execute_king_move(Board, Move, Info*);

#endif