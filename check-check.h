
#ifndef CHECK_CHECK
#define CHECK_CHECK

bool check_draw_situation(Board, Point, Color);

bool check_mate_situation(Board, Point, Color);

bool king_check_situation(Board, Point, Color);

bool check_knight_check(Board, Point, Color);

bool check_diagonal_check(Board, Point, Color);

bool check_straight_check(Board, Point, Color);

bool check_pawn_check(Board, Point, Color);

bool king_is_moveable(Board, Point, Color);

Board copy_chess_board(Board);

bool simulate_check_move(Board, Move, Color);

bool check_king_check(Board, Point, Color);

bool other_pieces_moveable(Board, Color);

#endif