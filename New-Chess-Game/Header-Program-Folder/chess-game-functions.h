
#ifndef CHESS_GAME_FUNCTIONS_H
#define CHESS_GAME_FUNCTIONS_H

#include "../Header-Program-Folder/global-include-header.h"
#include "../Header-Program-Folder/check-prevent-functions.h"
#include "../Header-Program-Folder/chess-pieces-moveable.h"

bool other_pieces_moveable(Board, Info*, Color);

bool check_mate_situation(Board, Info*, Point);

bool check_draw_situation(Board, Info*, Point);

bool game_still_running(Color*, Board, Info*);

bool update_kings_point(Board, Info*);

#endif