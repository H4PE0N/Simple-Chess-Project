
#ifndef CHESS_COMPUTER_PROGRAM_H
#define CHESS_COMPUTER_PROGRAM_H

#include "global-include-header.h"
#include "chess-game-functions.h"
#include "board-move-handler.h"
#include "chess-computer-program.h"
#include "game-interface-program.h"
#include "chess-simulations-program.h"

bool best_possible_move(Move*, Board, Info, int, Team);

int board_depth_value(Board, Info, int, int, int, Team, Team);


int team_state_value(Board, Info, Team);

int piece_matrix_value(Piece, Point);

int team_pieces_value(Board, Team);

int board_state_value(Board, Info, Team);

int check_mate_value(Board, Info, Team);


void sort_pruning_moves(Move*, int, Board, Info, Team);

int move_state_value(Board, Info, Move, Team);


bool piece_possible_moves(Move*, Board, Info, Point);

Move* all_possible_moves(Board, Info, Team);

int moves_array_amount(Move*);

void append_moves_array(Move*, Move*);

void switch_array_moves(Move*, int, int);

Move* create_moves_array(int);

bool board_piece_exposed(Board, Info, Point);

#endif
