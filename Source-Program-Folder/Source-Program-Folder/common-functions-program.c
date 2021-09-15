
#include "../Header-Program-Folder/global-include-header.h"

bool number_inside_bounds(int number, int minimum, int maximum)
{
	bool minimumValid = (number >= minimum);
	bool maximumValid = (number <= maximum);

	return (minimumValid && maximumValid);
}

bool point_inside_board(Point point)
{
	bool heightValid = number_inside_bounds(point.height, 0, B_HEIGHT-1);
	bool widthValid = number_inside_bounds(point.width, 0, B_WIDTH-1);

	return (heightValid && widthValid);
}

bool chess_team_string(char* string, Team team)
{
	switch(team)
	{
		case (NONE): strcpy(string, "NONE"); return true;

		case(WHITE): strcpy(string, "WHITE"); return true;

		case(BLACK): strcpy(string, "BLACK"); return true;
	}
	return false;
}

bool points_inside_board(Point first, Point second)
{
	bool firstValid = point_inside_board(first);
	bool secondValid = point_inside_board(second);

	return (firstValid && secondValid);
}

void free_chess_board(Board board)
{
	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		free(board[height]);
	}
	free(board);
}

void extract_file_name(char* filename, char* arguments[], int amount)
{
	if(amount >= 2) strcpy(filename, arguments[1]);

	else strcpy(filename, STD_FILE);
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
	bool typeEqual = (first.type == second.type);
	bool teamEqual = (first.team == second.team);

	return (typeEqual && teamEqual);
}

bool board_piece_points(Point* points, Board board, Piece piece)
{
	Piece currPiece; int index = 0;
	
	for(int height = 0; height < B_HEIGHT; height = height + 1)
	{
		for(int width = 0; width < B_WIDTH; width = width + 1)
		{
			currPiece = board_point_piece(board, (Point) {height, width});

			if(!board_piece_equal(piece, currPiece)) continue;
			
			points[index] = (Point) {height, width};
			index += 1;
		}
	}
	return (index > 0);
}

Point* create_point_array(int length)
{
	Point* points = malloc(sizeof(Point) * (length + 1));

	for(int index = 0; index <= length; index += 1)
	{
		points[index] = (Point) {-1, -1};
	}
	return points;
}

bool board_piece_point(Point* point, Board board, Piece piece)
{
	Point* piecePoints = create_point_array(64);

	if(!board_piece_points(piecePoints, board, piece))
	{
		free(piecePoints);

		return false;
	}

	if(point_array_amount(piecePoints) != 1)
	{
		free(piecePoints);

		return false;
	}

	*point = piecePoints[0];

	free(piecePoints);

	return true;
}

int point_array_amount(Point points[])
{
	int amount = 0;
	while(point_inside_board(points[amount]))
	{
		amount += 1;
	}
	return amount;
}

Team board_point_team(Board board, Point point)
{
	Piece piece = board_point_piece(board, point);
	return piece.team;
}

Type board_point_type(Board board, Point point)
{
	Piece piece = board_point_piece(board, point);
	return piece.type;
}

Board copy_chess_board(Board board)
{
	Board boardCopy = malloc(sizeof(Piece*) * B_HEIGHT);
	for(int height = 0; height < B_HEIGHT; height = height + 1)
	{
		boardCopy[height] = malloc(sizeof(Piece) * B_WIDTH);
		for(int width = 0; width < B_WIDTH; width = width + 1)
		{
			boardCopy[height][width] = board[height][width];
		}
	}
	return boardCopy;
}

Point team_king_point(Info info, Team team)
{
	if(team == NONE) return (Point) {-1, -1};
	return (team == WHITE) ? info.wKing : info.bKing;
}

bool board_points_team(Board board, Point start, Point stop)
{
	Team start_c = board_point_team(board, start);
	Team stop_c = board_point_team(board, stop);

	return (start_c == stop_c && start_c != NONE  && stop_c != NONE);
}

bool board_point_empty(Board board, Point point)
{
	Type type = board_point_type(board, point);
	Team team = board_point_team(board, point);

	return (type == EMPTY || team == NONE);
}

bool board_point_clear(Board board, Point point)
{
	Type type = board_point_type(board, point);
	Team team = board_point_team(board, point);

	return (type == EMPTY && team == NONE);
}

bool board_point_exists(Board board, Point point)
{
	Type type = board_point_type(board, point);
	Team team = board_point_team(board, point);

	return (type != EMPTY && team != NONE);
}

bool move_inside_board(Move move)
{
	bool startValid = point_inside_board(move.start);
	bool stopValid = point_inside_board(move.stop);

	return (startValid && stopValid);
}

bool board_points_enemy(Board board, Point start, Point stop)
{
	Team start_c = board_point_team(board, start);
	Team stop_c = board_point_team(board, stop);

	return (start_c != stop_c && start_c != NONE && stop_c != NONE);
}

bool clear_moving_path(Board board, Point start, Point stop)
{
	int heightOffset = (stop.height - start.height);
	int widthOffset = (stop.width - start.width);

	// If the knight is moving, he dont need a clear moving path
	if(moving_knight_valid(start, stop)) return true;

	int steps = (abs(heightOffset) > abs(widthOffset)) ? abs(heightOffset) : abs(widthOffset);

	int heightAdder = (heightOffset == 0) ? 0 : (heightOffset / abs(heightOffset));
	int widthAdder = (widthOffset == 0) ? 0 : (widthOffset / abs(widthOffset));

	int height, width;

	Point point;

	for(int index = 1; index < steps; index = index + 1)
	{
		height = start.height + (index * heightAdder);
		width = start.width + (index * widthAdder);

		point = (Point) {height, width};

		if(!board_point_clear(board, point)) return false;
	}
	return true;
}

bool board_points_equal(Point first, Point second)
{
	bool heightEqual = (first.height == second.height);
	bool widthEqual = (first.width == second.width);

	return (heightEqual && widthEqual);
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
	// If the letter is not lowercase, it cant be converted
	if(!number_inside_bounds(character, 97, 122)) return character;

	// If the letter is lowercase, it will be converted.
	else return (character - 32);
}
