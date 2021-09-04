
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
