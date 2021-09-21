
#ifndef PIECE_EXECUTE_HANDLER_H
#define PIECE_EXECUTE_HANDLER_H

bool execute_piece_move(Board, Move, Info*);

bool pawn_execute_handler(Board, Move, Info*);

bool rook_execute_handler(Board, Move, Info*);

bool bishop_execute_handler(Board, Move, Info*);

bool knight_execute_handler(Board, Move, Info*);

bool queen_execute_handler(Board, Move, Info*);

bool king_execute_handler(Board, Move, Info*);

#endif
