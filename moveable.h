
#ifndef MOVEABLE
#define MOVEABLE

bool straight_move_able(Board, Point, Color);

bool diagonal_move_able(Board, Point, Color);

bool board_piece_moveable(Board, Piece, Point);

bool path_empty_and_clear(Board, Point, Point);

bool board_pawn_moveable(Board, Point, Color);

bool board_rook_moveable(Board, Point, Color);

bool board_knight_moveable(Board, Point, Color);

bool board_bishop_moveable(Board, Point, Color);

bool board_queen_moveable(Board, Point, Color);

bool board_king_moveable(Board, Point, Color);

bool simulate_check_move(Board, Move, Color);

#endif