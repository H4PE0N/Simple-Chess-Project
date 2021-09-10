
#ifndef CHESS_COMPUTER_PROGRAM_H
#define CHESS_COMPUTER_PROGRAM_H

#include "global-include-header.h"
#include "chess-game-functions.h"
#include "board-move-handler.h"
#include "chess-computer-program.h"
#include "chess-bot-algorithms.h"
#include "game-interface-program.h"
#include "chess-simulations-program.h"

bool best_possible_move(Move*, Board, Info, int, Color);

int board_depth_value(Board, Info, int, int, int, Color, Color);

int color_state_value(Board, Info, Color);

int team_pieces_value(Board, Color);

int board_state_value(Board, Info, Color);


void sort_pruning_moves(Move*, int, Board, Info);

int move_state_value(Board, Info, Move, Color);


bool find_computer_move(Move*, Board, Info, Color);

bool piece_possible_moves(Move*, Board, Info, Point);

Move* all_possible_moves(Board, Info, Color);

int moves_array_amount(Move*);

void append_moves_array(Move*, Move*);

void shuffle_moves_array(Move*, int);

void switch_array_moves(Move*, int, int);

Move* create_moves_array(int);

MoveInfo create_move_info(Board, Move, Info);

void update_best_move(MoveInfo*, Board, Move, Info);

bool piece_move_exposed(Board, Move, Info);

bool board_piece_exposed(Board, Info, Point);

#endif