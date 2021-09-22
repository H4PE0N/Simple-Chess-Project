
#ifndef EXECUTE_BOARD_MOVES_H
#define EXECUTE_BOARD_MOVES_H

bool execute_piece_move(Board, Move, Info*);

bool execute_pawn_move(Board, Move, Info*);

bool execute_rook_move(Board, Move, Info*);

bool execute_team_castle(Board, Move, Info*);

bool execute_knight_move(Board, Move, Info*);

bool execute_bishop_move(Board, Move, Info*);

bool execute_queen_move(Board, Move, Info*);

bool execute_king_move(Board, Move, Info*);

#endif
