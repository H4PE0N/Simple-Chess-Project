
#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef enum Type
{
	EMPTY = 0, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING,
} Type;

typedef enum Color 
{
	NONE = 0, BLACK, WHITE,
} Color;

typedef struct Piece
{
	Type type;
	Color color;
} Piece;

typedef struct Point
{
	int height, width;
} Point;

typedef Piece** Board;

#include "program.h"
#include "move.h"

#endif