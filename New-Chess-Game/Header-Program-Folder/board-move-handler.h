
#ifndef BOARD_MOVE_HANDLER_H
#define BOARD_MOVE_HANDLER_H

#include "../Header-Program-Folder/global-include-header.h"
#include "../Header-Program-Folder/chess-moves-acceptable.h"
#include "../Header-Program-Folder/execute-board-moves.h"

bool move_chess_piece(Board, Move, Info*);

bool pawn_move_handler(Board, Move, Info*);

bool rook_move_handler(Board, Move, Info*);

bool knight_move_handler(Board, Move, Info*);

bool bishop_move_handler(Board, Move, Info*);

bool queen_move_handler(Board, Move, Info*);

bool king_move_handler(Board, Move, Info*);

#endif