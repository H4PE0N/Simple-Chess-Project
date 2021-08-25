
#ifndef CHESS_PIECES_MOVEABLE_H
#define CHESS_PIECES_MOVEABLE_H

#include "../Header-Program-Folder/global-include-header.h"
#include "../Header-Program-Folder/chess-moves-acceptable.h"

bool straight_move_able(Board, Point);

bool diagonal_move_able(Board, Point);

bool board_piece_moveable(Board, Piece, Point);

bool board_pawn_moveable(Board, Point);

bool board_rook_moveable(Board, Point);

bool board_knight_moveable(Board, Point);

bool board_bishop_moveable(Board, Point);

bool board_queen_moveable(Board, Point);

bool board_king_moveable(Board, Point);

#endif