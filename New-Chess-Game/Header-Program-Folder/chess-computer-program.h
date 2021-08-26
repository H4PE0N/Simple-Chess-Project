
#ifndef CHESS_COMPUTER_PROGRAM_H
#define CHESS_COMPUTER_PROGRAM_H

#include "global-include-header.h"
#include "chess-game-functions.h"
#include "board-move-handler.h"
#include "chess-computer-program.h"

bool computer_chess_move(Board, Info*, Color);

bool find_computer_move(Move*, Board, Info*, Color);

bool piece_possible_moves(Move*, Board, Info*, Point);

Move* all_possible_moves(Board, Info*, Color);

int moves_array_amount(Move*);

void append_moves_array(Move*, Move*);

Move* create_moves_array(int);

bool simulate_enemy_check(Board, Point, Point);

bool current_move_better(Board, BestMove, BestMove);

BestMove create_bestMove_data(Board, Move);

void update_best_move(BestMove*, Board, Move);

bool piece_can_get_taken(Board, Point, Point);

#endif