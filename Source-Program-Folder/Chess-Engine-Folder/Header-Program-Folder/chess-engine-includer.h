
#ifndef CHESS_ENGINE_INCLUDER_H
#define CHESS_ENGINE_INCLUDER_H

#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <string.h>

#include <math.h>

#include <time.h>

#include <unistd.h>

#include "chess-engine-structures.h"

#include "common-functions-program.h"

#include "board-move-handler.h"

#include "check-prevent-functions.h"

#include "chess-computer-program.h"

#include "chess-game-functions.h"

#include "chess-moves-acceptable.h"

#include "chess-pieces-moveable.h"

#include "execute-board-moves.h"

#include "game-check-functions.h"

#include "piece-possible-moves.h"

#include "pieces-moves-valid.h"

#include "setup-game-variables.h"

#include "output-message-functions.h"

#include "chess-engine-defines.h"

#include "chess-engine-logic.h"

#define CLEAR_LINE printf("\033[2K")

#define MOVE_UP_LINES(lines) printf("\033[%dA", lines)

#define MOVE_UP_BOARD MOVE_UP_LINES(19);

#define MOVE_UP_INFO MOVE_UP_LINES(3);

#define MOVE_UP_INPUT MOVE_UP_LINES(1);

#endif
