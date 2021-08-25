
#ifndef EXECUTE_BOARD_MOVES_H
#define EXECUTE_BOARD_MOVES_H

#include "../Header-Program-Folder/global-include-header.h"

void execute_pawn_move(Board, Move, Info*);

void execute_rook_move(Board, Move, Info*);

void execute_rook_switch(Board, Move, Info*);

void update_king_point(Info*, Color, Point);

void turn_off_rook_switch(Info*, Color);

void execute_knight_move(Board, Move, Info*);

void execute_bishop_move(Board, Move, Info*);

void execute_queen_move(Board, Move, Info*);

void execute_king_move(Board, Move, Info*);

void make_pawn_queen(Board, Point);

#endif