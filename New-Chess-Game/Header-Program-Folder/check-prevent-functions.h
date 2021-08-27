
#ifndef CHECK_PREVENT_FUNCTIONS_H
#define CHECK_PREVENT_FUNCTIONS_H

#include "../Header-Program-Folder/global-include-header.h"
#include "../Header-Program-Folder/chess-moves-acceptable.h"
#include "../Header-Program-Folder/chess-game-functions.h"
#include "../Header-Program-Folder/board-move-handler.h"
#include "../Header-Program-Folder/game-check-functions.h"

bool team_prevent_check(Board, Info, Color);

bool piece_prevent_check(Board, Point, Info);

bool move_prevent_check(Board, Move, Info);

#endif