
#ifndef CHESS_GAME_FUNCTIONS_H
#define CHESS_GAME_FUNCTIONS_H

#include "../Header-Program-Folder/global-include-header.h"
#include "../Header-Program-Folder/check-prevent-functions.h"
#include "../Header-Program-Folder/chess-pieces-moveable.h"

bool king_check_situation(Board, Point);

bool other_pieces_moveable(Board, Color);

bool check_mate_situation(Board, Point, Info*);

bool check_draw_situation(Board, Point);

bool game_still_running(Color*, Board, Info*);

#endif