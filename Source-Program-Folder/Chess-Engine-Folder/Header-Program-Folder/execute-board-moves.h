
#ifndef EXECUTE_BOARD_MOVES_H
#define EXECUTE_BOARD_MOVES_H

bool execute_piece_move(Board, Move, Info*);

bool execute_pawn_move(Board, Move);

bool execute_rook_move(Board, Move, Info*);

bool execute_team_castle(Board, Move, Info*);

bool extract_castle_points(Point*, Point*, Point, Point, Team);

// bool update_king_point(Info*, Team, Point);
//
// bool turn_off_rook_switch(Info*, Team);

bool execute_knight_move(Board, Move);

bool execute_bishop_move(Board, Move);

bool execute_queen_move(Board, Move);

bool execute_king_move(Board, Move, Info*);

bool pawn_becomes_queen(Point, Team);

#endif
