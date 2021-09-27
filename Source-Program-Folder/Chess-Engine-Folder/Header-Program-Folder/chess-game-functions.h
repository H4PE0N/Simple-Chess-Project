
#ifndef CHESS_GAME_FUNCTIONS_H
#define CHESS_GAME_FUNCTIONS_H

bool team_pieces_movable(Board, Info, Team);

bool check_mate_situation(Board, Info, Team);

bool check_draw_situation(Board, Info, Team);

bool game_still_running(Team*, Board, Info);

bool team_enough_materials(Board, Team);

bool little_material_draw(Board);

bool move_chess_piece(Board, Move, Info*);

bool king_inside_check(Board, Point);

bool board_point_checking(Board, Point, Point);

#endif
