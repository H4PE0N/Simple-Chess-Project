
#ifndef STRUCT_DEFINITIONS_HEADER_H
#define STRUCT_DEFINITIONS_HEADER_H

typedef enum Type
{
	EMPTY = 0, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING,
} Type;

typedef enum Color 
{
	NONE = 0, WHITE, BLACK,
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
	bool left;
	bool right;
} RKSwitch;

typedef struct Info
{
	Color current;
	RKSwitch whiteRKS;
	RKSwitch blackRKS;
	Point wKing;
	Point bKing;
	int turns;
} Info;

#define B_HEIGHT 8
#define B_WIDTH 8

#endif