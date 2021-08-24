
#ifndef MOVEABLE
#define MOVEABLE

bool straight_move_able(Board, Point);

bool diagonal_move_able(Board, Point);

bool board_piece_moveable(Board, Piece, Point);

bool board_pawn_moveable(Board, Point);

bool board_rook_moveable(Board, Point);

bool board_knight_moveable(Board, Point);

bool board_bishop_moveable(Board, Point);

bool board_queen_moveable(Board, Point);

bool board_king_moveable(Board, Point);

bool simulate_check_move(Board, Move, Color);

#endif