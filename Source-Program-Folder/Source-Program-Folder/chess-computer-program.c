
#include "../Header-Program-Folder/chess-computer-program.h"

/*

MIN MAX

DEPTH = 2

			0
		   / \
		  /   \
		 /     \
		/ 	    \
	   1 		 1
	  / \	    / \
	 /   \     /   \
	/     \   /     \
   2   	   2 2       2

calculate every possible move [depth 1]

go through every move in [depth 1]->
	calculate every possible move for enemy [depth 2]
	
	go throught every move for the enemy ->
		value the state of the board [the algorithm]

	pick the move that has the highest score,
	and set the move at [depth 1] to that score

PAWN 	= 10
KNIGHT	= 30
BISHOP	= 30
ROOK	= 50
QUEEN	= 90
KING 	= 900

 - all_possible_moves()

 - best_possible_move(board, info color, depth) (recursive)
 {
	moves = all_possible_moves()

	// The value is the total value difference between the teams;
	value;

	MoveValue bestMove = {moves[0], value};
	// This struct has a move and the score with that move;

	for move in moves
	{
		// Execute the current move (on a copy of the board);
		move_piece(board, move);

		// The depth is the grade of move you want to calculate
		// The higher depth, the higher chans the move is better
		value = value_of_board(board, color, depth);

		// If this move is better
		if(value > bestMove.value)
		{
			// Update the best move
			bestMove = move;
		}
	}
	return bestMove;
 }

 value_of_board(board, color, depth)
 {
	if(depth == 0) // Base case, should return the value
	{
		// The value is the total value difference between the teams;
		return value;
	}

	moves = all_possible_moves()

	best_value = 0;

	for move in moves
	{
		// Execute the current move (on a copy of the board);
		move_piece(board, move);

		value = value_of_board(board, color, depth - 1);

		if(value > best_value)
		{
			best_value = value;
		}
	}

	// Now we have found the best move of this board
	// We just return the best value

	return best_value;
 }

*/

#define MIN_VAL -100000
#define MAX_VAL +100000

bool best_possible_move(Move* move, Board board, Info info, int depth, Color color)
{
	if(depth <= 0) return false;

	Move* moves = all_possible_moves(board, info, color);
	int amount = moves_array_amount(moves);

	if(amount <= 0)
	{
		free(moves);

		return false;
	}

	sort_pruning_moves(moves, amount, board, info);

	Move bestMove = moves[0];
	int bestValue = MIN_VAL;

	Move currMove;

	Info dummyInfo;

	Board copy;

	Color next;

	int value;

	for(int index = 0; index < amount; index += 1)
	{
		currMove = moves[index];

		dummyInfo = info;
		dummyInfo.current = color;

		copy = copy_chess_board(board);

		if(!move_chess_piece(copy, currMove, &dummyInfo))
		{
			free(copy);

			CLEAR_LINE; printf("Cant move Main move!\n");
			
			continue;
		}

		next = (color == WHITE) ? BLACK : WHITE;
		value = board_depth_value(copy, dummyInfo, (depth - 1), MIN_VAL, MAX_VAL, color, next);

		free(copy);

		printf("Checking [%d %d] -> [%d %d] = [%d] Best = [%d]\n", currMove.start.height, currMove.start.width, currMove.stop.height, currMove.stop.width, value, bestValue);

		if(value > bestValue)
		{
			bestMove = currMove;
			bestValue = value;
		}
	}

	free(moves);

	*move = bestMove;

	CLEAR_LINE; printf("Best move [%d %d -> %d %d] [%d]\n",
		bestMove.start.height, bestMove.start.width, bestMove.stop.height, bestMove.stop.width, bestValue);

	return true;
}

int board_depth_value(Board board, Info info, int depth, int alpha, int beta, Color color, Color current)
{
	if(depth <= 0) // Base-case, Should return the value of the board
	{
		int value = color_state_value(board, info, color);
		return value;
	}

	Info dummyInfo = info;
	dummyInfo.current = current;

	Move* moves = all_possible_moves(board, dummyInfo, current);
	int amount = moves_array_amount(moves);

	if(amount <= 0)
	{
		free(moves);

		return (color == current) ? MIN_VAL : MAX_VAL;
	}

	sort_pruning_moves(moves, amount, board, info);

	int bestValue = (current == color) ? MIN_VAL : MAX_VAL;

	Move currMove;

	Board copy;

	Color next;

	int value;

	for(int index = 0; index < amount; index += 1)
	{
		currMove = moves[index];

		dummyInfo = info;
		dummyInfo.current = current;

		copy = copy_chess_board(board);

		if(!move_chess_piece(copy, currMove, &dummyInfo))
		{
			free(copy);

			CLEAR_LINE; printf("Cant move Depth move!\n");
			continue;
		}

		next = (current == WHITE) ? BLACK : WHITE;
		value = board_depth_value(copy, dummyInfo, (depth - 1), alpha, beta, color, next);

		free(copy);

		// Update best value (own)
		if(current == color && value > bestValue) bestValue = value;

		else if(current != color && value < bestValue) bestValue = value;
		

		// alpha-beta pruning (copying from internet, I am not smart)
		if(current == color && value > alpha) alpha = value;

		else if(current != color && value < beta) beta = value;


		if(beta <= alpha) break;
	}

	free(moves);

	return bestValue;
}

void sort_pruning_moves(Move* moves, int amount, Board board, Info info)
{
	// Scetchy!
	Color color = board_point_color(board, moves[0].start);

	Move first, second;
	int firstValue, secondValue;

	for(int iteration = 0; iteration < amount; iteration += 1)
	{
		for(int index = 0; index < (amount - iteration - 1); index += 1)
		{
			first = moves[index];
			second = moves[index + 1];

			firstValue = move_state_value(board, info, first, color);
			secondValue = move_state_value(board, info, second, color);

			if(firstValue > secondValue)
			{
				switch_array_moves(moves, index, (index + 1) );
			}
		}
	}
}

int move_state_value(Board board, Info info, Move move, Color color)
{
	Color current = board_point_color(board, move.start);

	Info dummyInfo = info;
	Board copy = copy_chess_board(board);

	if(!move_chess_piece(copy, move, &dummyInfo))
	{
		free(copy);

		return (color == current) ? MIN_VAL : MAX_VAL;
	}

	free(copy);

	return board_state_value(board, dummyInfo, color);
}

int color_state_value(Board board, Info info, Color color)
{
	int enemy = (color == WHITE) ? BLACK : WHITE;

	int enemyValue = board_state_value(board, info, enemy);
	int teamValue = board_state_value(board, info, color);

	return (teamValue - enemyValue);
}

typedef struct TypeValue
{
	Type type;
	int value;
} TypeValue;

const TypeValue typeValues[] = { {EMPTY, 0}, {PAWN, 10}, {KNIGHT, 30}, 
	{BISHOP, 30}, {ROOK, 50}, {QUEEN, 90}, {KING, 900} };

int team_pieces_value(Board board, Color color)
{
	Point point; Piece piece;

	int value = 0;

	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			point = (Point) {height, width};

			piece = board_point_piece(board, point);

			if(piece.color != color) continue;

			value += typeValues[piece.type].value;
		}
	}
	return value;
}

int check_mate_value(Board board, Info info, Color color)
{
	int value = 0;

	Color enemy = (color == WHITE) ? BLACK : WHITE;

	Point enemyKing = color_king_point(info, enemy);
	Point teamKing = color_king_point(info, color);

	if(check_mate_situation(board, info, teamKing)) 		value += MAX_VAL;
	else if(check_mate_situation(board, info, enemyKing)) 	value += MIN_VAL;

	return value;
}

int board_state_value(Board board, Info info, Color color)
{
	int value = 0;

	value += team_pieces_value(board, color);

	value += check_mate_value(board, info, color);

	// Add more parameters

	return value;
}

bool find_computer_move(Move* move, Board board, Info info, Color color)
{
	Move* moves = all_possible_moves(board, info, color);
	int amount = moves_array_amount(moves);

	if(amount == 0) { free(moves); return false; }

	shuffle_moves_array(moves, amount);

	MoveInfo bestMove = create_move_info(board, moves[0], info);

	Move current;

	for(int index = 0; index < amount; index += 1)
	{
		current = moves[index];

		update_best_move(&bestMove, board, current, info);
	}

	CLEAR_LINE; printf("[+] === BEST MOVE OUT OF [%d] === [+]\n", amount);
	CLEAR_LINE; display_move_info(bestMove);

	*move = bestMove.move; free(moves); return true;
}

void shuffle_moves_array(Move* moves, int amount)
{
	for(int index = 0; index < amount; index += 1)
	{
		int random = create_random_number(0, amount - 1);
		switch_array_moves(moves, index, random);
	}
}

void switch_array_moves(Move* moves, int first, int second)
{
	Move firstMove = moves[first];
	Move secondMove = moves[second];

	moves[first] = secondMove;
	moves[second] = firstMove;
}

MoveInfo create_move_info(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	MoveInfo moveInfo;

	moveInfo.move = move;

	moveInfo.setsCheck = simulate_enemy_check(board, move, info);

	moveInfo.checkMate = simulate_check_mate(board, move, info);

	moveInfo.takeEnemy = board_points_enemy(board, start, stop);

	moveInfo.getsTaken = piece_move_exposed(board, move, info);

	moveInfo.exposed = board_piece_exposed(board, info, start);

	moveInfo.type = board_point_type(board, start);
	moveInfo.enemy = board_point_type(board, stop);

	return moveInfo;
}

void update_best_move(MoveInfo* bestMove, Board board, Move move, Info info)
{
	MoveInfo current = create_move_info(board, move, info);

	if(default_bot_algorithm(board, *bestMove, current)) 
	{
		*bestMove = current;
	}
}

bool piece_move_exposed(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	Board copy = copy_chess_board(board);
	move_board_piece(copy, start, stop);

	if(board_piece_exposed(copy, info, stop))
	{ 
		free(copy); return true; 
	}

	free(copy); return false;
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

Move* all_possible_moves(Board board, Info info, Color color)
{
	Move* moves = create_moves_array(1024);
	Move* adding;

	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			Point point = {height, width};
			Color currColor = board_point_color(board, point);
			if(currColor != color) continue;

			adding = create_moves_array(40);

			if(!piece_possible_moves(adding, board, info, point)) continue;

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

int moves_array_amount(Move* moves)
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
