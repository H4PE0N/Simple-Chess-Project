
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
	Point whiteKing;
	Point blackKing;
	int turns;
	Move lastMove;
} Info;

typedef struct TypeValue
{
	Type type;
	int value;
} TypeValue;

typedef Piece** Board;

#endif
