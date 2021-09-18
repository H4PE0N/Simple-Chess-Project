
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

// typedef SDL_Window Window;

// typedef SDL_Renderer Render;

// typedef SDL_Surface	Surface;

// typedef SDL_Texture Texture;

// typedef SDL_Rect Rect;

// typedef SDL_Color Color;

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

#define B_HEIGHT 8
#define B_WIDTH 8

#define MIN_VAL -100000
#define MAX_VAL +100000

#define STD_DEPTH 3

#define SAVE_FILE	"../Source-Program-Folder/Data-Program-Folder/saved-chess-board.txt"
#define STD_FILE	"../Source-Program-Folder/Data-Program-Folder/default-chess-board.txt"
#define PIECE_FOLDER "../Source-Program-Folder/Piece-Image-Folder"

#define SCREEN_HEIGHT	800
#define SCREEN_WIDTH	800

#define SQUARE_HEIGHT SCREEN_HEIGHT / B_HEIGHT
#define SQUARE_WIDTH SCREEN_WIDTH / B_WIDTH

#endif
