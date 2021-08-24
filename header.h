
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

typedef struct Move
{
	Point start;
	Point stop;
} Move;

typedef struct RKSwitch
{
	bool right;
	bool left;
} RKSwitch;

typedef struct Info
{
	Color current;
	Move lastMove;
	RKSwitch whiteRKS;
	RKSwitch blackRKS;
	Point bKing;
	Point wKing;
	bool bCheck;
	bool wCheck;
	int turns;
} Info;

#include "program.h"
#include "moveable.h"
#include "prevent-check.h"
#include "check-move.h"
#include "check-check.h"
#include "move-piece.h"
#include "move-handler.h"
#include "move.h"

#endif