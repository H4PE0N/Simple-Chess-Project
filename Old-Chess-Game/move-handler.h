
#ifndef MOVE_HANDLER
#define MOVE_HANDLER

bool pawn_move_handler(Board, Move, Info*);

bool rook_move_handler(Board, Move, Info*);

bool knight_move_handler(Board, Move, Info*);

bool bishop_move_handler(Board, Move, Info*);

bool queen_move_handler(Board, Move, Info*);

bool king_move_handler(Board, Move, Info*);

#endif