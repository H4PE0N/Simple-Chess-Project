
#ifndef CHESS_ENGINE_DEFINES_H
#define CHESS_ENGINE_DEFINES_H

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8

#define KING_WIDTH 4

#define EMPTY_PIECE (Piece) {EMPTY, NONE}

#define EMPTY_POINT (Point) {-1, -1}

#define EMPTY_MOVE (Move) {EMPTY_POINT, EMPTY_POINT}

#define EMPTY_CASTLE (Castle) {false, false}

#define EMPTY_CASTLES (Castles) {EMPTY_CASTLE, EMPTY_CASTLE}

#define MIN_VAL -100000
#define MAX_VAL +100000

#define STD_DEPTH 3

#endif
