
#ifndef CHECK_CHECK
#define CHECK_CHECK

bool check_draw_situation(Board, int, int);

bool check_mate_situation(Board, int, int);

bool king_check_situation(Board, int, int);

bool check_knight_check(Board, int, int);

bool check_diagonal_check(Board, int, int);

bool check_straight_check(Board, int, int);

bool check_pawn_check(Board, int, int);

bool king_is_moveable(Board, int, int);

#endif