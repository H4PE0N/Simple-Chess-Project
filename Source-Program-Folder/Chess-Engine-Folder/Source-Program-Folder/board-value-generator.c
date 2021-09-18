
#include "../Header-Program-Folder/chess-engine-includer.h"

const int pieceMatrix[7][BOARD_HEIGHT][BOARD_WIDTH] =
{
	{ // Matrix for "EMPTY"
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	},
	{ // Matrix for "PAWN"
		{0, 0, 0, 0, 0, 0, 0, 0},
		{50, 50, 50, 50, 50, 50, 50, 50},
		{10, 10, 20, 30, 30, 20, 10, 10},
		{5, 5, 10, 27, 27, 10, 5, 5},
		{0, 0, 0, 25, 25, 0, 0, 0},
		{5, -5, -10, 0, 0, -10, -5, 5},
		{5, 10, 10, -25, -25, 10, 10, 5},
		{0, 0, 0, 0, 0, 0, 0, 0}
	},
	{ // Matrix for "BISHOP"
		{-20, -10, -10, -10, -10, -10, -10, -20},
		{-10, 0, 0, 0, 0, 0, 0, -10},
		{-10, 0, 5, 10, 10, 5, 0, -10},
		{-10, 5, 5, 10, 10, 5, 5, -10},
		{-10, 0, 10, 10, 10, 10, 0, -10},
		{-10, 10, 10, 10, 10, 10, 10, -10},
		{-10, 5, 0, 0, 0, 0, 5, -10},
		{-20, -10, -10, -10, -10, -10, -10, -20}
	},
	{ // Matrix for "KNIGHT"
		{-50, -40, -30, -30, -30, -30, -40, -50},
		{-40, -20, 0, 0, 0, 0, -20, -40},
		{-30, 0, 10, 15, 15, 10, 0, -30},
		{-30, 5, 15, 20, 20, 15, 5, -30},
		{-30, 0, 15, 20, 20, 15, 0, -30},
		{-30, 5, 10, 15, 15, 10, 5, -30},
		{-40, -20, 0, 5, 5, 0, -20, -40},
		{-50, -40, -30, -30, -30, -30, -40, -50}
	},
	{ // Matrix for "ROOK"
		{0, 0, 0, 0, 0, 0, 0, 0},
		{5, 10, 10, 10, 10, 10, 10, 5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{0, 0, 0, 5, 5, 0, 0, 0}
	},
	{ // Matrix for "QUEEN"
		{-20, -10, -10, -5, -5, -10, -10, -20},
		{-10, 0, 0, 0, 0, 0, 0, -10},
		{-10, 0, 5, 5, 5, 5, 0, -10},
		{-5, 0, 5, 5, 5, 5, 0, -5},
		{0, 0, 5, 5, 5, 5, 0, -5},
		{-10, 5, 5, 5, 5, 5, 0, -10},
		{-10, 0, 5, 0, 0, 0, 0, -10},
		{-20, -10, -10, -5, -5, -10, -10, -20}
	},
	{ // Matrix for "KING"
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	}
};

const int pieceValues[] = {0, 10, 30, 30, 50, 90, 900};

int team_state_value(Board board, Info info, Team team)
{
	int enemy = (team == WHITE) ? BLACK : WHITE;

	int enemyValue = board_state_value(board, info, enemy);
	int teamValue = board_state_value(board, info, team);

	return (teamValue - enemyValue);
}

int team_pieces_value(Board board, Team team)
{
	Point point; Piece piece;

	int value = 0;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		for(int width = 0; width < BOARD_WIDTH; width += 1)
		{
			point = (Point) {height, width};
			piece = board_point_piece(board, point);

			if(piece.team != team) continue;

			// Adding the value of the piece
			value += pieceValues[piece.type];

			// Adding extra value for the piece location
			int matrixValue = piece_matrix_value(piece, point);
			value += (matrixValue / 10);
		}
	}
	return value;
}

int piece_matrix_value(Piece piece, Point point)
{
	// This is a error catcher. If the point insn't inside the board, segfault is going to happen next
	if(!point_inside_board(point)) return MIN_VAL;

	if(piece.team == WHITE) return pieceMatrix[piece.type][point.height][point.width];

	if(piece.team == BLACK) return pieceMatrix[piece.type][BOARD_HEIGHT - point.height - 1][point.width];

	return 0;
}

int check_mate_value(Board board, Info info, Team team)
{
	int value = 0;

	Team enemy = (team == WHITE) ? BLACK : WHITE;

	// If the teamKing (own king) is in check mate
	if(check_mate_situation(board, info, team)) value += MIN_VAL;

	// If the enemyKing (opponent) is in check mate
	else if(check_mate_situation(board, info, enemy)) value += MAX_VAL;

	return value;
}

int game_draw_value(Board board, Info info, Team team)
{
	int value = 0;

	Team enemy = (team == WHITE) ? BLACK : WHITE;

	// If the own king cant move (oppenent did draw)
	if(check_draw_situation(board, info, team)) 		value += MAX_VAL;

	// If the opponent cant move (you did draw)
	else if(check_draw_situation(board, info, enemy)) 	value += MIN_VAL;

	return value;
}

int board_state_value(Board board, Info info, Team team)
{
	int value = 0;

	value += team_pieces_value(board, team);

	value += check_mate_value(board, info, team);

	value += game_draw_value(board, info, team);

	return value;
}
