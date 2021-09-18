
#ifndef CHESS_PIECES_MOVEABLE_H
#define CHESS_PIECES_MOVEABLE_H

bool board_piece_moveable(Board, Info, Point);

bool board_pawn_moveable(Board, Info, Point);

bool board_rook_moveable(Board, Info, Point);

bool board_knight_moveable(Board, Info, Point);

bool board_bishop_moveable(Board, Info, Point);

bool board_queen_moveable(Board, Info, Point);

bool board_king_moveable(Board, Info, Point);

bool board_diagonal_moveable(Board, Info, Point);

bool board_straight_moveable(Board, Info, Point);

#endif
