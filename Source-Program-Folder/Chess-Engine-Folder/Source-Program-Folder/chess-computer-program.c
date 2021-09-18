
#include "../Header-Program-Folder/engine-file-includer.h"

const int pieceMatrix[7][8][8] =
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

bool best_possible_move(Move* move, Board board, Info info, int depth, Team team)
{
	if(!piece_team_exists(team)) return false;

	if(depth <= 0) return false;

	time_t startTime = time(NULL);

	Move* moves = all_possible_moves(board, info, team);
	int amount = moves_array_amount(moves);

	if(amount <= 0)
	{
		can_not_find_move(board, info, team);

		free(moves);

		return false;
	}

	Move bestMove = moves[0], currMove;
	int bestValue = MIN_VAL, currValue;

	Info dummyInfo; Board boardCopy; Team nextTeam;

	for(int index = 0; index < amount; index += 1)
	{
		dummyInfo = info; dummyInfo.currTeam = team;

		currMove = moves[index];

		boardCopy = copy_chess_board(board);

		if(!move_chess_piece(boardCopy, currMove, &dummyInfo))
		{
			// For some reson, the computer cant move!

			free_chess_board(boardCopy);

			continue;
		}

		nextTeam = (team == WHITE) ? BLACK : WHITE;
		currValue = board_depth_value(boardCopy, dummyInfo, (depth - 1), MIN_VAL, MAX_VAL, team, nextTeam);

		free_chess_board(boardCopy);

		if(currValue > bestValue) { bestMove = currMove; bestValue = currValue; }
	}

	free(moves);

	time_t stopTime = time(NULL);
	time_t time = difftime(stopTime, startTime);

	display_found_move(bestMove, bestValue, time);

	*move = bestMove; return true;
}

int board_depth_value(Board board, Info info, int depth, int alpha, int beta, Team team, Team currTeam)
{
	// Base-case, Should return the value of the board
	if(depth <= 0)
	{
		return team_state_value(board, info, team);
	}

	Info dummyInfo = info; dummyInfo.currTeam = currTeam;

	Move* moves = all_possible_moves(board, dummyInfo, currTeam);
	int amount = moves_array_amount(moves);

	// If the computer cant move, it will return the worst score
	if(amount <= 0)
	{
		free(moves);

		return team_state_value(board, info, team);
	}

	int bestValue = (currTeam == team) ? MIN_VAL : MAX_VAL;

	// This is very slow, and makes the program run MUCH SLOWER (3s vs 73s)
	//sort_pruning_moves(moves, amount, board, info, currTeam);

	Move currMove; int currValue; Board boardCopy; Team nextTeam;

	for(int index = 0; index < amount; index += 1)
	{
		currMove = moves[index];

		dummyInfo = info; dummyInfo.currTeam = currTeam;

		boardCopy = copy_chess_board(board);

		if(!move_chess_piece(boardCopy, currMove, &dummyInfo))
		{
			free_chess_board(boardCopy);

			continue;
		}

		nextTeam = (currTeam == WHITE) ? BLACK : WHITE;
		currValue = board_depth_value(boardCopy, dummyInfo, (depth - 1), alpha, beta, team, nextTeam);

		free_chess_board(boardCopy);

		if(currTeam == team && currValue > bestValue) 	bestValue = currValue;
		if(currTeam != team && currValue < bestValue) 	bestValue = currValue;

		if(currTeam == team && currValue > alpha) 		alpha = currValue;
		if(currTeam != team && currValue < beta) 		beta = currValue;

		if(beta <= alpha) break;
	}

	free(moves);

	return bestValue;
}

int team_state_value(Board board, Info info, Team team)
{
	int enemy = (team == WHITE) ? BLACK : WHITE;

	int enemyValue = board_state_value(board, info, enemy);
	int teamValue = board_state_value(board, info, team);

	return (teamValue - enemyValue);
}

const TypeValue typeValues[] = { {EMPTY, 0}, {PAWN, 10}, {KNIGHT, 30},
	{BISHOP, 30}, {ROOK, 50}, {QUEEN, 90}, {KING, 900} };

int team_pieces_value(Board board, Team team)
{
	Point point; Piece piece;

	int value = 0;

	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			point = (Point) {height, width};
			piece = board_point_piece(board, point);

			if(piece.team != team) continue;

			// Adding the value of the piece
			value += typeValues[piece.type].value;

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

	if(piece.team == BLACK) return pieceMatrix[piece.type][B_HEIGHT - point.height - 1][point.width];

	return 0;
}

int check_mate_value(Board board, Info info, Team team)
{
	int value = 0;

	Team enemy = (team == WHITE) ? BLACK : WHITE;

	Point enemyKing = team_king_point(info, enemy);
	Point teamKing = team_king_point(info, team);

	// If the teamKing (own king) is in check mate
	if(check_mate_situation(board, info, teamKing)) value += MIN_VAL;

	// If the enemyKing (opponent) is in check mate
	else if(check_mate_situation(board, info, enemyKing)) value += MAX_VAL;

	return value;
}

int game_draw_value(Board board, Info info, Team team)
{
	int value = 0;

	Team enemy = (team == WHITE) ? BLACK : WHITE;

	Point enemyKing = team_king_point(info, enemy);
	Point teamKing = team_king_point(info, team);

	// If the own king cant move (oppenent did draw)
	if(check_draw_situation(board, info, teamKing)) 		value += MAX_VAL;

	// If the opponent cant move (you did draw)
	else if(check_draw_situation(board, info, enemyKing)) 	value += MIN_VAL;

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

void switch_array_moves(Move* moves, int first, int second)
{
	Move firstMove = moves[first];
	Move secondMove = moves[second];

	moves[first] = secondMove;
	moves[second] = firstMove;
}

/*
This function goes through all pieces in the inputted team.
You may can store every piece position in the info struct
and then go through that array, but I dont know.
*/
Move* all_possible_moves(Board board, Info info, Team team)
{
	Move* moves = create_moves_array(1024);
	Move* adding = NULL;

	Point point; Team currTeam;

	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			point = (Point) {height, width};
			currTeam = board_point_team(board, point);

			if(currTeam != team) continue;

			// The queen can do the most moves, and she can do 32 moves
			adding = create_moves_array(32);

			if(!piece_possible_moves(adding, board, info, point))
			{
				free(adding);

				continue;
			}

			append_moves_array(moves, adding);

			free(adding);
		}
	}
	return moves;
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