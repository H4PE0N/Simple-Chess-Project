
#ifndef STRUCT_DEFINITIONS_HEADER_H
#define STRUCT_DEFINITIONS_HEADER_H

typedef enum Type
{
	EMPTY, PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING
} Type;

typedef enum Team
{
	NONE, WHITE, BLACK
} Team;

typedef enum Side
{
	STILL, LEFT, RIGHT
} Side;

typedef struct Piece
{
	Type type;
	Team team;
} Piece;

typedef struct Point
{
	int height;
	int width;
} Point;

typedef struct Move
{
	Point start;
	Point stop;
} Move;

typedef struct Castle
{
	// queenSide kingSide
	bool queen;
	bool king;
} Castle;

typedef struct Castles
{
	Castle white;
	Castle black;
} Castles;

typedef struct Info
{
	// Team current;
  // Castles castles;
	// Point passant;
	// int counter;
  // int turns;
	// Move lastMove;
	Team currTeam;
	Castle whiteRKS;
	Castle blackRKS;
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
