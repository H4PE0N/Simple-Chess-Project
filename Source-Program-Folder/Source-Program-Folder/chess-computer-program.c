 
#include "../Header-Program-Folder/chess-computer-program.h"

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

int checked = 0; // Remove this: Just for debug
int total = 0;   // Remove this: Just for debug
int pruned = 0;	 // Remove this: Just for debug
int ones = 0; 	 // Remove this: Just for debug

bool best_possible_move(Move* move, Board board, Info info, int depth, Team team)
{
	// If the depth is lower or equal to 0, no move can be caluclated
	if(depth <= 0) return false;

	time_t startTime = time(NULL);  // Remove this: Just for debug
	checked = 0;					// Remove this: Just for debug
	total = 0;						// Remove this: Just for debug
	pruned = 0;						// Remove this: Just for debug	
	ones = 0;						// Remove this: Just for debug

	Move* moves = all_possible_moves(board, info, team);
	int amount = moves_array_amount(moves);

	// No moves can be calculated, the computer cant move!
	if(amount <= 0)
	{
		// Make this into an error function
		CLEAR_LINE; printf("The computer cant find a move!\n");

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

			// Make this into an error function
			CLEAR_LINE; printf("Cant move Main move!\n"); 

			continue;
		}

		nextTeam = (team == WHITE) ? BLACK : WHITE;
		currValue = board_depth_value(boardCopy, dummyInfo, (depth - 1), MIN_VAL, MAX_VAL, team, nextTeam);

		free_chess_board(boardCopy);

		// If the value is greater, the move is better. BestMove will then be updated
		if(currValue > bestValue) { bestMove = currMove; bestValue = currValue; }
	}

	free(moves);

	time_t stopTime = time(NULL); 																// Remove this: Just for debug

	int time = difftime(stopTime, startTime); 													// Remove this: Just for debug

	char moveString[20] = "\0"; 																// Remove this: Just for debug
	chess_move_string(moveString, bestMove); 													// Remove this: Just for debug
	CLEAR_LINE; printf("Best move: [%s] Value = %d Time = %d\n", moveString, bestValue, time); 	// Remove this: Just for debug

	CLEAR_LINE; printf("Checked %d moves out of %d! Pruned %d Ones %d\n", checked, total, pruned, ones); 		// Remove this: Just for debug

	// The move was found, and we return a positive (true) result
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

	total += amount; 			   // Remove this: Just for debug
	if(depth == 1) ones += amount; // Remove this: Just for debug

	int bestValue = (currTeam == team) ? MIN_VAL : MAX_VAL;

	// If the computer cant move, it will return the worst score
	if(amount <= 0)
	{
		// Make this into an error function
		CLEAR_LINE; printf("Depth valuing cant find moves!\n");

		free(moves);

		return bestValue;
	}

	sort_pruning_moves(moves, amount, board, info, currTeam);

	Move currMove; int currValue; Board boardCopy; Team nextTeam;

	for(int index = 0; index < amount; index += 1)
	{
		checked++; // Remove this: Just for debug

		currMove = moves[index];

		dummyInfo = info; dummyInfo.currTeam = currTeam;

		boardCopy = copy_chess_board(board);

		if(!move_chess_piece(boardCopy, currMove, &dummyInfo))
		{
			free_chess_board(boardCopy);

			// Make this into an error function
			CLEAR_LINE; printf("Cant move Depth move!\n"); 

			continue;
		}

		nextTeam = (currTeam == WHITE) ? BLACK : WHITE;
		currValue = board_depth_value(boardCopy, dummyInfo, (depth - 1), alpha, beta, team, nextTeam);

		free_chess_board(boardCopy);

		if(currTeam == team && currValue > bestValue) 	bestValue = currValue;
		if(currTeam != team && currValue < bestValue) 	bestValue = currValue;

		if(currTeam == team && currValue > alpha) 		alpha = currValue;
		if(currTeam != team && currValue < beta) 		beta = currValue;

		if(beta <= alpha)
		{
			pruned++; // Remove this: Just for debug

			break;
		}
	}

	free(moves);

	return bestValue;
}

void sort_pruning_moves(Move* moves, int amount, Board board, Info info, Team team)
{
	Move firstMove, secondMove; int firstValue, secondValue;

	for(int iteration = 0; iteration < amount; iteration += 1)
	{
		for(int index = 0; index < (amount - iteration - 1); index += 1)
		{
			firstMove = moves[index];
			secondMove = moves[index + 1];

			firstValue = move_state_value(board, info, firstMove, team);
			secondValue = move_state_value(board, info, secondMove, team);

			if(firstValue > secondValue)
			{
				switch_array_moves(moves, index, (index + 1) );
			}
		}
	}
}

int move_state_value(Board board, Info info, Move move, Team team)
{
	Team currTeam = board_point_team(board, move.start);

	Info dummyInfo = info; dummyInfo.currTeam = currTeam;

	Board copy = copy_chess_board(board);

	if(!move_chess_piece(copy, move, &dummyInfo))
	{
		free_chess_board(copy);

		return (team == currTeam) ? MIN_VAL : MAX_VAL;
	}

	free_chess_board(copy);

	return board_state_value(board, dummyInfo, team);
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

	if(check_mate_situation(board, info, teamKing)) 		value += MAX_VAL;
	else if(check_mate_situation(board, info, enemyKing)) 	value += MIN_VAL;

	return value;
}

int board_state_value(Board board, Info info, Team team)
{
	int value = 0;

	value += team_pieces_value(board, team);

	value += check_mate_value(board, info, team);

	return value;
}

void switch_array_moves(Move* moves, int first, int second)
{
	Move firstMove = moves[first];
	Move secondMove = moves[second];

	moves[first] = secondMove;
	moves[second] = firstMove;
}

bool board_piece_exposed(Board board, Info info, Point point)
{
	Point start; Move move;
	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			start = (Point) {height, width};
			move = (Move) {start, point};

			if(!board_points_enemy(board, point, start)) continue;
			if(piece_move_acceptable(board, move, info)) return true;
		}
	}
	return false;
}

Move* all_possible_moves(Board board, Info info, Team team)
{
	Move* moves = create_moves_array(1024);
	Move* adding;

	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			Point point = {height, width};
			Team currTeam = board_point_team(board, point);
			if(currTeam != team) continue;

			adding = create_moves_array(40);

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

void append_moves_array(Move* moves, Move* adding)
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

bool piece_possible_moves(Move* moves, Board board, Info info, Point start)
{
	Point stop; Move currMove; int amount = 0;
	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			stop = (Point) {height, width};
			currMove = (Move) {start, stop};

			if(!piece_move_acceptable(board, currMove, info)) continue;
			if(!move_prevent_check(board, currMove, info)) continue;

			moves[amount] = currMove;
			amount += 1;
		}
	}
	return (amount != 0);
}
