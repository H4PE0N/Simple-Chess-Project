
#ifndef CHESS_PIECES_MOVABLE_H
#define CHESS_PIECES_MOVABLE_H

bool board_piece_movable(Board, Info, Point);

bool board_pawn_movable(Board, Info, Point);

bool board_rook_movable(Board, Info, Point);

bool board_knight_movable(Board, Info, Point);

bool board_bishop_movable(Board, Info, Point);

bool board_queen_movable(Board, Info, Point);

bool board_king_movable(Board, Info, Point);

bool board_diagonal_movable(Board, Info, Point);

bool board_straight_movable(Board, Info, Point);

#endif
