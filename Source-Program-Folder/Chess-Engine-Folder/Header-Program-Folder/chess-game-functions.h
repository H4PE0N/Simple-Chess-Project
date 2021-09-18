
#ifndef CHESS_GAME_FUNCTIONS_H
#define CHESS_GAME_FUNCTIONS_H

bool other_pieces_moveable(Board, Info, Team);

bool check_mate_situation(Board, Info, Point);

bool check_draw_situation(Board, Info, Point);

bool game_still_running(Team*, Board, Info);

bool update_kings_point(Board, Info*);

#endif