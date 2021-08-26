
#ifndef CHESS_COMPUTER_PROGRAM_H
#define CHESS_COMPUTER_PROGRAM_H

#include "global-include-header.h"
#include "chess-game-functions.h"
#include "board-move-handler.h"
#include "chess-computer-program.h"

bool computer_chess_move(Board, Info*, Color);

bool get_computer_move(Move*, Board, Info*, Color);

bool computer_suicide_move(Move*, Board, Info*, Color);

bool computer_offence_move(Move*, Board, Info*, Color);

bool computer_defence_move(Move*, Board, Info*, Color);

bool computer_regular_move(Move*, Board, Info*, Color);

#endif