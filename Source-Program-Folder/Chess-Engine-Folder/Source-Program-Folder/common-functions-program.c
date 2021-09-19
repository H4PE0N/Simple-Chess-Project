
#include "../Header-Program-Folder/chess-engine-includer.h"

// bool number_inside_bounds(int number, int minimum, int maximum)
// {
// 	bool minimumValid = (number >= minimum);
// 	bool maximumValid = (number <= maximum);
//
// 	return (minimumValid && maximumValid);
// }

// bool point_inside_board(Point point)
// {
// 	bool heightValid = number_inside_bounds(point.height, 0, BOARD_HEIGHT-1);
// 	bool widthValid = number_inside_bounds(point.width, 0, BOARD_WIDTH-1);
//
// 	return (heightValid && widthValid);
// }

// bool piece_team_exists(Team team)
// {
// 	return (team == WHITE || team == BLACK);
// }

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

// bool points_inside_board(Point first, Point second)
// {
// 	bool firstValid = point_inside_board(first);
// 	bool secondValid = point_inside_board(second);
//
// 	return (firstValid && secondValid);
// }

// int create_random_number(int minimum, int maximum)
// {
// 	return (rand() % (maximum - minimum + 1) + minimum);
// }

// Piece board_point_piece(Board board, Point point)
// {
// 	return board[point.height][point.width];
// }

// void append_board_piece(Board board, Point point, Piece piece)
// {
// 	board[point.height][point.width] = piece;
// }

// void remove_board_piece(Board board, Point point)
// {
// 	board[point.height][point.width] = (Piece) {EMPTY, NONE};
// }
//
// void move_board_piece(Board board, Point start, Point stop)
// {
// 	remove_board_piece(board, stop);
// 	switch_chess_pieces(board, start, stop);
// }
//
// void switch_chess_pieces(Board board, Point first, Point second)
// {
// 	Piece firPiece = board_point_piece(board, first);
// 	Piece secPiece = board_point_piece(board, second);
//
// 	append_board_piece(board, first, secPiece);
// 	append_board_piece(board, second, firPiece);
// }

// bool board_piece_equal(Piece first, Piece second)
// {
// 	bool typeEqual = (first.type == second.type);
// 	bool teamEqual = (first.team == second.team);
//
// 	return (typeEqual && teamEqual);
// }

// bool board_piece_points(Point* points, Board board, Piece piece)
// {
// 	Piece currPiece; int index = 0;
//
// 	for(int height = 0; height < BOARD_HEIGHT; height = height + 1)
// 	{
// 		for(int width = 0; width < BOARD_WIDTH; width = width + 1)
// 		{
// 			currPiece = board_point_piece(board, (Point) {height, width});
//
// 			if(!board_piece_equal(piece, currPiece)) continue;
//
// 			points[index] = (Point) {height, width};
// 			index += 1;
// 		}
// 	}
// 	return (index > 0);
// }

Point* create_point_array(int length)
{
	Point* points = malloc(sizeof(Point) * (length + 1));

	for(int index = 0; index <= length; index += 1)
	{
		points[index] = (Point) {-1, -1};
	}
	return points;
}

// bool board_piece_point(Point* point, Board board, Piece piece)
// {
// 	Point* piecePoints = create_point_array(64);
//
// 	if(!board_piece_points(piecePoints, board, piece))
// 	{
// 		free(piecePoints);
//
// 		return false;
// 	}
//
// 	if(point_array_amount(piecePoints) != 1)
// 	{
// 		free(piecePoints);
//
// 		return false;
// 	}
//
// 	*point = piecePoints[0];
//
// 	free(piecePoints);
//
// 	return true;
// }

int point_array_amount(Point points[])
{
	int amount = 0;
	while(point_inside_board(points[amount]))
	{
		amount += 1;
	}
	return amount;
}

// Team board_point_team(Board board, Point point)
// {
// 	Piece piece = board_point_piece(board, point);
// 	return piece.team;
// }
//
// Type board_point_type(Board board, Point point)
// {
// 	Piece piece = board_point_piece(board, point);
// 	return piece.type;
// }

Point team_king_point(Info info, Team team)
{
	if(team == NONE) return (Point) {-1, -1};
	return (team == WHITE) ? info.whiteKing : info.blackKing;
}

// bool board_points_team(Board board, Point start, Point stop)
// {
// 	Team start_c = board_point_team(board, start);
// 	Team stop_c = board_point_team(board, stop);
//
// 	return (start_c == stop_c && start_c != NONE  && stop_c != NONE);
// }

// bool board_point_empty(Board board, Point point)
// {
// 	Type type = board_point_type(board, point);
// 	Team team = board_point_team(board, point);
//
// 	return (type == EMPTY || team == NONE);
// }

// bool board_point_clear(Board board, Point point)
// {
// 	Type type = board_point_type(board, point);
// 	Team team = board_point_team(board, point);
//
// 	return (type == EMPTY && team == NONE);
// }
//
// bool board_point_exists(Board board, Point point)
// {
// 	Type type = board_point_type(board, point);
// 	Team team = board_point_team(board, point);
//
// 	return (type != EMPTY && team != NONE);
// }

// bool move_inside_board(Move move)
// {
// 	bool startValid = point_inside_board(move.start);
// 	bool stopValid = point_inside_board(move.stop);
//
// 	return (startValid && stopValid);
// }

// bool board_points_enemy(Board board, Point start, Point stop)
// {
// 	Team start_c = board_point_team(board, start);
// 	Team stop_c = board_point_team(board, stop);
//
// 	return (start_c != stop_c && start_c != NONE && stop_c != NONE);
// }

// bool board_points_equal(Point first, Point second)
// {
// 	bool heightEqual = (first.height == second.height);
// 	bool widthEqual = (first.width == second.width);
//
// 	return (heightEqual && widthEqual);
// }

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

const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
const char numbers[] = {'8', '7', '6', '5', '4', '3', '2', '1'};

bool board_point_string(char* string, Point point)
{
	int height = point.height, width = point.width;

	if(!number_inside_bounds(height, 0, BOARD_HEIGHT-1)) return false;
	if(!number_inside_bounds(width, 0, BOARD_WIDTH-1)) return false;

	sprintf(string, "%c%c", letters[width], numbers[height]);

	return true;
}

bool chess_move_string(char* string, Move move)
{
	Point start = move.start, stop = move.stop;

	char startString[10], stopString[10];

	if(!board_point_string(startString, start)) return false;
	if(!board_point_string(stopString, stop)) return false;

	sprintf(string, "%s->%s", startString, stopString);

	return true;
}

void switch_array_moves(Move* moves, int first, int second)
{
	Move firstMove = moves[first];
	Move secondMove = moves[second];

	moves[first] = secondMove;
	moves[second] = firstMove;
}

void append_moves_array(Move* moves, Move adding[])
{
	int amount = moves_array_amount(moves);
	int addAmount = moves_array_amount(adding);

	for(int index = 0; index < addAmount; index += 1)
	{
		moves[amount + index] = adding[index];
	}
}

int moves_array_amount(Move moves[])
{
	int amount = 0;
	while(points_inside_board(moves[amount].start, moves[amount].stop))
	{
		amount += 1;
	}
	return amount;
}

void clear_moves_array(Move* moves)
{
	int amount = moves_array_amount(moves);

	for(int index = 0; index < amount; index += 1)
	{
		moves[index] = (Move) {(Point) {-1, -1}, (Point) {-1, -1}};
	}
}

Move* create_moves_array(int amount)
{
	Move* moves = malloc(sizeof(Move) * amount);
	Point start, stop;
	for(int index = 0; index < amount; index += 1)
	{
		start = (Point) {-1, -1}, stop = (Point) {-1, -1};
		moves[index] = (Move) {start, stop};
	}
	return moves;
}
