
#include "../Header-Program-Folder/common-functions-program.h"

bool number_inside_bounds(int number, int minimum, int maximum)
{
	return (number <= maximum) && (number >= minimum);
}

bool point_inside_board(Point point)
{
	if(!number_inside_bounds(point.height, 0, 7)) return false;

	if(!number_inside_bounds(point.width, 0, 7)) return false;

	return true;
}

bool points_inside_board(Point first, Point second)
{
	if(!point_inside_board(first)) return false;

	if(!point_inside_board(second)) return false;

	return true;
}

int create_random_number(int minimum, int maximum)
{
	return (rand() % (maximum - minimum + 1) + minimum);
}

Piece board_point_piece(Board board, Point point)
{
	return board[point.height][point.width];
}

void append_board_piece(Board board, Point point, Piece piece)
{
	board[point.height][point.width] = piece;
}

void remove_board_piece(Board board, Point point)
{
	board[point.height][point.width] = (Piece) {EMPTY, NONE}; 
}

void move_board_piece(Board board, Point start, Point stop)
{
	remove_board_piece(board, stop);
	switch_chess_pieces(board, start, stop);
}

void switch_chess_pieces(Board board, Point first, Point second)
{
	Piece firPiece = board_point_piece(board, first);
	Piece secPiece = board_point_piece(board, second);

	append_board_piece(board, first, secPiece);
	append_board_piece(board, second, firPiece);
}

bool board_piece_equal(Piece first, Piece second)
{
	return (first.type == second.type && first.color == second.color);
}

bool board_piece_point(Point* point, Board board, Piece piece)
{
	Piece current;
	for(int height = 0; height < 8; height = height + 1)
	{
		for(int width = 0; width < 8; width = width + 1)
		{
			current = board_point_piece(board, (Point) {height, width});

			if(board_piece_equal(piece, current))
			{ *point = (Point) {height, width}; return true; }
		}
	}
	return false;
}

Color board_point_color(Board board, Point point)
{
	Piece piece = board_point_piece(board, point);
	return piece.color;
}

Type board_point_type(Board board, Point point)
{
	Piece piece = board_point_piece(board, point);
	return piece.type;
}

Board copy_chess_board(Board board)
{
	Board copy = malloc(sizeof(Piece*) * B_HEIGHT);
	for(int height = 0; height < B_HEIGHT; height = height + 1)
	{
		copy[height] = malloc(sizeof(Piece) * B_WIDTH);
		for(int width = 0; width < B_WIDTH; width = width + 1)
		{
			copy[height][width].type = board[height][width].type;
			copy[height][width].color = board[height][width].color;
		}
	}
	return copy;
}

Point color_king_point(Info info, Color color)
{
	if(color == NONE) return (Point) {-1, -1};
	return (color == WHITE) ? info.wKing : info.bKing;
}

bool board_points_team(Board board, Point start, Point stop)
{
	Color start_c = board_point_color(board, start);
	Color stop_c = board_point_color(board, stop);

	return (start_c == stop_c && start_c != NONE  && stop_c != NONE);
}

bool board_point_empty(Board board, Point point)
{
	Type type = board_point_type(board, point);
	Color color = board_point_color(board, point);
	return (type == EMPTY || color == NONE);
}

bool move_inside_board(Move move)
{
	if(!point_inside_board(move.start)) return false;
	if(!point_inside_board(move.stop)) return false;

	return true;
}

bool board_points_enemy(Board board, Point start, Point stop)
{
	Color start_c = board_point_color(board, start);
	Color stop_c = board_point_color(board, stop);

	return (start_c != stop_c && start_c != NONE && stop_c != NONE);
}

bool clear_moving_path(Board board, Point start, Point stop)
{
	int hOffset = stop.height - start.height;
	int wOffset = stop.width - start.width;

	int steps = (abs(hOffset) > abs(wOffset)) ? abs(hOffset) : abs(wOffset);

	int hAdder = (hOffset == 0) ? 0 : (hOffset / abs(hOffset));
	int wAdder = (wOffset == 0) ? 0 : (wOffset / abs(wOffset));

	for(int index = 1; index < steps; index = index + 1)
	{
		int hIndex = start.height + (index * hAdder);
		int wIndex = start.width + (index * wAdder);

		if(board[hIndex][wIndex].type != EMPTY) return false;
	}
	return true;
}

bool board_points_equal(Point first, Point second)
{
	return (first.height == second.height && first.width == second.width);
}

void convert_string_upper(char* string, int length)
{
	for(int index = 0; index < length; index += 1)
	{
		string[index] = convert_char_upper(string[index]);
	}
}

char convert_char_upper(char character)
{
	if(!number_inside_bounds(character, 97, 122)) return character;

	return (character - 32);
}
