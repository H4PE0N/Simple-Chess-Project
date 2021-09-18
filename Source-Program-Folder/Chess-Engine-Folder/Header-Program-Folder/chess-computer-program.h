
#ifndef CHESS_COMPUTER_PROGRAM_H
#define CHESS_COMPUTER_PROGRAM_H

bool best_possible_move(Move*, Board, Info, int, Team);

int board_depth_value(Board, Info, int, int, int, Team, Team);


Move* all_possible_moves(Board, Info, Team);

int moves_array_amount(Move[]);

void append_moves_array(Move*, Move[]);

void clear_moves_array(Move*);

void switch_array_moves(Move*, int, int);

Move* create_moves_array(int);

#endif
