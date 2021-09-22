
#ifndef CHESS_COMPUTER_PROGRAM_H
#define CHESS_COMPUTER_PROGRAM_H

bool best_possible_move(Move*, Board, Info, int, Team);

int board_depth_value(Board, Info, int, int, int, Team, Team);

Move* all_possible_moves(Board, Info, Team);

#endif
