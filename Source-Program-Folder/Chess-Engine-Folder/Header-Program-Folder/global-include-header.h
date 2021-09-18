
#ifndef GLOBAL_INCLUDE_HEADER_H
#define GLOBAL_INCLUDE_HEADER_H

#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <string.h>

#include <math.h>

#include <time.h>

#include <unistd.h>

#define CLEAR_LINE printf("\033[2K")

#define MOVE_UP_LINES(lines) printf("\033[%dA", lines)

#define MOVE_UP_BOARD MOVE_UP_LINES(19);

#define MOVE_UP_INFO MOVE_UP_LINES(3);

#define MOVE_UP_INPUT MOVE_UP_LINES(1);

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

// This is all header programs:

#include "struct-definitions-header.h"

#include "common-functions-program.h"

#include "board-move-handler.h"

#include "check-prevent-functions.h"

#include "chess-computer-program.h"

#include "chess-game-functions.h"

#include "chess-moves-acceptable.h"

#include "chess-pieces-moveable.h"

#include "error-message-functions.h"

#include "execute-board-moves.h"

#include "game-check-functions.h"

#include "piece-possible-moves.h"

#include "pieces-moves-valid.h"

#include "setup-game-variables.h"

#include "output-message-functions.h"

// This is the game program headers:

#endif
