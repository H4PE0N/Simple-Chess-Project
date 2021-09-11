
#ifndef STRUCT_DEFINITIONS_HEADER_H
#define STRUCT_DEFINITIONS_HEADER_H

typedef enum Type
{
	EMPTY = 0, PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING,
} Type;

typedef enum Team
{
	NONE = 0, WHITE, BLACK,
} Team;

typedef struct Piece
{
	Type type;
	Team team;
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
	Team currTeam;
	RKSwitch whiteRKS;
	RKSwitch blackRKS;
	Point wKing;
	Point bKing;
	int turns;
} Info;

typedef struct TypeValue
{
	Type type;
	int value;
} TypeValue;

#define B_HEIGHT 8
#define B_WIDTH 8

#define MIN_VAL -100000
#define MAX_VAL +100000

#endif
